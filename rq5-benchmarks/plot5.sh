#!/bin/bash
# Extract the data from the raw data file
if [[ "$1" == "--paper" ]]; then
    ./runtimes_to_csv.py --mode timing --split 35 paper-runs/plot5-6-raw.txt > plots/5/plot5-short.csv 2> plots/5/plot5-long.csv
else
    ./runtimes_to_csv.py --mode timing --split 35 plot5-6-raw.txt > plots/5/plot5-short.csv 2> plots/5/plot5-long.csv
fi
# Normalize CSV files by renaming benchmarks with long names, sorting etc
../helper-scripts/postprocess-csv.py plots/5/plot5-long.csv
../helper-scripts/postprocess-csv.py plots/5/plot5-short.csv
# Move plots where a run failed to a separate file
./split-out-fails.py plots/5/plot5-long.csv > plots/5/plot5-long-nofails.csv 2> plots/5/plot5long-fails.csv
./separate-extra-long.py plots/5/plot5-long-nofails.csv > plots/5/plot5-middle.csv 2> plots/5/plot5-extra.csv
./separate-extra-short.py plots/5/plot5-short.csv > plots/5/plot5-extra-short.csv 2> plots/5/plot5-middle-low.csv
# Generate the plot
cd plots/5 && pdflatex plot5.tex && cd ..
