#!/bin/bash

# name_file=$(find -maxdepth 1 -name "*.txt" | sort)
for i in $(seq 1 50); do
    ./app.exe < test.txt > tmp.txt
    grep "Ticks spent: " tmp.txt > tmp2.txt

    grep -Eo "[0-9]*$" tmp2.txt >> tmp3.txt
done
