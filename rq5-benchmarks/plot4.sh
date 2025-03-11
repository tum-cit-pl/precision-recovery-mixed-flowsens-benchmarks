#!/bin/bash
# Extract the data from the raw data file
if [[ "$1" == "--paper" ]]; then
    ./prec_to_csv_cumulative.py --mode all --compare glob paper-runs/plot4-7-raw.txt base &> plots/4/plot4-differences.csv
else
    ./prec_to_csv_cumulative.py --mode all --compare glob plot4-7-raw.txt base &> plots/4/plot4-differences.csv
fi
# Normalize CSV file by renaming benchmarks with long names, sorting etc
../helper-scripts/postprocess-csv.py plots/4/plot4-differences.csv
# Generate the plot
cd plots/4 && pdflatex plot4.tex && cd ..
