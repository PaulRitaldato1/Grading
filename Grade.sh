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
	#echo $exstension
	if [[ $late == "late" ]]; then
			rtn=${str#*_*_*_*_}
		else
			rtn=${str#*_*_*_}
	fi
 # rtn=${rtn/%%(-[0-9]).cpp/.cpp}
  #before="$(awk -F. '{print $1}' <<< "${rtn}")"
	#rtn=${before%-+([0-9])}
  #rtnn="$rtn$extension"
  #echo "$rtn"
}

#declaring flag booleans & variables 
init=false
type_stdio=false
type_interface=false
separate=false
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
		-f  [FILENAME]	*OPTIONAL FLAG* Specify a test file to use, if not set the script will default to a file named tests.
    -c    Absolutely cleans the  system. Literally deletes everyting. For now it is used for debugging. Later on this will delete everything except log files, which will be zipped up.
    -s    Just separates student files, do nothing else."
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
		-f)
			shift
			file=$1
			shift
			;;
		-c|--clean)
			clean
			exit 0
			;;
    -s)
        separate=true
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

#Take all zipfiles in the Zip directory (There should only be one but this prevents a crash if there is more than one)
zipfile=(Zip/*.zip)

#only use the first zipfile in the directory
echo "Unzipping "${zipfile[0]}" " | tee .grader/Logs/script_run_log
unzip "${zipfile[0]}" -d Canvas >.grader/Logs/script_run_log

#for now this is a copy, for testing purposes. Final release will be a mv command
cp Zip/*.zip .grader/History/Zips
echo "################################################ END UNZIP LOG ################################################" >> .grader/Logs/script_run_log
echo -e "Moved the "${zipfile[0]}" file into .grader/History/Zips\n"


#create an array with all the files
filenames=(Canvas/*)

#heres where the magic happens bby

#effectively the number of student files NOT the number of students
arr_size=${#filenames[@]}

#this is set to the last possible directory name that will be created by these loops. If it exists then this has already been run, so skip it.
test="$(basename "${filenames[$((arr_size - 1))]}")"

#test if the files are already separated, if they are, skip this part
if [ ! -d "StudentsToGrade/$test" ]; then 
    echo "Creating student directories in StudentsToGrade/"
	  for ((i=0; i<$arr_size;)); do

		    offset=0
		    temp="$(basename "${filenames[$i]}")"
		    temp=${temp%%_*}

		    future=$temp
		    mkdir StudentsToGrade/"$future" && mkdir Results/"$future"
		    while [[ $temp == $future ]];
		    do

			      mv "${filenames[$((i + offset))]}" StudentsToGrade/"$future"
			      rename="$(basename "${filenames[$((i + offset))]}")"

			      #this function properly renames the files passed to it
			      correct_names "$rename"
			      mv StudentsToGrade/"$temp"/"$rename" StudentsToGrade/"$temp"/"$rtn"

			      offset=$((offset + 1))

			      future="$(basename "${filenames[$((i+offset))]}")"
			      future=${future%%_*}

		    done
		    Progress_bar $i $arr_size
		    i=$((i + offset)) 

	  done
	  Progress_bar $arr_size $arr_size

	echo "Finished creating student directories."

else
    echo -e "Student files have already been separated, skipping this process.\n"
fi

#if you just wanted to separate student files, script ends here
if $separate; then
    echo -e "Student files have been separated, exiting..."
    exit 0
fi


#Now compiling will start, this process is separate from the one above so that others can use this script(with the -s flag) to just separate student files and not compile/test.

dirs=(StudentsToGrade/*)
dir_size=${#dirs[@]}

threads=$(cat /proc/cpuinfo | awk '/^processor/{print $3}' | wc -l)

echo -e "\nStarting compilation..."
echo "Detected $threads threads on your CPU, finna use em all"
for base in $(seq 0 ${threads} ${dir_size}); do
	  for ((t=0; t<threads; ++t)); do

        #since the number of student files to be compiled is probably not evenly divied by your number of cores/threads, this breaks when everything is compiled
        if [ $((base+t)) -gt $dir_size ]; then
            break
        fi

        Progress_bar $((base + t)) $dir_size
        stu_dir="$(basename "${dirs[$((base + t))]}")"
        #start compiling everyones stuff. The & at the end of the command backgrounds the process. This allows multiple processes to be run in parallel. Ghetto threading yall!
		    g++ StudentsToGrade/"$stu_dir"/*.cpp -o StudentsToGrade/"$stu_dir"/"TEST$stu_dir" &>> .grader/Logs/compile_log &

        # $! gets the pid of the last backgrounded process, this will be used to wait for all processes to finish (the number of processes running at a time will be the number of threads your CPU has)
        pids="$pids $!"
	done

 #literally crashed my OS because i forgot to wait for the batch of processes to finish and i had like 700 compiler jobs running. Not the best way to parallelize but I didnt want to spend a ton of time of this. Fix it if you want.
 wait $pids

done
echo -e "Finished compiling. All errors, and general compiler output found in .grader/Logs/compile_log\n"
