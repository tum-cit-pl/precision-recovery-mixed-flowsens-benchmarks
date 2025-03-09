#!/bin/bash
# Extract the data from the raw data file
./runtimes_to_csv.py --mode dead plot4-7-raw.txt > plots/7/plot7-dead.csv
# Normalize CSV file by renaming benchmarks with long names, sorting etc
../helper-scripts/postprocess-csv.py plots/7/plot7-dead.csv
# Generate the plot
cd plots/7 && pdflatex plot7.tex && cd ..
