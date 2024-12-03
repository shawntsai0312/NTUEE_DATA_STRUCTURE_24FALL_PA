#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_SIZE 1000 // Max size for input string and stacks
#define MAX_EXPR_SIZE 1000 // Maximum size of an expression

typedef struct {
    int a, b, c, d;
} Matrix;

void printMatrix(Matrix m) {
    printf("[%d,%d,%d,%d]\n", m.a, m.b, m.c, m.d);
}

// Custom stack for matrices
typedef struct {
    Matrix data[STACK_SIZE];
    int topIndex;
} MatrixStack;

void initMatrixStack(MatrixStack *stack) {
    stack->topIndex = -1;
}

void pushMatrix(MatrixStack *stack, Matrix m) {
    stack->data[++stack->topIndex] = m;
}

Matrix popMatrix(MatrixStack *stack) {
    return stack->data[stack->topIndex--];
}

Matrix topMatrix(MatrixStack *stack) {
    return stack->data[stack->topIndex];
}

int isMatrixStackEmpty(MatrixStack *stack) {
    return stack->topIndex == -1;
}

// Custom stack for operators
typedef struct {
    char data[STACK_SIZE];
    int topIndex;
} CharStack;

void initCharStack(CharStack *stack) {
    stack->topIndex = -1;
}

void pushChar(CharStack *stack, char c) {
    stack->data[++stack->topIndex] = c;
}

char popChar(CharStack *stack) {
    return stack->data[stack->topIndex--];
}

char topChar(CharStack *stack) {
    return stack->data[stack->topIndex];
}

int isCharStackEmpty(CharStack *stack) {
    return stack->topIndex == -1;
}

// Function to perform matrix multiplication
Matrix multiply(Matrix m1, Matrix m2) {
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
    sscanf(matrixStr, "%d,%d,%d,%d", &result.a, &result.b, &result.c, &result.d);
    return result;
}

// Function to evaluate the matrix expression
Matrix evaluateExpression(const char *expression) {
    MatrixStack matrixStack;
    CharStack operatorStack;

    initMatrixStack(&matrixStack);
    initCharStack(&operatorStack);

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
            pushMatrix(&matrixStack, matrix);
            i = end + 1;
        } else if (ch == '(' || ch == '*') {
            // Push the operator to the stack
            pushChar(&operatorStack, ch);
            i++;
        } else if (ch == ')') {
            // Perform multiplication until a '(' is encountered
            while (!isCharStackEmpty(&operatorStack) && topChar(&operatorStack) == '*') {
                popChar(&operatorStack);
                Matrix m2 = popMatrix(&matrixStack);
                Matrix m1 = popMatrix(&matrixStack);
                pushMatrix(&matrixStack, multiply(m1, m2));
            }
            // Pop the '('
            popChar(&operatorStack);
            i++;
        } else {
            i++;
        }
    }

    // Perform any remaining multiplications
    while (!isCharStackEmpty(&operatorStack)) {
        popChar(&operatorStack);
        Matrix m2 = popMatrix(&matrixStack);
        Matrix m1 = popMatrix(&matrixStack);
        pushMatrix(&matrixStack, multiply(m1, m2));
    }

    return popMatrix(&matrixStack);
}

int main() {
    // Input the matrix expression
    char expression[MAX_EXPR_SIZE];
    while (fgets(expression, MAX_EXPR_SIZE, stdin)) {
        // Remove trailing newline, if any
        expression[strcspn(expression, "\n")] = '\0';
        // Evaluate the expression and output the result
        Matrix result = evaluateExpression(expression);
        printMatrix(result);
    }
    return 0;
}
