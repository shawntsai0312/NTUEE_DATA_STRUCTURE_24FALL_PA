[](#Programming-Assignment "Programming-Assignment")Programming Assignment
--------------------------------------------------------------------------

### [](#Update "Update")Update

**2024/11/23:**  
Output format:  
And print out your result.

**Test:**  
The test time limit is 1 min per test case.

**2024/11/17:**  
Test case 2 input:

    ([1,0,2,1]*[1,2,0,1])*([2,1,1,0]*[1,1,1,2]) (old)
    (([1,0,2,1]*[1,2,0,1])*([2,1,1,0]*[1,1,1,2])) (new)
    

Input format:  
ai∈N, where ai is the element in the input matrix (new)  
Output format:  
ai≤231−1, where ai is the element in the output matrix (new)

### [](#Description "Description")Description

In this problem, you need to write a program to solve 2×2 matrix multiplication. Following are some rules:

1.  A matrix A\=\[a1a2a3a4\] is represented as \[a1,a2,a3,a4\] in this problem.
2.  The "\*" is matrix multiplication operator.
3.  You have to calculate the matrix multiplication inside the brackets first.

### [](#Submission "Submission")Submission

You should write a C/C++ program named main.c or main.cpp and anything you need. Place all the files in the same folder, and name the folder "studentID" with lower case. Compress the folder into a .zip file and submit to NTUCOOL. There is a 10% deduction for wrong format. Following is the directory example. The due time is 2024/12/05 9:10 AM. No late submission.

studentID/  
|–\- main.c or main.cpp  
└–\- other files if needed

### [](#Compile "Compile")Compile

We will compile your main.c or main.cpp file with g++(7.5.0) in Ubuntu 22.04.5 LTS as following.

    g++ main.c
    

or

    g++ main.cpp
    

### [](#Test "Test")Test

We will test your program in Ubuntu 22.04.5 LTS as following. The test time limit is 1 min per test case.(2024/11/23 update)

    ./a.out < test_case.in
    

### [](#Grading "Grading")Grading

*   50% for correct program design
    *   20% for correct design stack
    *   20% for correct design algorithm
    *   10% for reading the input correctly
*   50% for correct result
    *   2% × 25 test cases
*   Full marks will be awarded if all test cases are correct.

### [](#Policy "Policy")Policy

*   Only C/C++ are accepted.
*   Any LLM(e.g. chatGPT) is prohibited.
*   You can use C/C++ standard library except STL.

### [](#Input-format "Input-format")Input format

The input contains a string s with only "0-9\*,()\[\]". Following are some constraints:

*   0<s.length() <1000
*   All test cases are valid
*   Each "\*" will always be paired with a pair of brackets
*   ai∈N, where ai is the element in the input matrix (2024/11/17 update)

### [](#Output-format "Output-format")Output format

The output is the martix representation in this problem, consisting of 4 numbers separated by a comma enclosed within square brackets. And print out your result.(2024/11/23 update)

*   ai≤231−1, where ai is the element in the output matrix (2024/11/17 update)

### [](#Hint "Hint")Hint

*   Use stack to handle the brackets

### [](#Test-case "Test-case")Test case

Input

    (([1,1,1,1]*[1,0,0,1])*[1,0,0,1])
    

Explaination

((\[1111\]×\[1001\])×\[1001\])  
\=(\[1111\]×\[1001\])

Output

    [1,1,1,1]
    

Explaination

\[1111\]

Input (2024/11/17 update)

    (([1,0,2,1]*[1,2,0,1])*([2,1,1,0]*[1,1,1,2]))
    

Output

    [5,6,11,13]
    

### [](#Contact "Contact")Contact

If you have any questions, please email TA 廖韋凱.  
Email address: [r12921a23@ntu.edu.tw](mailto:r12921a23@ntu.edu.tw)