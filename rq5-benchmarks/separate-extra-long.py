#!/usr/bin/python3
import csv
import sys

def process_csv(filename):
    with open(filename, 'r') as f:
        reader = csv.reader(f)
        header = next(reader)

        # Determine indices for required columns dynamically
        required_columns = ['apinis', 'base', 'ours', 'ours-bot']
        column_indices = {}
        for col in required_columns:
            if col not in header:
                sys.stderr.write(f"Error: Required column '{col}' not found in CSV header.\n")
                sys.exit(1)
            column_indices[col] = header.index(col)

        stdout_writer = csv.writer(sys.stdout)
        stderr_writer = csv.writer(sys.stderr)

        # Write header to both outputs
        stdout_writer.writerow(header)
        stderr_writer.writerow(header)

        for row in reader:
            try:
                # Extract values using dynamic indices
                apinis = float(row[column_indices['apinis']])
                base = float(row[column_indices['base']])
                ours = float(row[column_indices['ours']])
                ours_bot = float(row[column_indices['ours-bot']])
            except (ValueError, IndexError) as e:
                sys.stderr.write(f"Error processing row {row}: {str(e)}\n")
                continue

            # Check if any value exceeds 500
            if any(val > 500 for val in [apinis, base, ours, ours_bot]):
                stderr_writer.writerow(row)
            else:
                stdout_writer.writerow(row)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.stderr.write("Usage: python script.py <input_csv>\n")
        sys.exit(1)
    process_csv(sys.argv[1])
