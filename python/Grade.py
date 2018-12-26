#!/usr/bin/env python3
import sys
import zipfile
import os, os.path
import glob
import shutil #this is for removing non empty directories
import multiprocessing
from multiprocessing import Pool, Process, Lock
import csv
import time
import subprocess
from subprocess import PIPE
from subprocess import Popen
#This is a python version of the script. Im doing this to help me learn python :)
#There are gonna be little notes for myself all over this about cool stuff I found out about


def process_args():
    stage_num = 3

    if (len(sys.argv) < 2):
        return stage_num
    elif (sys.argv[1] == "-Rsc"):
        clean()
        sys.exit()
    elif (sys.argv[1] == "-s"):
        if(int(sys.argv[2]) >= 1 and int(sys.argv[2]) <= 3):
            stage_num = sys.argv[2]
        else:
            print("The command line argument " + sys.argv[2] + " is out of range. Number must be 1, 2 or 3. Try the -h flag")
            sys.exit()
    elif(sys.argv[1] == "-h"):
        print("Welcome to the Grader Script!")
        print("Here are the flags you can use: ")
        print("\t-h to display this menu")
        print("\t-Rsc to completely wipe all traces of everything")
        print("\t-s [STAGE_NUM] to choose up to what stage you want to execute")
        print("\t\t The stages available are:")
        print("\t\t\t 1. Unzip, and separate, and rename student files")
        print("\t\t\t 2. Compile student submissions")
        print("\t\t\t 3. Test compiled submissions")
    else:
        print("Running the grading script...")
        print("Try passing the -h flag if you need help")
        print("Default, running all three stages.")
        sys.exit()
    
    return stage_num

def init():
    path = os.getcwd()
    os.mkdir(path + "/Canvas")
    os.mkdir(path + "/StudentsToGrade")
    os.mkdir(path + "/Results")

def clean():
    path = os.getcwd()
    shutil.rmtree(path + "/Canvas")
    shutil.rmtree(path + "/StudentsToGrade")
    shutil.rmtree(path + "/Results")


#def update_progress(progress):
#    barLength = 100 
#    status = ""
#    if isinstance(progress, int):
#        progress = float(progress)
#    if not isinstance(progress, float):
#        progress = 0
#        status = "error: progress var must be float\r\n"
#    if progress < 0:
#        progress = 0
#        status = "Halt...\r\n"
#    if progress >= 1:
#        progress = 1
#        status = "Done...\r\n"
#    block = int(round(barLength*progress))
#    text = "\rPercent: [{0}] {1}% {2}".format( "#"*block + "-"*(barLength-block), progress*100, status)
#    sys.stdout.write(text)
#    sys.stdout.flush()

def correct_name(file_name):
    tmp = file_name.split("_")
    ext = file_name.split(".")
    if(len(ext) == 2):
        ext = '.' + ext[1]
    else:
        ext = ''

    if(tmp[1] == "late"):
        tmp = tmp[4].split(".")
    else:
        tmp = tmp[3].split(".")
    tmp2 = tmp[0].split("-")
    rtn = tmp2[0] + ext
    
    return rtn
    
def stage_1():

    print("Initialize the directory structure")
    init()

    #unzip submissions
    print("======================================== Unzipping student submissions ========================================")
    zip_file = glob.glob("*.zip")
    zip = zipfile.ZipFile(zip_file[0])
    zip.extractall("Canvas/")
    zip.close()
    print("======================================== Finished unzipping student submissions ========================================")
    
    #Separate student files
    print("Separating student submissions. Each student gets a directory all to themselves")
    files = sorted(os.listdir("Canvas/"))
    i = 0
    size = len(files)
    while i < size - 1:
        offset = 0
        
        
        student = files[i].split("_")
        temp = student[0]
        future = temp
        
        os.mkdir("StudentsToGrade/" + temp)

        while temp == future:

            shutil.move("Canvas/" + files[i + offset], "StudentsToGrade/" + temp + "/" + correct_name(files[i + offset]))

            offset += 1
           
            if ( (i + offset) > size - 1 ):
                break
            future = files[i + offset].split("_")
            future = future[0]

        i += offset

def compile(dir_name):
    os.system("g++ -std=c++11 " + "StudentsToGrade/" + dir_name + "/*.cpp -o StudentsToGrade/" + dir_name + "/TEST > /dev/null 2>&1")

def stage_2():
    
    #files = sorted(os.listdir("StudentsToGrade/"))
    files = os.listdir("StudentsToGrade/")
    with Pool(multiprocessing.cpu_count()) as p:
        p.map(compile, files)

def write_results(results,files):
    with files:
        writer = csv.writer(files)
        writer.writerow(results)


mutex = Lock()
def run_test(stu_name):
    test = ["7 2\ngoogle.com gmail.com\ngoogle.com maps.com\nfacebook.com ufl.edu\nufl.edu google.com\nufl.edu gmail.com\nmaps.com facebook.com\ngmail.com maps.com"]
    answer = ["facebook.com 0.20\ngmail.com 0.20\ngoogle.com 0.10\nmaps.com 0.30\nufl.edu 0.20"]

    results = [stu_name]
    with open("tests.txt", 'rb') as inputFile:
        try:
            for i in inputFile:
                exists=os.path.exists("StudentsToGrade/"+stu_name+"/TEST")
                if(exists):
                    proc = Popen("StudentsToGrade/"+stu_name+"/TEST", stdin=PIPE,stdout=PIPE)
                    out, err  = proc.communicate(input=i)
                    out = out.strip('b')
                    out = out.strip('\'')
                    print (out)
                    if(out == answer[0]):
                        results.append(1)
        except:
            print("ugh")

    files = open('Results/results.csv', 'a+')

    with mutex:
        write_results(results, files)
        

def stage_3():
    header = ["Name", "Test 1", "Test 2", "Test 3", "Test 4", "Test 5", "Test 6", "Test 7", "Test 8", "Test 9"]
    results = open('Results/results.csv', 'a+')
    with results:
        writer = csv.writer(results)
        writer.writerow(header)
        
    with Pool(multiprocessing.cpu_count()) as p:
        p.map(run_test, sorted(os.listdir("StudentsToGrade/")))


def main():
#Notes:    
    #found out that python stores variables in memory differently than normal languages. Example:
    #a=1
    #a=2
    #these are both references to TWO different objects. the '=' operator simply updates the reference to a different location
    #Since '1' no longer has anything referencing it, it is garbage collected. But, there can be many references to that '1'
    #To simulate 'pass-by-reference' you need to pass in a mutable object. 
#end Notes

    #get stage num from command line or set default
    #also check other command line args
    stage_num = process_args()

    if(int(stage_num) >= 1):
        stage_1()

        if(int(stage_num) >=2):
            stage_2()

            if(int(stage_num) == 3):
                stage_3()
main()
