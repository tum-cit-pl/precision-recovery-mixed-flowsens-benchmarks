#!/usr/bin/env bash


shopt -s extglob

SERVER=goblint@server02
ANALYZERDIR=/home/goblint/pldi-25-svcomp/analyzer
MYBENCHDIR=/home/goblint/pldi-25-svcomp/analyzer/sv-comp/my-bench-sv-comp
BASE_RESULTSDIR=/home/goblint/pldi-25-svcomp/analyzer/sv-comp/my-bench-sv-comp/results
TASK_DEFINITIONS_DIR=./task-definitions
GOBLINTPARALLEL=35

# Variable to configure the suffix for table-generator
TASKSET_FOR_TABLE="/*SV-COMP24_unreach-call.xml.bz2"

# retrieve current analyzer commit hash
cd /home/goblint/pldi-25-svcomp/analyzer
analyzerhash=$(git show | head -n 1  | awk '{ print $2 }')
analyzerhash=${analyzerhash:0:7}
cd -

# List all XML task definitions in the specified directory
XML_TASKS=("$TASK_DEFINITIONS_DIR"/*.xml)

# Array to collect all result directories
RESULT_DIRS=()

for XML_FILE in "${XML_TASKS[@]}"; do
    # Extract the filename without the path
    XML_FILENAME=$(basename "$XML_FILE")

    # Create a unique results directory for each task
    RESULTSDIR="$BASE_RESULTSDIR/$(date +'%Y%m%d-%H%M%S')-$analyzerhash-all-tasks-${XML_FILENAME%.xml}"  # Removing '.xml' extension from the task name
    mkdir -p "$RESULTSDIR"

    # Add result directory to array
    RESULT_DIRS+=("$RESULTSDIR")

    # Run verification
    cd $ANALYZERDIR
    # read-only and overlay dirs for Value too large for defined data type workaround
    benchexec --read-only-dir / --overlay-dir . --overlay-dir /home --outputpath "$RESULTSDIR" --numOfThreads "$GOBLINTPARALLEL" "$MYBENCHDIR/$XML_FILE"

    # Extract witness directory
    cd "$RESULTSDIR"
    LOGDIR=$(echo goblint*.files)
    echo "$LOGDIR"

    # Generate table with merged results and witness validation results
    sed -e "s/LOGDIR/$LOGDIR/" "$MYBENCHDIR/table-generator-all-fast.xml" > table-generator.xml
    table-generator -x table-generator.xml

    # Decompress all tool outputs for table HTML links
    # unzip -o goblint*.logfiles.zip
done

# Construct the list of directories with the required suffix for table-generator
RESULT_FILES=()
for dir in "${RESULT_DIRS[@]}"; do
    RESULT_FILES+=("$dir$TASKSET_FOR_TABLE")
done

# Execute table-generator with all result files
table-generator "${RESULT_FILES[@]}"
