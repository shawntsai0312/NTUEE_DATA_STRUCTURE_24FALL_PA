#include <iostream>
#include <cstring> // For strlen, strncpy, etc.

using namespace std;

#define STACK_SIZE 1000 // Max size for input string and stacks
#define MAX_EXPR_SIZE 1000 // Maximum size of an expression

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

// Function to parse a matrix from a C-style string
Matrix parseMatrix(const char *matrixStr, int length) {
    Matrix result;
    int a, b, c, d;
    sscanf(matrixStr, "%d,%d,%d,%d", &a, &b, &c, &d);
    result.a = a;
    result.b = b;
    result.c = c;
    result.d = d;
    return result;
}

// Function to evaluate the matrix expression
Matrix evaluateExpression(const char *expression) {
    MatrixStack matrixStack;
    CharStack operatorStack;

    int i = 0;
    int length = strlen(expression);

    while (i < length) {
        char ch = expression[i];

        if (ch == '[') {
            // Parse the matrix
            int start = i + 1;
            int end = start;
            while (expression[end] != ']') {
                end++;
            }
            char matrixStr[MAX_EXPR_SIZE];
            strncpy(matrixStr, expression + start, end - start);
            matrixStr[end - start] = '\0'; // Null-terminate the substring
            Matrix matrix = parseMatrix(matrixStr, end - start);
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
    char expression[MAX_EXPR_SIZE];
    while (cin.getline(expression, MAX_EXPR_SIZE)) {
        // Evaluate the expression and output the result
        Matrix result = evaluateExpression(expression);
        result.print();
    }
    return 0;
}
