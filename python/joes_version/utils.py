import json
import subprocess
import xml.etree.ElementTree as ET
import re

def read_config_file(config_filename):
    with open(config_filename) as json_data:
        config_data = json.load(json_data)
    return config_data

# returns true if the project compiles succesfully
# and false otherwise
def build_project(test_runner_folder, log_file = None, clean_build = False):
    try:
        # clean the build if clean_build is true
        if(clean_build):
            subprocess.run(["make", "clean"],
                            cwd=test_runner_folder)

        # open a subprocess to run the compile command
        completed = subprocess.run(["make", "build/test"],
                        stdout=subprocess.PIPE,
                        stderr=subprocess.STDOUT,
                        cwd=test_runner_folder,
                        check=True)
        # save the output text
        log_text = completed.stdout.decode()
        return True
    except subprocess.CalledProcessError as e:
        # if the compilation fails, save the output text
        log_text = e.stdout.decode()
        return False
    finally:
        if(log_file != None):
            # write the output to the student's log file
            with open(log_file, "w+") as log:
                log.write("===========================\n")
                log.write("         COMPILE\n")
                log.write("===========================\n")
                log.write(log_text)

# sometimes the text in the expanded section of the xml will cause it to fail to parse
# this function will remove those sections
def clean_xml(output):
    return re.sub("<Expanded>[\s\S]*?<\/Expanded>", "", output.decode("utf-8"))

def parse_section(section_root, case_number, section_name):
    test_results = {}
    children = section_root.findall('Section')
    
    if(children != []):
        for child in section_root.findall('Section'):
            child_name = section_name + ">" + child.attrib['name']
            new_cases = parse_section(child, case_number, child_name)
            test_results.update(new_cases)
            case_number += len(new_cases)
    elif section_root.find('OverallResults') != None:
        name = "Test Case {}: {}".format(case_number, section_name)
        score = 1 if section_root.find('OverallResults').attrib['failures'] == '0' else 0
        test_results[name] = score
    
    return test_results

def parse_results(output):
    test_results = {}
    output = clean_xml(output)
    # build the xml tree
    xml_root = ET.fromstring(output)
    # go through each test case, get its overall result
    # set the score to 1 if it passed, otherwise set score to 0
    case_number = 1
    for test_case in xml_root.find('Group').findall('TestCase'):
        new_cases = parse_section(test_case, case_number, test_case.attrib['name'])
        test_results.update(new_cases)
        case_number += len(new_cases)
    
    return test_results

def run_project(test_runner_folder, timeout=None, log_file = None):
    # will raise an error if timeout occurs
    completed = subprocess.run(["./build/test", "-r xml"],
                                stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT,
                                cwd=test_runner_folder,
                                timeout=timeout)
    # save the output if the log file is specified
    if(log_file != None):
            with open(log_file, "a") as log:
                log.write("===========================\n")
                log.write("         Execution\n")
                log.write("===========================\n")
                log.write(completed.stdout.decode())
    # parse the xml output and return it
    return parse_results(completed.stdout)

    