#!/usr/bin/python3
import sys

def process_csv(filename):
    try:
        with open(filename, 'r') as f:
            # Read the header line
            header = next(f)
            # Write header to both stdout and stderr
            sys.stdout.write(header)
            sys.stderr.write(header)

            # Process remaining lines
            for line in f:
                if "Failed" in line:
                    sys.stderr.write(line)
                else:
                    sys.stdout.write(line)
    except FileNotFoundError:
        sys.stderr.write(f"Error: File '{filename}' not found.\n")
        sys.exit(1)
    except StopIteration:
        sys.stderr.write("Error: The file is empty.\n")
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.stderr.write("Usage: python script.py <filename>\n")
        sys.exit(1)
    process_csv(sys.argv[1])
