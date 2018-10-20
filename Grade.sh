#!/bin/bash

#function definitions will go here
init(){
	#mkdir Results
	#	mkdir Results/Sections
	mkdir Students
	mkdir .grader
	mkdir .grader/Logs
		touch .grader/Logs/runtime_error_log
		touch .grader/Logs/compile_log
		touch .grader/Logs/test_log
		touch .grader/Logs/script_run_log
}

#declaring flag booleans & variables 
verbose=false
init=false
type_stdio=false
type_interface=false
threading=false
file="tests"

#parse input, grab flags
while test $# -gt 0; do
	case "$1" in
		-h|--help)
			echo "Welcome to the Grader script!"
			echo "The format of this command is simple: ./Grader [FLAGS]"
			echo "Here are all of the flag options:
		-i/--init 	*OPTIONAL FLAG* This flag should be set if this is your first time running the script. The script will attempt to auto-detect if init should be used.
		-v/--verbose 	*OPTIONAL FLAG* Sets verbose mode. In verbose mode, all actions on student files will be outputted to the terminal (including error messages). All operations are stored in the Logs directory, always.
		-o		Sets the test mode to stdio related tests. This mode will run the student program, feed it inputs, and check the output. This or -a flag are required. Both cannot be set.
		-a		Sets the test mode to interface based tests.
		-t		*OPTIONAL FLAG* Script will detect hardware, and attempt use threads to speed up the grading process.
		-f  [FILENAME]	*OPTIONAL FLAG* Specify a test file to use, if not set the script will default to a file named tests."
			exit 0
			;;
		-i|--init)
			init=true
			shift
			;;

		-v|--verbose)
			verbose=true
			shift
			;;
		-o)
			type_stdio=true
			shift
			;;
		-a)
			type_interface=true
			shift
			;;
		-t)
			threading=true
			shift
			;;
		-f)
			shift
			file=$1
			shift
			;;
		*)
			echo "Invalid command. Try: ./Grade.sh -h or ./Grade.sh --help"
			exit 0;
			;;
	esac
done

#Checking for the required software
if ! which g++ >/dev/null; then
	echo "Could not find g++, please install g++."
	exit 1

fi

#Make sure there is only 1 grading type
if $type_stdio && $type_interface; then
	echo "Cannot have -o and -a flags BOTH set. Exiting."
	exit 1
fi

#Attempting to detect if init() needs to be called
if $init; then
	init
elif ! -d ".grader";  then
	echo "Auto-detected that init() has never been run. Running init()"
	init
fi

#Start of the main script














