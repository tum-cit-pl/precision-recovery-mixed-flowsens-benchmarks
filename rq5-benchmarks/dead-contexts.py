#!/usr/bin/python3
import subprocess
import sys
import csv
import argparse


# Set up argument parsing
parser = argparse.ArgumentParser(description="Process a CSV file and count improvements/worsening.")
parser.add_argument('--paper', action='store_true', help="Use 'paper-runs/plot4-7-raw.txt instead of 'plot4-7-raw.txt'.")
args = parser.parse_args()

# Determine the input file based on the --paper argument
input_file = "paper-runs/plot4-7-raw.txt" if args.paper else "plot4-7-raw.txt"

# Run the command and capture its output
command = ["./runtimes_to_csv.py", "--mode", "dead", input_file]
result = subprocess.run(command, stdout=subprocess.PIPE, universal_newlines=True)

# Parse the CSV output
csv_data = result.stdout.splitlines()
csv_reader = csv.DictReader(csv_data)

deads = 0
all = 0

# Process the data
processed_data = []
for row in csv_reader:
    # Subtract `worse` from `better` to get the new `better`
    dead = float(row['stillbot']) / float(row['total'])
    if dead >= 0.4:
        deads += 1
    all += 1

# Output the results
print(f"Total entries: {all}")
print(f"40% or more identified : {deads}")
