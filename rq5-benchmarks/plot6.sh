#!/bin/bash
# Extract the data from the raw data file
./runtimes_to_csv.py --mode timing --split 60 plot5-6-raw.txt > plots/6/plot6-short.csv 2> plots/6/plot6-long.csv
# Normalize CSV files by renaming benchmarks with long names, sorting etc
../helper-scripts/postprocess-csv.py plots/6/plot6-long.csv
../helper-scripts/postprocess-csv.py plots/6/plot6-short.csv
# Move plots where a run failed to a separate file
./split-out-fails.py plots/6/plot6-long.csv > plots/6/plot6-long-nofails.csv 2> plots/6/plot6long-fails.csv
# Generate the plot
cd plots/6 && pdflatex plot6.tex && cd ..
