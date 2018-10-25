#!/bin/bash

mkfifo test_pipe
./tests < test_pipe | ./p_to_test >test_pipe

echo $test_pipe

rm test_pipe
