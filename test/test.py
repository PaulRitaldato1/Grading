#!/usr/bin/env python3

import subprocess
from subprocess import PIPE
from subprocess import Popen
import os

def main():
    print("it started")
    os.system("g++ -std=c++11 test.cpp -o TEST")
    with open("test.txt", 'rb') as inputFile:
#        print("in with")
        for i in inputFile:
            proc = Popen("./TEST", stdin=PIPE,stdout=PIPE)
            out, err = proc.communicate(input=i)
            print (out)

main()
