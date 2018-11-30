#!/bin/bash

#function definitions will go here

#create directory/file structure for grading
init(){
  mkdir Zip
  	mv *.zip Zip
  mkdir Results
#	touch Results/results.csv
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

Progress_bar() {
# Process data
    let _progress=(${1}*100/${2}*100)/100
    let _done=(${_progress}*4)/10
    let _left=40-$_done
# Build progressbar string lengths
    _fill=$(printf "%${_done}s")
    _empty=$(printf "%${_left}s")


printf "\rProgress : [${_fill// /\#}${_empty// /-}] ${_progress}%%"

#newline after bar reaches 100%
if [ $1 -eq $2 ]; then
	printf "\n"
fi
}

correct_names(){
  #pattern matching in bash
	  shopt -s extglob

    #see if the assignment was marked as late
	  late="$(awk -F_ '{print $2}' <<< "${1}")"

    #if the assignment was late then the pattern match needs to account for an extra underscore
    #After this if/else rtn will be the original file name (before canvas nonesense), unless it was a resubmit in which it will be in a form like this: filename-1.cpp. 
	#That -1 needs to be cut off
	  if [[ $late == "late" ]]; then
			  rtn=${1#*_*_*_*_}
		else
			  rtn=${1#*_*_*_}
	  fi

    #get the extension of the file for later use
	extension=".${rtn##*.}"

    #rtn will now be everything before the . so filename-1.cpp -> filename-1
    rtn="${rtn%.*}"

    #cut off any combination of -#
    #this might not work on double digit resubmits. Havent tested it but it should be fine unless some student is REALLY extra
    rtn=${rtn/%-+([0-9])}

    #tack on the file extension again
	rtn="$rtn$extension"
}

#declaring flag booleans & variables 
init=false
separate=3
t_file="test.sh"

#parse input, grab flags
while test $# -gt 0; do
	case "$1" in
		-h|--help)
			echo "Welcome to the Grader script!"
			echo "The format of this command is simple: ./Grader [FLAGS]"
			echo "Here are all of the flag options:
	-i/--init 	*OPTIONAL FLAG* This flag should be set if this is your first time running the script. The script will attempt to auto-detect if init should be used.
	-f  [FILENAME]	*OPTIONAL FLAG* Specify a test file to use, if not set the script will default to a file named tests.
    -Rsc    Absolutely cleans the  system. Literally deletes everyting. For now it is used for debugging. Later on this will delete everything except log files, which will be zipped up.
    -s  [STAGE_NUM]  Choose up to what stage you want the script to run to. The stages are as follows: 1. Separate and rename files, 2. Compile, 3. Test"
			exit 0
			;;
		-i|--init)
			init=true
			shift
			;;
		-f)
			shift
			t_file=$1
			shift
			;;
		-Rsc)
			clean
			exit 0
			;;
		-s)
			shift
			if [ $1 -gt 3 ] || [ $1 -lt 0 ]; then
				echo -e "Choose a valid value please\n"
				exit 1
			fi
			separate=$1
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

#Check if unzip is installed
if ! which unzip >/dev/null; then
	  echo "Could not find unzip, please install unzip."
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

