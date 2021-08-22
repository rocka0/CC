#! /usr/bin/python

from subprocess import run
from blessings import Terminal
from time import time
from os import system

MAIN_CODE_BASE_NAME = "app"
MAIN_CODE_EXTENSION = "cpp"
MAIN_CODE_FILE = MAIN_CODE_BASE_NAME + '.' + MAIN_CODE_EXTENSION

# Initialise blessings module for colored output
term = Terminal()

# Function to execute command locally
def exec(cmd, cwd="."):
    try:
        res = run(cmd, cwd=cwd, capture_output=True, check=True)
        return (True, res.stdout.decode('utf-8'))
    except:
        res = run(cmd, cwd=cwd, capture_output=True)
        return (False, res.stderr.decode('utf-8'))

# Compile main code file
def compile():
    st = time()
    executed, res = exec(["g++", "-std=c++17", "-O2", MAIN_CODE_FILE, "-o", MAIN_CODE_BASE_NAME])
    et = time()
    if not executed:
        print(term.bold(term.red("[FAIL] Compilation failed")))
        print(term.red("Compile Error:\n"), res)
        exit(0)
    print(term.bold(term.green("[OK] Compiled successfully")))
    delta = str(round(et-st, 3)) + 's'
    print(term.blue("Compile Time: "), term.bold(term.green((delta))))

def main():
    compile()
    test_at = 1
    while True:
        try:
            with open(f"in{test_at}", "r") as file:
                inData = file.read()
            ok = system(f"./{MAIN_CODE_BASE_NAME} < in{test_at} > {MAIN_CODE_BASE_NAME}out{test_at}")
            if(ok != 0):
                print(term.bold(term.red(f"[RTE] Run Time Error on Test {test_at}")))
                print(term.bold(term.red("Test Data:")))
                print(inData)
                exit(0)
            with open(f"out{test_at}", "r") as file:
                correctOutput = file.read().strip()
            with open(f"{MAIN_CODE_BASE_NAME}out{test_at}", "r") as file:
                programOutput = file.read().strip()
            system(f"rm {MAIN_CODE_BASE_NAME}out{test_at}")
            if correctOutput == programOutput:
                print(term.bold(term.green(f"[AC] Test {test_at}")))
            else:
                print(term.bold(term.red(f"[WA] Wrong Answer on Test {  test_at}")))
                print(term.bold(term.green("Expected Answer:")))
                print(correctOutput)
                print(term.bold(term.red("Your Answer:")))
                print(programOutput)
                exit(0)
            test_at += 1
        except Exception:
            test_at -= 1
            print(term.bold(term.green(f"[OK] {test_at}/{test_at} test cases")))
            break

    return 0

if __name__ == '__main__':
    main()