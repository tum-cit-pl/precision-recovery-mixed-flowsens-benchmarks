#!/usr/bin/python3
import subprocess
import sys
import csv
import argparse
from collections import defaultdict

def seconds_to_human(seconds):
    hours = int(seconds // 3600)
    remaining = seconds % 3600
    minutes = int(remaining // 60)
    seconds = remaining % 60

    parts = []
    if hours > 0:
        parts.append(f"{hours}h")
    if minutes > 0 or hours > 0:  # Show minutes even if 0 if we have hours
        parts.append(f"{minutes}m")
    parts.append(f"{seconds:.1f}s")  # Show 1 decimal place for seconds

    return " ".join(parts)


# Set up argument parsing
parser = argparse.ArgumentParser(description="Process a CSV file and count improvements/worsening.")
parser.add_argument('--paper', action='store_true', help="Use 'paper-runs/svcomp-raw.txt' instead of 'svcomp-raw.txt'.")
args = parser.parse_args()

# Determine the input file based on the --paper argument
input_file = "paper-runs/svcomp-raw.txt" if args.paper else "svcomp-raw.txt"


command = ["./runtimes_to_csv.py", input_file]
result = subprocess.run(command, stderr=subprocess.PIPE, universal_newlines=True)

# Parse the CSV output
csv_data = result.stderr.splitlines()
csv_reader = csv.DictReader(csv_data)

suite_totals = defaultdict(float)

for row in csv_reader:
    # Check if any of the relevant columns contains 'timeout'
    def parse_value(val):
        if not val:
            return 0
        if 'timeout' in val.lower():
            return 900
        try:
            return float(val)
        except ValueError:
            return 0

    ours20 = parse_value(row['ours20'])
    base = parse_value(row['base'])
    apinis = parse_value(row['apinis'])
    ours3 = parse_value(row['ours3'])

    total = ours20 + base + apinis + ours3
    suite_totals[row['suite']] += total




for suite, total in suite_totals.items():
    print(f"{suite}: {seconds_to_human(total)} seconds")
