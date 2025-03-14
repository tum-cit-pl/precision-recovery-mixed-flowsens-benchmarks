#!/usr/bin/python3
import subprocess
import sys
import csv
import argparse

# Function to compute statistics
def compute_statistics(data):
    improved_ge_0 = 0
    improved_ge_5 = 0
    worsened_lt_0 = 0
    worsened_le_5 = 0

    for row in data:
        better = float(row['better'])

        if better > 0:
            improved_ge_0 += 1
            if better >= 0.05:
                improved_ge_5 += 1
        elif better < 0:
            worsened_lt_0 += 1
            if better <= -0.05:
                worsened_le_5 += 1

    return improved_ge_0, improved_ge_5, worsened_lt_0, worsened_le_5

# Set up argument parsing
parser = argparse.ArgumentParser(description="Process a CSV file and count improvements/worsening.")
parser.add_argument('--compare', type=str, required=True, help="Comparison argument (e.g., apinis).")
parser.add_argument('--paper', action='store_true', help="Use 'paper-runs/plot4-7-raw.txt instead of 'plot4-7-raw.txt'.")
args = parser.parse_args()

compare = args.compare

# Determine the input file based on the --paper argument
input_file = "paper-runs/plot4-7-raw.txt" if args.paper else "plot4-7-raw.txt"

# Run the command and capture its output
command = ["./prec_to_csv_cumulative.py", "--mode", "all", "--compare", "glob", input_file, "base"]
result = subprocess.run(command, stdout=subprocess.PIPE, universal_newlines=True)

# Parse the CSV output
csv_data = result.stdout.splitlines()
csv_reader = csv.DictReader(csv_data)

# Process the data
processed_data = []
for row in csv_reader:

    # Subtract `worse` from `better` to get the new `better`
    better = float(row['worse-' + compare])-float(row['better-' + compare])
    processed_data.append({
        'suite': row['suite'],
        'file': row['file'],
        'better': better
    })

# Compute statistics
improved_ge_0, improved_ge_5, worsened_lt_0, worsened_le_5 = compute_statistics(processed_data)

# Calculate total number of entries
total_entries = len(processed_data)

# Calculate percentages
improved_ge_0_percent = (improved_ge_0 / total_entries) * 100 if total_entries > 0 else 0
improved_ge_5_percent = (improved_ge_5 / total_entries) * 100 if total_entries > 0 else 0
worsened_lt_0_percent = (worsened_lt_0 / total_entries) * 100 if total_entries > 0 else 0
worsened_le_5_percent = (worsened_le_5 / total_entries) * 100 if total_entries > 0 else 0

# Output the results
print(f"Total entries: {total_entries}")
print(f"improved (> 0%) : {improved_ge_0} ({improved_ge_0_percent:.2f}%)")
print(f"improved significantly (>= 5%) : {improved_ge_5} ({improved_ge_5_percent:.2f}%)")
print(f"worsened (< 0%) : {worsened_lt_0} ({worsened_lt_0_percent:.2f}%)")
print(f"worsened significantly (<= -5%) : {worsened_le_5} ({worsened_le_5_percent:.2f}%)")
