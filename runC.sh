input="test_case.in"
output="answer.out"
golden="golden.out"

# input="test_by_python.in"
# num_of_test=100
# output="answer.out"
# golden="golden_by_python.out"
# python3 data.py $input $golden $num_of_test
# echo "test case generated"

rm -f a.out
gcc main.c
./a.out < $input > $output
python3 verify.py $golden $output