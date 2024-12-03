import sys

def compare_files(goldenFile, answerFile):
    error = 0
    with open(goldenFile, 'r') as golden, open(answerFile, 'r') as answer:
        golden_lines = golden.readlines()
        answer_lines = answer.readlines()
    
    if len(golden_lines) != len(answer_lines):
        print("Error: The number of lines in the files do not match.")
        return
    
    for i, (g_line, a_line) in enumerate(zip(golden_lines, answer_lines), 1):
        if g_line.strip() != a_line.strip():
            error += 1
            print(f"Test case {i} differs:")
            print(f"golden.out: {g_line.strip()}")
            print(f"answer.out: {a_line.strip()}")

    if error == 0:
        print("All test cases passed.")
    else:
        print(f"{error} test cases failed.")
        print("test case fail might due to overflow")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(sys.argv)
        print("用法: python3 verify.py <goldenFile> <answerFile>")
        sys.exit(1)
    goldenFile = sys.argv[1]
    answerFile = sys.argv[2]
    compare_files(goldenFile, answerFile)
