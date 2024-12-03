import random
import sys

# 生成随机矩阵
def generate_matrix():
    return [random.randint(0, 9) for _ in range(4)]

# 格式化矩阵
def format_matrix(matrix):
    return f"[{','.join(map(str, matrix))}]"

# 生成随机嵌套表达式
def generate_random_expression(matrices):
    expr = [format_matrix(mat) for mat in matrices]
    while len(expr) > 1:
        idx = random.randint(0, len(expr) - 2)
        new_expr = f"({expr[idx]}*{expr[idx + 1]})"
        expr = expr[:idx] + [new_expr] + expr[idx + 2:]
    return expr[0]

# 矩阵乘法实现
def multiply(mA, mB):
    return [
        mA[0]*mB[0] + mA[1]*mB[2],
        mA[0]*mB[1] + mA[1]*mB[3],
        mA[2]*mB[0] + mA[3]*mB[2],
        mA[2]*mB[1] + mA[3]*mB[3],
    ]

# 解析表达式并计算结果
def evaluate_expression(expr):
    operand_stack = []  # 用于存储矩阵
    operator_stack = []  # 用于存储操作符和括号

    i = 0
    while i < len(expr):
        if expr[i] == '(':
            operator_stack.append('(')
            i += 1
        elif expr[i] == ')':
            # 遇到右括号时，执行栈顶操作，直到遇到左括号
            while operator_stack and operator_stack[-1] != '(':
                perform_operation(operand_stack, operator_stack)
            if not operator_stack or operator_stack[-1] != '(':
                raise ValueError("Invalid expression: unmatched ')' or insufficient operators")
            operator_stack.pop()  # 弹出左括号
            i += 1
        elif expr[i] == '*':
            operator_stack.append('*')
            i += 1
        elif expr[i] == '[':
            # 解析矩阵
            j = i + 1
            while j < len(expr) and expr[j] != ']':
                j += 1
            if j == len(expr) or expr[j] != ']':
                raise ValueError(f"Unmatched '[' in expression: {expr}")
            matrix = list(map(int, expr[i+1:j].split(',')))
            operand_stack.append(matrix)
            i = j + 1
        else:
            i += 1

    # 处理剩余操作符
    while operator_stack:
        perform_operation(operand_stack, operator_stack)

    if len(operand_stack) != 1:
        raise ValueError("Invalid expression: unmatched operations or extra operands")
    return operand_stack[0]

def perform_operation(operand_stack, operator_stack):
    """执行一次操作符栈的运算"""
    if len(operand_stack) < 2:
        raise ValueError("Invalid expression: insufficient operands for operation")
    if not operator_stack:
        raise ValueError("Invalid expression: no operators to apply")
    operator = operator_stack.pop()
    if operator == '*':
        b = operand_stack.pop()
        a = operand_stack.pop()
        operand_stack.append(multiply(a, b))


# 写入测试输入文件
def write_test_input(inputFile, num_tests):
    with open(inputFile, 'w') as f:
        for _ in range(num_tests):
            num_matrices = random.randint(2, 10)
            matrices = [generate_matrix() for _ in range(num_matrices)]
            expr = generate_random_expression(matrices)
            f.write(expr + '\n')

# 写入Golden输出文件
def write_golden_output(inputFile, outputFile):
    with open(inputFile, 'r') as f_in, open(outputFile, 'w') as f_out:
        for line in f_in:
            line = line.strip()
            try:
                result = evaluate_expression(line)
                f_out.write(f"[{','.join(map(str, result))}]\n")
            except ValueError as e:
                print(f"Error processing line: {line}\n{e}")
                f_out.write("Error\n")

# 主函数
if __name__ == "__main__":
    inputFile = sys.argv[1] if len(sys.argv) > 1 else "test_by_python.in"
    outputFile = sys.argv[2] if len(sys.argv) > 2 else "golden_by_python.out"
    num_tests = int(sys.argv[3]) if len(sys.argv) > 3 else 10

    write_test_input(inputFile, num_tests)
    write_golden_output(inputFile, outputFile)
    print(f"Generated {num_tests} test cases in '{inputFile}' and golden results in '{outputFile}'")
