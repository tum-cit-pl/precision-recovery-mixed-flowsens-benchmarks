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

gain =0
loss = 0

# Read the data from the file
with open('plots/5/plot5-long-nofails.csv', 'r') as file:
    reader = csv.DictReader(file)

    for row in reader:
        # Extract the values for 'ours' and 'ours-bot'
        ours = float(row['ours-memory'])
        ours_bot = float(row['ours-bot-memory'])

        # Calculate the overhead
        reduction = ours_bot / ours

        if reduction < 0.8:
            gain += 1
        elif reduction > 1.2:
            loss += 1

        print(f"Memory usage of ours-bot as fraction of ours for {row['file']} : {reduction:.2f}")

with open('plots/5/plot5-short.csv', 'r') as file:
    reader = csv.DictReader(file)

    for row in reader:
        # Extract the values for 'ours' and 'ours-bot'
        ours = float(row['ours-memory'])
        ours_bot = float(row['ours-bot-memory'])

        # Calculate the overhead
        reduction = ours_bot / ours

        if reduction < 0.8:
            gain += 1
        elif reduction > 1.2:
            loss += 1


        print(f"Memory usage of ours-bot as fraction of ours for {row['file']} : {reduction:.2f}")

# Print reduction and gain
print(f"Gain: {gain}")
print(f"Loss: {loss}")
