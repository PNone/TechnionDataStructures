#!/bin/bash

export MATAM_TESTER_TEST_TIMEOUT=50
export MATAM_TESTER_VALGRIND_TIMEOUT=60
export MATAM_TESTER_RUN_MULTI_THREADED=1
git submodule update --init --recursive --remote
g++ -DNDEBUG -std=c++11 -Wall -o test.out *.cpp
python3 ./MatamGenericTester/run_tests.py ./TechnionDataStructures/HW1/tests/custom_tests.json ./test.out