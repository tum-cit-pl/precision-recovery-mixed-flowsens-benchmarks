#!/bin/bash
# Extract the data from the raw data file
if [[ "$1" == "--paper" ]]; then
    ./prec_to_csv_cumulative.py paper-runs/svcomp-raw.txt ours20 base > plots/2/plot2-ours20-vs-base.csv
    ./prec_to_csv_cumulative.py paper-runs/svcomp-raw.txt ours3 base > plots/2/plot2-ours3-vs-base.csv
    ./prec_to_csv_cumulative.py paper-runs/svcomp-raw.txt apinis base > plots/2/plot2-apinis-vs-base.csv
    ./prec_to_csv_cumulative.py --zero-ambiguous paper-runs/svcomp-raw.txt ours20 base > plots/2/plot2-ours20-vs-base-unambiguous.csv
    ./prec_to_csv_cumulative.py --zero-ambiguous paper-runs/svcomp-raw.txt ours3 base > plots/2/plot2-ours3-vs-base-unambiguous.csv
    ./prec_to_csv_cumulative.py --zero-ambiguous paper-runs/svcomp-raw.txt apinis base > plots/2/plot2-apinis-vs-base-unambiguous.csv
    ./runtimes_to_csv.py --mode count paper-runs/svcomp-raw.txt > plots/2/timeout-counts.tex
else
    ./prec_to_csv_cumulative.py svcomp-raw.txt ours20 base > plots/2/plot2-ours20-vs-base.csv
    ./prec_to_csv_cumulative.py svcomp-raw.txt ours3 base > plots/2/plot2-ours3-vs-base.csv
    ./prec_to_csv_cumulative.py svcomp-raw.txt apinis base > plots/2/plot2-apinis-vs-base.csv
    ./prec_to_csv_cumulative.py --zero-ambiguous svcomp-raw.txt ours20 base > plots/2/plot2-ours20-vs-base-unambiguous.csv
    ./prec_to_csv_cumulative.py --zero-ambiguous svcomp-raw.txt ours3 base > plots/2/plot2-ours3-vs-base-unambiguous.csv
    ./prec_to_csv_cumulative.py --zero-ambiguous svcomp-raw.txt apinis base > plots/2/plot2-apinis-vs-base-unambiguous.csv
    ./runtimes_to_csv.py --mode count svcomp-raw.txt > plots/2/timeout-counts.tex
fi
cd plots/2 && pdflatex plot2.tex && cd ..
