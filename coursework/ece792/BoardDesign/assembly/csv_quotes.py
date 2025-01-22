import csv

# Define the input and output file paths
input_file = "BoardDesign1.csv"
output_file = "BoardDesign2.csv"

# Function to add double quotes around each value in a CSV row
def add_quotes(row):
    return [f"{value}" for value in row]

# Read the input CSV and write to the output CSV with quotes added
with open(input_file, newline="") as csvfile:
    with open(output_file, 'w', newline="") as outfile:
        reader = csv.reader(csvfile)
        writer = csv.writer(outfile)
        for row in reader:
            writer.writerow(add_quotes(row))

print("Quotes added successfully!")
