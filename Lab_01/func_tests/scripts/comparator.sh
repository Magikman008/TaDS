#!/bin/bash

ERROR_WRONG_FILES=1
ERROR_FILES_DONT_EXIST=2
ERROR_NOT_EQUAL=4

if [ $# != 2 ]; then
    exit $ERROR_WRONG_FILES
fi

if ! [ -f "$1" ] || ! [ -f "$2" ]; then 
    exit $ERROR_FILES_DONT_EXIST
fi

if ! (cmp -s "$1" "$2") ; then
    exit $ERROR_NOT_EQUAL
fi

