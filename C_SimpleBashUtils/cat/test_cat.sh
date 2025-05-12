#!/bin/bash

#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

s21_cat="./s21_cat"
cat="cat"

tests=(
"tests_files/test_1_cat.txt"
"tests_files/test_2_cat.txt"
"tests_files/test_3_cat.txt"
"tests_files/test_4_cat.txt"
)

flags=(""
       "-b"
       "-e"
       "-n"
       "-s"
       "-t"
       "-v" 
       "-b -s" 
       "-e -n" 
       "-n -s -v"
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

        $s21_cat $TEST1 > result_s21_cat.txt
        $cat $TEST1 > result_cat.txt
        DIFF_RES="$(diff -s result_s21_cat.txt result_cat.txt)"
        if [ "$DIFF_RES" == "Files result_s21_cat.txt and result_cat.txt are identical" ]
            then
                (( SUCCESS++ ))
                echo "$COUNTER - SUCCESS $TEST1"
            else
                # echo "$TEST1" >> log.txt
                (( FAIL++ ))
                echo "$COUNTER - FAIL $TEST1"
        fi
        rm result_s21_cat.txt result_cat.txt
    done
done


printf "\n"
echo "TEST RESULT"
echo "$SUCCESS - SUCCESS"
echo "$FAIL - FAIL"
echo "TOTAL TESTS - $COUNTER"


# S21_CAT="./s21_cat"

# TEST_FILE="test.txt"
# STEST_FILE="stest.txt"
# OUTTEST_FILE="outtest.txt"

# SUCCESS=0
# TOTAL=0

# FLAGS=("" "-b" "-e" "-n" "-s" "-t" "-v" "-b -s" "-e -n" "-n -s -v")


# echo -e "Hello, world!\n\nThis\tis\ta\ttest.\nAnother line.\n\n\nEnd of file." > $TEST_FILE

# run_test() {
#   local flags=$1
#   ((TOTAL++))
#   echo "Testing: $S21_CAT $flags $TEST_FILE"

#   S21_OUTPUT=$($S21_CAT $flags $TEST_FILE)
#   CAT_OUTPUT=$(cat $flags $TEST_FILE)

#   echo $S21_OUTPUT > $STEST_FILE
#   echo $CAT_OUTPUT > $OUTTEST_FILE

#   if [ "$S21_OUTPUT" == "$CAT_OUTPUT" ]; then
#     echo "PASS"
#     ((SUCCESS++))
#   else
#     echo "FAIL"
#     echo "s21_cat output:"
#     echo "$S21_OUTPUT"
#     echo "cat output:"
#     echo "$CAT_OUTPUT"
#   fi
# }

# for flag in "${FLAGS[@]}"; do
#   run_test "$flag"
# done

# echo "Passed $SUCCESS out of $TOTAL tests."

# # rm $TEST_FILE
