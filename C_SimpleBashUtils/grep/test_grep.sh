#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

s21_grep="./s21_grep"
grep="grep"

tests=(
"-e brrktbhm -e fy tests_files/test_1_grep.txt"
"r tests_files/test_1_grep.txt"
"R tests_files/test_1_grep.txt"
" s tests_files/test_1_grep.txt"
"'s' tests_files/test_1_grep.txt"
"r tests_files/test_1_grep.txt tests_files/test_2_grep.txt"
"-e min_rm_so -e rm_eo tests_files/test_2_grep.txt"
"'*' tests_files/test_2_grep.txt"
"rm tests_files/test_2_grep.txt"
"'-' tests_files/test_2_grep.txt tests_files/test_3_grep.txt"
"- tests_files/test_2_grep.txt tests_files/test_3_grep.txt"
"and tests_files/test_3_grep.txt"
"i tests_files/test_4_grep.txt"
"int tests_files/test_4_grep.txt"
"intel tests_files/test_4_grep.txt"
)
flags=(
    "-i"
    "-v"
    "-c"
    "-l"
    "-n"
)

printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${tests[@]}"
    do
        (( COUNTER++ ))
        TEST1="$var1 $var2"

        $s21_grep $TEST1 > result_s21_grep.txt
        $grep $TEST1 > result_grep.txt
        DIFF_RES="$(diff -s result_s21_grep.txt result_grep.txt)"
        if [ "$DIFF_RES" == "Files result_s21_grep.txt and result_grep.txt are identical" ]
            then
                (( SUCCESS++ ))
                echo "$COUNTER - SUCCESS $TEST1"
            else
                # echo "$TEST1" >> log.txt
                (( FAIL++ ))
                echo "$COUNTER - FAIL $TEST1"
        fi
        rm result_s21_grep.txt result_grep.txt
    done
done


printf "\n"
echo "TEST RESULT"
echo "$SUCCESS - SUCCESS"
echo "$FAIL - FAIL"
echo "TOTAL TESTS - $COUNTER"