#!/bin/bash

mkfifo test_pipe
< test_pipe ./tests | ./p_to_test >test_pipe


rm test_pipe
