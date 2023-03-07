#!/bin/bash

ERROR_ONLY_MEM_OK=1
ERROR_ONLY_TEST_OK=2
ERROR_NOTHING_OK=3
ERROR_TOO_LITTLE_PARAMS=4
ERROR_FILES_DONT_EXIST=5

if [ "$#" -lt 2 ]; then
    exit $ERROR_TOO_LITTLE_PARAMS
fi

if ! [ -f "$1" ] || ! [ -f "$2" ]; then
    exit $ERROR_FILES_DONT_EXIST
fi

args=

if [ -n "$3" ]; then
    if ! [ -f "$3" ]; then
        exit $ERROR_FILES_DONT_EXIST
    fi
    args=$(<"$3")
fi

if [ -n "${USE_VALGRIND}" ]; then
    valgrind --leak-check=full --leak-resolution=med --log-file="$(dirname "$0")/report.txt" --quiet "$(dirname "$0")/../../app.exe" "$args" <"$1" >"$(dirname "$0")/result.txt"

    if [ -z "$(cat "$(dirname "$0")/report.txt")" ]; then
        if ! [ "$?" ]; then
            exit $ERROR_ONLY_MEM_OK
        fi
    elif [ $? ]; then
        exit $ERROR_ONLY_TEST_OK
    else
        exit $ERROR_NOTHING_OK
    fi
else
    "$(dirname "$0")/../../app.exe" "$args" <"$1" >"$(dirname "$0")/result.txt"

    if ! [ "$?" ]; then
        exit $ERROR_ONLY_MEM_OK
    fi
fi
