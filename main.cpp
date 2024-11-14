#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Matrix
{
    int a, b, c, d;
};

// Function to perform matrix multiplication
Matrix multiply(const Matrix &m1, const Matrix &m2)
{
    Matrix result;
    result.a = m1.a * m2.a + m1.b * m2.c;
    result.b = m1.a * m2.b + m1.b * m2.d;
    result.c = m1.c * m2.a + m1.d * m2.c;
    result.d = m1.c * m2.b + m1.d * m2.d;
    return result;
}

// Function to parse a matrix from a string
Matrix parseMatrix(const string &matrixStr)
{
    stringstream ss(matrixStr);
    int a, b, c, d;
    char temp;
    ss >> a >> temp >> b >> temp >> c >> temp >> d;
    return {a, b, c, d};
}

// Function to process the input expression and calculate the result
vector<Matrix> evaluateExpression(const string &expression)
{
    // cout << expression << endl;
    vector<Matrix> matrixArray;

    int i = 0;
    while (i < expression.size())
    {
        char ch = expression[i];
        // cout << i << " " << ch << endl;
        if (ch == '[')
        {
            // Start of a matrix, find the matrix and push to stack
            int start = i + 1;
            int end = expression.find(']', start);
            string matrixStr = expression.substr(start, end - start);
            // cout << matrixStr << endl;
            Matrix matrix = parseMatrix(matrixStr);
            matrixArray.push_back(matrix);
            i = end + 1;
        }
        else
        {
            i++;
        }
    }

    return matrixArray;
}

int main()
{
    // Input the matrix expression
    string expression;
    while (getline(cin, expression))
    {
        // Evaluate the expression and output the result
        vector<Matrix> matrixArray = evaluateExpression(expression);
        Matrix result = matrixArray[0];

        // cout << "saved" << endl;
        // cout << matrixArray.size() << endl;
        for (int i = 1; i < matrixArray.size(); i++){
            // cout << "[" << matrixArray[i].a << "," << matrixArray[i].b << "," << matrixArray[i].c << "," << matrixArray[i].d << "]" << endl;
            result = multiply(result, matrixArray[i]);
        }
        cout << "[" << result.a << "," << result.b << "," << result.c << "," << result.d << "]" << endl;
    }
    return 0;
}
