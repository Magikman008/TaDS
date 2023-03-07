#!/bin/bash

count=10000

rm -rf result.txt
rm -rf result2.txt
rm -rf result3.txt

fun() {

    for ((i = 0; i < count; i++)); do
        ./app.exe <in.txt >>result.txt
    done

    grep -o -E "Таблица отсортирована за [0-9]+ микросекунд" result.txt >>result2.txt
    grep -o -E " [0-9]+ " result2.txt >>result3.txt
    awk '{ sum += $1; count += 1 } END { print sum/count }' result3.txt

    rm -rf result.txt
    rm -rf result2.txt
    rm -rf result3.txt
}

echo "4" >in.txt

fun

echo "5" >in.txt

fun

echo "6" >in.txt

fun

echo "7" >in.txt

fun

rm -rf in.txt
