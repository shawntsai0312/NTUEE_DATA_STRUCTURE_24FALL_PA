#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define STACK_SIZE 1000 // max of input string size

struct Matrix {
    int a, b, c, d;

    void print() {
        cout << "[" << a << "," << b << "," << c << "," << d << "]" << endl;
    }
};

// Custom stack for matrices
struct MatrixStack {
    Matrix data[STACK_SIZE];
    int topIndex = -1;

    void push(const Matrix &m) {
        data[++topIndex] = m;
    }

    Matrix pop() {
        return data[topIndex--];
    }

    Matrix top() {
        return data[topIndex];
    }

    bool isEmpty() {
        return topIndex == -1;
    }
};

// Custom stack for operators
struct CharStack {
    char data[STACK_SIZE];
    int topIndex = -1;

    void push(char c) {
        data[++topIndex] = c;
    }

    char pop() {
        return data[topIndex--];
    }

    char top() {
        return data[topIndex];
    }

    bool isEmpty() {
        return topIndex == -1;
    }
};

// Function to perform matrix multiplication
Matrix multiply(const Matrix &m1, const Matrix &m2) {
    Matrix result;
    result.a = m1.a * m2.a + m1.b * m2.c;
    result.b = m1.a * m2.b + m1.b * m2.d;
    result.c = m1.c * m2.a + m1.d * m2.c;
    result.d = m1.c * m2.b + m1.d * m2.d;
    return result;
}

// Function to parse a matrix from a string
Matrix parseMatrix(const string &matrixStr) {
    stringstream ss(matrixStr);
    int a, b, c, d;
    char temp;
    ss >> a >> temp >> b >> temp >> c >> temp >> d;
    return {a, b, c, d};
}

// Function to process the input expression and calculate the result using custom stacks
Matrix evaluateExpression(const string &expression) {
    MatrixStack matrixStack;   // Custom stack for matrices
    CharStack operatorStack;   // Custom stack for operators ('(' or '*')

    int i = 0;
    while (i < expression.size()) {
        char ch = expression[i];

        if (ch == '[') {
            // Parse the matrix
            int start = i + 1;
            int end = expression.find(']', start);
            string matrixStr = expression.substr(start, end - start);
            // cout << matrixStr << endl;
            Matrix matrix = parseMatrix(matrixStr);
            // matrix.print();
            matrixStack.push(matrix);
            i = end + 1;
        } else if (ch == '(' || ch == '*') {
            // Push the operator to the stack
            operatorStack.push(ch);
            i++;
        } else if (ch == ')') {
            // Perform multiplication until a '(' is encountered
            while (!operatorStack.isEmpty() && operatorStack.top() == '*') {
                operatorStack.pop();
                Matrix m2 = matrixStack.pop();
                Matrix m1 = matrixStack.pop();
                matrixStack.push(multiply(m1, m2));
            }
            // Pop the '('
            operatorStack.pop();
            i++;
        } else {
            i++;
        }
    }

    // Perform any remaining multiplications
    while (!operatorStack.isEmpty()) {
        operatorStack.pop();
        Matrix m2 = matrixStack.pop();
        Matrix m1 = matrixStack.pop();
        matrixStack.push(multiply(m1, m2));
    }

    return matrixStack.pop();
}

int main() {
    // Input the matrix expression
    string expression;
    while (getline(cin, expression)) {
        // Evaluate the expression and output the result
        Matrix result = evaluateExpression(expression);
        result.print();
    }
    return 0;
}
