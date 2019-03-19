from pathlib import Path
import sys
import csv
from report import Report, ReportResult
import test_runner
import utils

config = None

def get_fields():
    print("Compiling base project")
    compiled = utils.build_project(config['project_base_folder'], clean_build=True)
    if not compiled:
        print("Building base project failed")
        sys.exit(1)
    # use the base project to find which test cases exist
    print("Running base project to discover test cases")
    test_results = utils.run_project(config['project_base_folder'])

    fields = ["Name", "Total", "Notes"]
    # add a column for each test case
    for test_case in test_results.keys():
        fields.append(test_case)
    
    return fields

def get_students():
    students = []
    submission_folder = Path(config['submissions_folder'])
    # iterate over each folder in the submission folder
    for filepath in submission_folder.iterdir():
        if not filepath.is_dir():
            continue
        
        students.append(filepath.name)
    
    return students

def save_reports(fields, reports):
    csv_filename = config['output_file']
    with open(csv_filename, 'w') as csvfile:
        csvwriter = csv.writer(csvfile)
        # write the column headers to the file
        csvwriter.writerow(fields)

        for report in reports:
            # build a row for each student and write it to the file
            row = []
            row.append(report.get_name())
            row.append(report.get_total())
            row.append(report.get_notes())
            for key, value in sorted(report.get_test_scores().items()):
                row.append(value)
            csvwriter.writerow(row)

if __name__ == "__main__":
    config = utils.read_config_file("config.json")
    # make the logs folder if it doesn't exist
    log_folder = Path(config['log_folder'])
    log_folder.mkdir(exist_ok=True)

    # make a list of students to grade
    students = get_students()
    # make a list of columns for the final csv file
    fields = get_fields()
    reports = []

    # start testing each student's submission
    test_reports = test_runner.test_students(students)
    for report in test_reports:
        reports.append(report)
    
    save_reports(fields, reports)
    

"""
Resources:
https://docs.python.org/3.6/library/os.html
https://docs.python.org/3/library/re.html
https://docs.python.org/3/library/shutil.html#shutil.copystat
https://docs.python.org/3/library/subprocess.html#using-the-subprocess-module
https://docs.python.org/3/library/multiprocessing.html#multiprocessing.Array
"""