#!/bin/bash

name_file=$(find -maxdepth 1 -name "*.txt" | sort)
for i in $name_file; do

    ./app.exe <"$i" >tmp.txt
    grep "Ticks spent " tmp.txt >tmp2.txt

    echo $i >>tmp3.txt
    grep -Eo "[0-9]*$" tmp2.txt >>tmp3.txt
done
