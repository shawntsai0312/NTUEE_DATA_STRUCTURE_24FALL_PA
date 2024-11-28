#include <iostream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

struct Matrix {
    int a, b, c, d;
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

// Function to process the input expression and calculate the result using a stack
Matrix evaluateExpression(const string &expression) {
    stack<Matrix> matrixStack;  // Stack to store matrices
    stack<char> operatorStack; // Stack to store operators ('(' or '*')

    int i = 0;
    while (i < expression.size()) {
        char ch = expression[i];

        if (ch == '[') {
            // Parse the matrix
            int start = i + 1;
            int end = expression.find(']', start);
            string matrixStr = expression.substr(start, end - start);
            Matrix matrix = parseMatrix(matrixStr);
            matrixStack.push(matrix);
            i = end + 1;
        } else if (ch == '(' || ch == '*') {
            // Push the operator to the stack
            operatorStack.push(ch);
            i++;
        } else if (ch == ')') {
            // Perform multiplication until a '(' is encountered
            while (!operatorStack.empty() && operatorStack.top() == '*') {
                operatorStack.pop();
                Matrix m2 = matrixStack.top();
                matrixStack.pop();
                Matrix m1 = matrixStack.top();
                matrixStack.pop();
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
    while (!operatorStack.empty()) {
        operatorStack.pop();
        Matrix m2 = matrixStack.top();
        matrixStack.pop();
        Matrix m1 = matrixStack.top();
        matrixStack.pop();
        matrixStack.push(multiply(m1, m2));
    }

    return matrixStack.top();
}

int main() {
    // Input the matrix expression
    string expression;
    while (getline(cin, expression)) {
        // Evaluate the expression and output the result
        Matrix result = evaluateExpression(expression);
        cout << "[" << result.a << "," << result.b << "," << result.c << "," << result.d << "]" << endl;
    }
    return 0;
}
