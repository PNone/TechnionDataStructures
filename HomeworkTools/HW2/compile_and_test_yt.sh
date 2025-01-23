#!/bin/bash

export MATAM_TESTER_TEST_TIMEOUT=250
export MATAM_TESTER_VALGRIND_TIMEOUT=250
export MATAM_TESTER_EXPORT_TEMP_REPORT=1
g++ -DNDEBUG -std=c++11 -Wall -o test.out *.cpp
python3 ./MatamGenericTester/run_tests.py ./TechnionDataStructures/HW2/YTtests/custom_tests.json ./test.out