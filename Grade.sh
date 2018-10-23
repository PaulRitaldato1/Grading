#!/bin/bash

#function definitions will go here

#create file structure for t
init(){
  mkdir Zip
  	cp *.zip Zip
  mkdir Results
  mkdir Canvas
  mkdir StudentsToGrade
  mkdir .grader
  	mkdir .grader/Logs
	     touch .grader/Logs/runtime_error_log
	     touch .grader/Logs/compile_log
	     touch .grader/Logs/test_log
	     touch .grader/Logs/script_run_log

    mkdir .grader/History
       mkdir .grader/History/Zips
       mkdir .grader/History/Logs
	   mkdir .grader/History/Results
}

clean(){
	rm -r Zip Results Canvas .grader StudentsToGrade
}


function Progress_bar {
# Process data
    let _progress=(${1}*100/${2}*100)/100
    let _done=(${_progress}*4)/10
    let _left=40-$_done
# Build progressbar string lengths
    _fill=$(printf "%${_done}s")
    _empty=$(printf "%${_left}s")


printf "\rProgress : [${_fill// /\#}${_empty// /-}] ${_progress}%%"

if [ $1 -eq $2 ]; then
	printf "\n"
fi
}

correct_names(){
	shopt -s extglob
	str=$1
	late="$(awk -F_ '{print $2}' <<< "${str}")"
	exstension=".$(awk -F. '{print $2}' <<< "${str}")"
	echo $exstension
	if [[ $late == "late" ]]; then
			rtn=${str#*_*_*_*_}
		else
			rtn=${str#*_*_*_}
	fi

	rtn=${rtn%-.cpp/.cpp}
}

#declaring flag booleans & variables 
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
		-c|--clean)
			clean
			exit 0
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

#Check if unzip is installed
if ! which unzip >/dev/null; then
	  echo "Could not find unzip, please install unzip."
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
elif [ ! -d ".grader" ];  then
	echo -e "Auto-detected that init() has never been run. Running init()\n"
	init
fi

#Start of the main script

#first thangs first, we have to separate all the students files so that each student has a directory with all their files.

#unzip the file then move the zip into history
echo "################################################ UNZIP LOG ################################################" >> .grader/Logs/script_run_log
zipfile=(Zip/*.zip)
echo "Unzipping "${zipfile[0]}" " | tee .grader/Logs/script_run_log
unzip "${zipfile[0]}" -d Canvas >.grader/Logs/script_run_log
cp Zip/*.zip .grader/History/Zips
echo "################################################ END UNZIP LOG ################################################" >> .grader/Logs/script_run_log
echo -e "Moved the "${zipfile[0]}" file into .grader/History/Zips\n"
#exit 0
#create an array with all the files
filenames=(Canvas/*)
#echo "${filenames[2]}"
#heres where the magic happens bby
echo "Creating student directories in StudentsToGrade/"
arr_size=${#filenames[@]}
for ((i=0; i<$arr_size;)); do

	offset=0
	temp="$(basename "${filenames[$i]}")"
	temp=${temp%%_*}

	future=$temp
	mkdir StudentsToGrade/"$future" && mkdir Results/"$future"
	while [[ $temp == $future ]];
	do

		mv "${filenames[$((i + offset))]}" StudentsToGrade/"$future"
		rename="StudentsToGrade/"$future"/$(basename "${filenames[$((i + offset))]}" )"
		echo $rename
		#this function properly renames the files passed to it
		correct_names "$rename"
		echo $rtn
		#mv "${filenames[$((i + offset))]}" StudentsToGrade/"$temp"/

		
		offset=$((offset + 1))

		future="$(basename "${filenames[$((i+offset))]}")"
		future=${future%%_*}

	done
	#Progress_bar $i $arr_size
	i=$((i + offset)) 

done
#Progress_bar $arr_size $arr_size
echo "Finished creating student directories."

#Now compiling will start, this process is separate from the one above so that others can use this (with the -s flag) to just separate student files.

	#if g++ StudentsToGrade/"${temp}"/*.cpp -o StudentsToGrade/"$temp"/"TEST$temp" &>> .grader/Logs/compile_log; then
	#	echo -e "$temp's FILE SUCCESSFULLY COMPILED\n" >> .grader/Logs/compile_log
	#else
	#	echo -e "$temp's FILE FAILED TO COMPILE\n" >> .grader/Logs/compile_log	
	#fi 