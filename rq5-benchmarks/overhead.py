#!/usr/bin/python3
import csv
import argparse
import subprocess

parser = argparse.ArgumentParser(description="Process a CSV file computer overhead.")
parser.add_argument('--paper', action='store_true', help="Use 'paper-runs/plot5-6-raw.txt instead of 'plot5-6-raw.txt'.")
args = parser.parse_args()

paper = "--paper" if args.paper else ""

command = ["./plot5.sh", paper]
result = subprocess.run(command, stdout=subprocess.PIPE, universal_newlines=True)


# Initialize variables to store the maximal overhead and corresponding row
max_overhead = 0
max_overhead_row = None

# Read the data from the file
with open('plots/5/plot5-long-nofails.csv', 'r') as file:
    reader = csv.DictReader(file)

    for row in reader:
        # Extract the values for 'ours' and 'ours-bot'
        ours = float(row['ours'])
        ours_bot = float(row['ours-bot'])

        # Calculate the overhead
        overhead = ours_bot / ours

        # Update the maximal overhead if the current overhead is higher
        if overhead > max_overhead:
            max_overhead = overhead
            max_overhead_row = row

with open('plots/5/plot5-short.csv', 'r') as file:
    reader = csv.DictReader(file)

    for row in reader:
        # Extract the values for 'ours' and 'ours-bot'
        ours = float(row['ours'])
        ours_bot = float(row['ours-bot'])

        # Calculate the overhead
        overhead = ours_bot / ours

        # Update the maximal overhead if the current overhead is higher
        if overhead > max_overhead:
            max_overhead = overhead
            max_overhead_row = row

# Print the maximal overhead and the corresponding row
print(f"Maximal overhead of 'ours-bot' over 'ours': {max_overhead:.2f}")
print(f"Corresponding row: {max_overhead_row}")
