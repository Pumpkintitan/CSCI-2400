#! /bin/bash
## Clears existing ./tsh_test.txt file if it exists
echo "" > ./tsh_test.txt
## Loops through all 16 tests for user-created ./tsh and
## stores the output in local ./tsh_test.txt file
for I in "01" "02" "03" "04" "05" "06" "07" "08" "09" "10" "11" "12" "13" "14" "15" "16"; do
    echo "make test$I >> ./tsh_test.txt"
    make test$I >> ./tsh_test.txt
done