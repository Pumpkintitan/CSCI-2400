#! /bin/bash
## Clears existing ./tshref_test.txt file if it exists
echo "" > ./tshref_test.txt
## Loops through all 16 tests for given reference ./tshref and
## stores the output in local ./tshref_test.txt file
for I in "01" "02" "03" "04" "05" "06" "07" "08" "09" "10" "11" "12" "13" "14" "15" "16"; do
    echo "make rtest$I >> ./tshref_test.txt"
    make rtest$I >> ./tshref_test.txt
done