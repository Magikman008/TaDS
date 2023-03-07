#!/bin/bash

./build_debug.sh
rm -rf main.gcda
./func_tests/scripts/func_tests.sh
echo
gcov -r main.c