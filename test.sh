#!/bin/bash

mkfifo test_pipe

./tests | ./p_to_test

rm test_pipe
