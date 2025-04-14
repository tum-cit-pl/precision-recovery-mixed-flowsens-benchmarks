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

    total_entries = len(data)
    improved_ge_0_percent = (improved_ge_0 / total_entries) * 100 if total_entries > 0 else 0
    improved_ge_5_percent = (improved_ge_5 / total_entries) * 100 if total_entries > 0 else 0
    worsened_lt_0_percent = (worsened_lt_0 / total_entries) * 100 if total_entries > 0 else 0
    worsened_le_5_percent = (worsened_le_5 / total_entries) * 100 if total_entries > 0 else 0

    return {
        'total_entries': total_entries,
        'improved_ge_0': improved_ge_0,
        'improved_ge_0_percent': improved_ge_0_percent,
        'improved_ge_5': improved_ge_5,
        'improved_ge_5_percent': improved_ge_5_percent,
        'worsened_lt_0': worsened_lt_0,
        'worsened_lt_0_percent': worsened_lt_0_percent,
        'worsened_le_5': worsened_le_5,
        'worsened_le_5_percent': worsened_le_5_percent
    }

# Set up argument parsing
parser = argparse.ArgumentParser(description="Process a CSV file and count improvements/worsening.")
parser.add_argument('--compare', type=str, required=True, help="Comparison argument (e.g., ours20).")
parser.add_argument('--paper', action='store_true', help="Use 'paper-runs/svcomp-raw.txt' instead of 'svcomp-raw.txt'.")
parser.add_argument('--rec', action='store_true', help="Only consider recursive-related suites.")
args = parser.parse_args()

# Determine the input file based on the --paper argument
input_file = "paper-runs/svcomp-raw.txt" if args.paper else "svcomp-raw.txt"

# Run the command and capture its output
command = ["./prec_to_csv_cumulative.py", input_file, args.compare, "base", "--mode", "all"]
result = subprocess.run(command, stdout=subprocess.PIPE, universal_newlines=True)

# Parse the CSV output
csv_data = result.stdout.splitlines()
csv_reader = csv.DictReader(csv_data)

# Define recursive-related suites
recursive_suites = [
    "recursive", "recursive-simple", "recursive-with-pointer", "verifythis",
    "recursified_loop-crafted", "recursified_loop-invariants", "recursified_loop-simple",
    "recursified_nla-digbench"
]

# Process the data and group by suite
suite_data = {}
for row in csv_reader:
    # Skip entries if --rec is supplied and the suite is not in the recursive list
    if args.rec and row['suite'] not in recursive_suites:
        continue

    # Subtract `worse` from `better` to get the new `better`
    better = float(row['better']) - float(row['worse'])
    processed_row = {
        'suite': row['suite'],
        'file': row['file'],
        'better': better,
        'worse': row['worse'],
        'incomparable': row['incomparable']
    }

    if row['suite'] not in suite_data:
        suite_data[row['suite']] = []
    suite_data[row['suite']].append(processed_row)

# Compute and print statistics for each suite
for suite, data in suite_data.items():
    stats = compute_statistics(data)

    print(f"\nSuite: {suite}")
    print(f"Total entries: {stats['total_entries']}")
    print(f"improved (> 0%) : {stats['improved_ge_0']} ({stats['improved_ge_0_percent']:.2f}%)")
    print(f"improved significantly (>= 5%) : {stats['improved_ge_5']} ({stats['improved_ge_5_percent']:.2f}%)")
    print(f"worsened (< 0%) : {stats['worsened_lt_0']} ({stats['worsened_lt_0_percent']:.2f}%)")
    print(f"worsened significantly (<= -5%) : {stats['worsened_le_5']} ({stats['worsened_le_5_percent']:.2f}%)")

# Compute and print overall statistics if there are multiple suites
if len(suite_data) > 1:
    all_data = []
    for data in suite_data.values():
        all_data.extend(data)

    stats = compute_statistics(all_data)

    print("\nOverall statistics:")
    print(f"Total entries: {stats['total_entries']}")
    print(f"improved (> 0%) : {stats['improved_ge_0']} ({stats['improved_ge_0_percent']:.2f}%)")
    print(f"improved significantly (>= 5%) : {stats['improved_ge_5']} ({stats['improved_ge_5_percent']:.2f}%)")
    print(f"worsened (< 0%) : {stats['worsened_lt_0']} ({stats['worsened_lt_0_percent']:.2f}%)")
    print(f"worsened significantly (<= -5%) : {stats['worsened_le_5']} ({stats['worsened_le_5_percent']:.2f}%)")
