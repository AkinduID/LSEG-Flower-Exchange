import os
import subprocess
import filecmp
import sys

INPUT_DIR = os.path.join('tests', 'integration_test', 'input')
OUTPUT_DIR = os.path.join('data', 'output')
VALIDATE_DIR = os.path.join('tests', 'integration_test', 'validate')
APP_EXECUTABLE = os.path.join('build', 'LSEG_Flower_Exchange.exe') if os.name == 'nt' else os.path.join('build', 'LSEG_Flower_Exchange')


def run_application(order_file, output_file):
    """
    Runs the application with the given order file and writes output to output_file.
    Assumes the application takes input and output file paths as arguments.
    """
    result = subprocess.run([
        APP_EXECUTABLE,
        '--input', order_file,
        '--output', output_file
    ], capture_output=True, text=True)
    return result.returncode, result.stdout, result.stderr


import csv

def compare_csv(file1, file2):
    """
    Compares two CSV files for exact match, ignoring the 'transaction time' column (case/whitespace-insensitive),
    ignoring column order, and sorting rows for robust comparison.
    Returns True if they match (ignoring transaction time), False otherwise.
    """
    def normalize_header(header):
        return header.strip().lower().replace(' ', '')

    def read_csv_wo_time(path):
        with open(path, newline='', encoding='utf-8') as f:
            reader = csv.DictReader(f)
            # Normalize headers
            norm_headers = [normalize_header(h) for h in reader.fieldnames]
            # Find index of transaction time column (if any)
            time_idx = None
            for i, h in enumerate(norm_headers):
                if h == 'transactiontime':
                    time_idx = i
            # Build rows without transaction time, normalize whitespace in values
            rows = []
            for row in reader:
                row_wo_time = {}
                for k, v in row.items():
                    if normalize_header(k) == 'transactiontime':
                        continue
                    row_wo_time[normalize_header(k)] = v.strip() if v is not None else ''
                rows.append(row_wo_time)
            return rows

    def sort_rows(rows):
        # Sort by all keys in row
        return sorted(rows, key=lambda r: tuple(r.get(k, '') for k in sorted(r.keys())))

    rows1 = sort_rows(read_csv_wo_time(file1))
    rows2 = sort_rows(read_csv_wo_time(file2))
    return rows1 == rows2


def main():
    failed = False
    for filename in os.listdir(INPUT_DIR):
        if not filename.endswith('.csv'):
            continue
        input_path = os.path.join(INPUT_DIR, filename)
        base, ext = os.path.splitext(filename)
        output_path = os.path.join(OUTPUT_DIR, f"{base}_exec_report{ext}")
        # Map order1.csv -> example1_output.csv, order2.csv -> example2_output.csv, etc.
        if filename.startswith('order') and filename.endswith('.csv'):
            num = filename[len('order'):-len('.csv')]
            expected_filename = f"example{num}_output.csv"
        else:
            expected_filename = filename  # fallback, should not happen
        expected_path = os.path.join(VALIDATE_DIR, expected_filename)

        print(f'Running test for {filename}...')
        rc, out, err = run_application(input_path, output_path)
        if rc != 0:
            print(f'  ERROR: Application failed for {filename}: {err}')
            failed = True
            continue
        if not os.path.exists(expected_path):
            print(f'  WARNING: No expected file for {filename} (looked for {expected_path})')
            continue
        if compare_csv(output_path, expected_path):
            print(f'  PASS: {filename}')
        else:
            print(f'  FAIL: {filename} output does not match expected.')
            failed = True
    if failed:
        sys.exit(1)
    else:
        print('All integration tests passed.')

if __name__ == '__main__':
    main()
