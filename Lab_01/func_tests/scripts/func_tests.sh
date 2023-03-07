#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

pos_tests=$(find "$(dirname "$0")/../data" -mindepth 1 | sort -t '\0' -n | grep -E '+pos_[0-9][0-9]_in.txt$')
pos_passed_ok=0
pos_passed_mem=0
pos_passed=0
pos_count=0
echo "START TESTING"
echo

for test in $pos_tests; do
    args=

    if ! [ -f "${test/in/out}" ]; then
        continue
    fi

    if [ -f "${test/in/args}" ]; then
        args=${test/in/args}
    fi

    ech=$(basename "$test")
    ((pos_count++))
    "$(dirname "$0")/pos_case.sh" "$test" "${test/in/out}" "$args"
    err=$?

    if [ $err -eq 0 ]; then
        echo -e "POS TEST $ech: ${GREEN}PASS${NC}"
        echo -e "POS TEST $ech: ${GREEN}MEMORY OK${NC}"
        ((pos_passed++))
        ((pos_passed_ok++))
        ((pos_passed_mem++))
    elif [ $err -eq 1 ]; then
        echo -e "POS TEST $ech: ${RED}FAIL${NC}"
        echo -e "POS TEST $ech: ${GREEN}MEMORY OK${NC}"
        ((pos_passed_mem++))
    elif [ $err -eq 2 ]; then
        echo -e "POS TEST $ech: ${GREEN}PASS${NC}"
        ((pos_passed_ok++))
        echo -e "POS TEST $ech: ${RED}MEMORY FAIL${NC}"
    elif [ $err -eq 3 ]; then
        echo -e "POS TEST $ech: $RED(FAIL)${NC}"
        echo -e "POS TEST $ech: ${RED}MEMORY FAIL${NC}"
    fi
done

echo "Positive tests: correct $pos_passed_ok of $pos_count; memory passed $pos_passed_mem of $pos_count"
echo "$((pos_passed * 100 / pos_count))% of positive tests PASSED"
echo

neg_tests=$(find "$(dirname "$0")/../data" -mindepth 1 | sort -t '\0' -n | grep -E '+neg_[0-9][0-9]_in.txt$')
neg_passed_ok=0
neg_passed_mem=0
neg_passed=0
neg_count=0

for test in $neg_tests; do
    args=

    if ! [ -f "${test/in/out}" ]; then
        continue
    fi

    if [ -f "${test/in/args}" ]; then
        args=${test/in/args}
    fi

    ech=$(basename "$test")
    ((neg_count++))
    "$(dirname "$0")/neg_case.sh" "$test" "${test/in/out}" "$args"
    err=$?

    if [ $err -eq 0 ]; then
        echo -e "NEG TEST $ech: ${GREEN}PASS${NC}"
        echo -e "NEG TEST $ech: ${GREEN}MEMORY OK${NC}"
        ((neg_passed++))
        ((neg_passed_ok++))
        ((neg_passed_mem++))
    elif [ $err -eq 1 ]; then
        echo -e "NEG TEST $ech: ${RED}FAIL${NC}"
        echo -e "NEG TEST $ech: ${GREEN}MEMORY OK${NC}"
        ((neg_passed_mem++))
    elif [ $err -eq 2 ]; then
        echo -e "NEG TEST $ech: ${GREEN}PASS${NC}"
        echo -e "NEG TEST $ech: ${RED}MEMORY FAIL${NC}"
        ((neg_passed_ok++))
    elif [ $err -eq 3 ]; then
        echo -e "NEG TEST $ech: ${RED}FAIL${NC}"
        echo -e "NEG TEST $ech: ${RED}MEMORY FAIL${NC}"
    fi
done

echo "Negative tests: correct $neg_passed_ok of $neg_count; memory passed $neg_passed_mem of $neg_count"
echo "$((neg_passed * 100 / neg_count))% of negative tests PASSED"

exit $((neg_count - neg_passed + pos_count - pos_passed))
