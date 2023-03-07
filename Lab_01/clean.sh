#!/bin/bash

shopt -s extglob
rm -rf !(data|scripts|func_tests|*.sh|*.c|*.h)
mapfile -t files < <(find "$PWD" -type f | grep -Ev '(pos|neg)_[0-9][0-9]_(in|out|args)' | grep -E '\.txt')

for file in "${files[@]}"; do
    rm -rf "$file"
done