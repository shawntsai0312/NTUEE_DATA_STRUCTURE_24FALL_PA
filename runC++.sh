# input="test_case.in"
# output="answer.out"
# golden="golden.out"

input="test_by_python.in"
num_of_test=20
output="answer.out"
golden="golden_by_python.out"

python3 data.py $input $golden $num_of_test
echo "test case generated"
rm -f a.out
g++ main.cpp
./a.out < $input > $output
python3 verify.py $golden $output