#Take all zipfiles in the Zip directory (There should only be one but this prevents a crash if there is more than one)
zipfile=(Zip/*.zip)

#only use the first zipfile in the directory
echo "Unzipping "${zipfile[0]}" " | tee .grader/Logs/script_run_log
if ! unzip "${zipfile[0]}" -d Canvas >.grader/Logs/script_run_log; then
    exit 1
fi

#for now this is a copy, for testing purposes. Final release will be a mv command
mv Zip/*.zip .grader/History/Zips
echo "################################################ END UNZIP LOG ################################################" >> .grader/Logs/script_run_log 
echo -e "Moved the "${zipfile[0]}" file into .grader/History/Zips\n" | tee .grader/Logs/script_run_log

######################################################## Stage 1: Separating and Renaming ########################################################
#create an array with all the files
filenames=(Canvas/*)

#heres where the magic happens bby

#effectively the number of student files NOT the number of students
arr_size=${#filenames[@]}

#this is set to the last possible directory name that will be created by these loops. If it exists then this has already been run, so skip it.
test="$(basename "${filenames[$((arr_size - 1))]}")"
test=${test%%_*}

#test if the files are already separated, if they are, skip this part
if [ ! -d "StudentsToGrade/$test" ] && [ $separate -ge 1 ]; then
    echo "Creating student directories in StudentsToGrade/"

	#I cannot use 'seq' because students may have turned in different numbers of files, making the step sizes variable. Instead 'i' will be changed
	#to each individual students step size. This is done with the inner loop
	  for ((i=0; i<$arr_size;)); do

        #logic might be hard to follow in these loops so heres the rundown
        #Outer loop: gets the first file belonging to one student. The outer loop should run once for every student NOT for every file
        #Inner loop: moves all files with the name found in the outer loop. Runs for every file belonging to ONE student, then updates a step size

        #the offset will be used to update the iterator for the outer loop, it will represent how many files belong to a single student
		    offset=0

        #basename removes the path from a given filename in the filenames array.
		    temp="$(basename "${filenames[$i]}")"
        #cuts off everything after the first _ which just leaves the students name in temp
		    temp=${temp%%_*}

        #future is used to "look in the future" and find all files belonging to a single student
		    future=$temp

        #make a directory for every student
		    mkdir StudentsToGrade/"$future"

			#many ways i could have implemented the actual test script but this was just easiest. Not efficient at all. Later ill change this so it doesnt need to be copied at all
			cp $t_file StudentsToGrade/"$future"/

        #find all files that belong to a single student
		    while [[ $temp == $future ]];
		    do

            #move the ugly canvas file into the students directory
			      mv "${filenames[$((i + offset))]}" StudentsToGrade/"$future"

            #get the students filename, probably couldve reused some variable but meh, making one is more clear on my intent
			      rename="$(basename "${filenames[$((i + offset))]}")"

			      #this function properly renames the files to there original name reversing the mess canvas does to filenames. Returns the corrected filename in the rtn variable.
			      correct_names "$rename"
			      mv StudentsToGrade/"$temp"/"$rename" StudentsToGrade/"$temp"/"$rtn"

            #increment offset for every file found with same students name
			      offset=$((offset + 1))

            #update future to be the next file in the directory
			      future="$(basename "${filenames[$((i+offset))]}")"
			      future=${future%%_*}

		    done
        #yay for progress bar animations partially found online
		    Progress_bar $i $arr_size

        #make outer loop skip over what the inner loop did
		    i=$((i + offset))

	  done
	  Progress_bar $arr_size $arr_size

	echo "Finished creating student directories."

else
    echo -e "Student files have already been separated, skipping this process.\n"
fi



######################################################## Stage 2: Compiling ########################################################


if [ $separate -ge 2 ]; then

    #Now compiling will start, this process is separate from the one above so that others can use this script(with the -s flag) to just separate student files and not compile/test.
    dirs=(StudentsToGrade/*)
    dir_size=${#dirs[@]}

    #get number of threads your cpu has
    threads=$(cat /proc/cpuinfo | awk '/^processor/{print $3}' | wc -l)
    echo -e "\nStarting compilation..."
    echo "Detected $threads threads on your CPU, finna use em all."

    #another nested loop
    #Since now we know what step sizes will be made (number of threads) the seq command can be used. It increments in steps of size $threads up until $dir_size
    #Outer loop: Move the compiling batch in steps of $threads through all student directories
    #Inner loop: Create the actualy threads
    for base in $(seq 0 ${threads} ${dir_size}); do
	      for ((t=0; t<threads; ++t)); do

            #since the number of student files to be compiled is probably not evenly divied by your number of cores/threads, this breaks when everything is compiled
            if [ $((base+t)) -gt $dir_size ]; then
                break
            fi

            Progress_bar $((base + t)) $dir_size
            stu_dir="$(basename "${dirs[$((base + t))]}")"
            #start compiling everyones stuff. The & at the end of the command backgrounds the process. This allows multiple processes to be run in parallel. Ghetto threading yall!
		        g++ -std=c++17 StudentsToGrade/"$stu_dir"/*.cpp -o StudentsToGrade/"$stu_dir"/"TEST"  &>> .grader/Logs/compile_log &
         
			if [ $? != 0 ]; then
                echo "$stu_dir failed to compile" >> StudentsToGrade/"$stu_dir"/compile_fail.txt
            fi
            echo "$stu_dir" >> .grader/Logs/compile_log

            # $! gets the pid of the last backgrounded process, this will be used to wait for all processes to finish (the number of processes running at a time will be the number of threads your CPU has)
            pids="$pids $!"
	      done

        #literally crashed my OS because i forgot to wait for the batch of processes to finish and i had like 700 compiler jobs running. Not the best way to parallelize but I didnt want to spend a ton of time of this. Fix it if you want.
        wait $pids

    done
    echo -e "Finished compiling. All errors, and general compiler output found in .grader/Logs/compile_log\n"
fi

######################################################## Stage 3: Testing and Reporting ########################################################
if [ $separate -eq 3 ]; then

	dirs=(StudentsToGrade/*)
	dir_size=${#dirs[@]}
	for index in $(seq 0 $((dir_size-1))); do
		Progress_bar $((index)) $dir_size
		stu_name="$(basename "${dirs[$index]}")"

		#call the test script, it takes the students name as a cli arg
		#echo "${dirs[$index]}"
		"${dirs[$index]}"/test.sh "$stu_name"
	done
	
fi
#clean
