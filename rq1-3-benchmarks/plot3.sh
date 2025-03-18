#!/bin/bash
# Extract the data from the raw data file
if [[ "$1" == "--paper" ]]; then
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec paper-runs/svcomp-raw.txt ours20 base > plots/3/plot3-ours20-vs-base.csv
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec paper-runs/svcomp-raw.txt ours3 base > plots/3/plot3-ours3-vs-base.csv
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec paper-runs/svcomp-raw.txt apinis base > plots/3/plot3-apinis-vs-base.csv
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec --zero-ambiguous paper-runs/svcomp-raw.txt ours20 base > plots/3/plot3-ours20-vs-base-unambiguous.csv
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec --zero-ambiguous paper-runs/svcomp-raw.txt ours3 base > plots/3/plot3-ours3-vs-base-unambiguous.csv
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec --zero-ambiguous paper-runs/svcomp-raw.txt apinis base > plots/3/plot3-apinis-vs-base-unambiguous.csv
    ./runtimes_to_csv.py --mode count-rec paper-runs/svcomp-raw.txt > plots/3/timeout-counts.tex
else
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec svcomp-raw.txt ours20 base > plots/3/plot3-ours20-vs-base.csv
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec svcomp-raw.txt ours3 base > plots/3/plot3-ours3-vs-base.csv
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec svcomp-raw.txt apinis base > plots/3/plot3-apinis-vs-base.csv
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec --zero-ambiguous svcomp-raw.txt ours20 base > plots/3/plot3-ours20-vs-base-unambiguous.csv
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec --zero-ambiguous svcomp-raw.txt ours3 base > plots/3/plot3-ours3-vs-base-unambiguous.csv
    ./prec_to_csv_cumulative.py --mode cumulative-diff-rec --zero-ambiguous svcomp-raw.txt apinis base > plots/3/plot3-apinis-vs-base-unambiguous.csv
    ./runtimes_to_csv.py --mode count-rec svcomp-raw.txt > plots/3/timeout-counts.tex
fi
cd plots/3 && pdflatex plot3.tex && cd ..
