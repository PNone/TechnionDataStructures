#!/bin/bash

export MATAM_TESTER_TEST_TIMEOUT=25
export MATAM_TESTER_VALGRIND_TIMEOUT=25
export MATAM_TESTER_EXPORT_TEMP_REPORT=1
git submodule update --init --recursive --remote
g++ -DNDEBUG -std=c++11 -Wall -o test.out *.cpp
python3 ./MatamGenericTester/run_tests.py ./TechnionDataStructures/HW2/tests/custom_tests.json ./test.out