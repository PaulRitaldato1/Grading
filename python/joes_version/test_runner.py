from pathlib import Path
import shutil
import subprocess
from multiprocessing import Process, Queue, Lock
import utils
from report import Report, ReportResult

def test_students(students):
    config = utils.read_config_file("config.json")
    num_threads = config['threads']
    
    processes = []
    # a Queue is a thread safe queue used to share memory between the process
    student_queue = Queue()
    reports = Queue()
    # lock is used so threads won't interleave their console printing
    print_lock = Lock()
    # add each student to the queue of students to grade
    for student in students:
        student_queue.put(student)

    # create each process, pass it the queues and lock
    # each process will start the "run_tests" function
    for i in range(1, num_threads+1):
        print("Creating process {}".format(i))
        processes.append(Process(target=run_tests, args=(i, student_queue, reports, print_lock)))
    # start each thread, and block waiting for each to finish
    [p.start() for p in processes]
    [p.join() for p in processes]
    
    # get each report from the queue and add it to a regular array
    reports_arr = []
    while not(reports.empty()):
        reports_arr.append(reports.get())
    return reports_arr

def check_missing_files(student, required_files, submissions_folder):
    studentpath = submissions_folder/student
    # get a list of all files in the student's folder, relative to the student's folder
    student_files = [str(filepath.relative_to(studentpath))
                        for filepath
                        in studentpath.glob('**/*')
                        if not filepath.is_dir()]
    
    # return an array of all the required files not found in the student's files
    return [file for file in required_files if file not in student_files]

def setup_student_base_folder(test_runner_folder, project_base_folder, student_folder, required_files):
    # if the folder already exists, delete it and all its files
    if test_runner_folder.exists():
        shutil.rmtree(test_runner_folder)

    # copy the base folder to the test runner's folder
    shutil.copytree(project_base_folder, test_runner_folder)
    # copy each required file from the student's folder to the test runner folder
    for file in required_files:
        filepath = student_folder.joinpath(file)
        shutil.copy(filepath, test_runner_folder)

# a thread safe way of printing to the console
def proc_print(message, number, print_lock):
    print_lock.acquire()
    print("Process [{}]: {}".format(number, message))
    print_lock.release()

def run_tests(number, students, reports, print_lock):
    config = utils.read_config_file("config.json")
    required_files = config['required_files']
    submissions_folder = Path(config['submissions_folder'])
    project_base_folder = Path(config['project_base_folder'])

    # loop while there are more students to grade
    while not(students.empty()):
        student = students.get()
        proc_print("Grading {}".format(student), number, print_lock)

        # check if the student is missing any files
        missing_files = check_missing_files(student, required_files, submissions_folder)
        if missing_files:
            reports.put(Report(student, ReportResult.MISSING_FILES, "Missing files: {}".format(missing_files), {}))
        else:        
            # otherwise, try to compile and run their project
            student_folder = Path("submissions/{}".format(student))
            test_runner_folder = Path("grader-{}".format(number))
            setup_student_base_folder(test_runner_folder, project_base_folder, student_folder, required_files)
            
            log_file = Path("logs/{}.log".format(student))
            compiled = utils.build_project(test_runner_folder, log_file)
            if compiled:
                try:
                    test_results = utils.run_project(test_runner_folder, config['timeout'], log_file)
                    reports.put(Report(student, ReportResult.TESTS_RUN, "Tests Run", test_results))
                except subprocess.TimeoutExpired as e:
                    reports.put(Report(student, ReportResult.TIME_LIMIT_EXCEEDED, "Time Limit Exceeded", {}))
            else:
                reports.put(Report(student, ReportResult.COMPILATION_ERROR, "Compilation Error", {}))
        
        proc_print("Finished grading {}".format(student), number, print_lock)
