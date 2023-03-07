#!/bin/bash

# name_file=$(find -maxdepth 1 -name "*.txt" | sort)
readarray arr < ./unique.txt
rm -rf ticksnums.txt
rm -rf compsnums.txt
for i in $(seq 1 10); do
    for j in "${arr[@]}"; do
        printf "11\n$j" > test.txt
        printf "0" >> test.txt
        ./app.exe <test.txt >tmp.txt
        grep "Ticks spent" tmp.txt > ticks.txt
        grep "Comparisons" tmp.txt > comps.txt

        grep -Eo "[0-9]*$" ticks.txt >>ticksnums.txt
        grep -Eo "[0-9]*$" comps.txt >>compsnums.txt
    done
done

rm -rf tmp.txt
rm -rf ticks.txt
rm -rf comps.txt
rm -rf test.txt
