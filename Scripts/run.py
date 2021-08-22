#! /usr/bin/python

from blessings import Terminal
from os import system

MAIN_CODE_BASE_NAME = "app"
MAIN_CODE_EXTENSION = "cpp"
MAIN_CODE_FILE = MAIN_CODE_BASE_NAME + '.' + MAIN_CODE_EXTENSION

# Initialise blessings module for colored output
term = Terminal()

# Function to execute command locally
def exec(cmd):
    res = system(cmd)
    return res == 0

def main():
    if not exec('./compile'):
        exit(1)

    test_at = 1
    while True:
        try:
            with open(f"in{test_at}", "r") as file:
                inData = file.read().strip()

            with open(f"out{test_at}", "r") as file:
                correctOutput = file.read().strip()

            ok = exec(f"./{MAIN_CODE_BASE_NAME} < in{test_at} > {MAIN_CODE_BASE_NAME}out{test_at}")
            if not ok:
                print(term.bold(term.red(f"[RTE] Run Time Error on Test {test_at}")))
                print(term.bold(term.red("Test Data:")))
                print(inData)
                exit(1)

            with open(f"{MAIN_CODE_BASE_NAME}out{test_at}", "r") as file:
                programOutput = file.read().strip()

            exec(f"rm {MAIN_CODE_BASE_NAME}out{test_at}")

            if correctOutput == programOutput:
                print(term.bold(term.green(f"[AC] Test {test_at}")))
            else:
                print(term.bold(term.red(f"[WA] Wrong Answer on Test {  test_at}")))
                print(term.bold(term.blue("Test Data:")))
                print(inData)
                print(term.bold(term.green("Expected Answer:")))
                print(correctOutput)
                print(term.bold(term.red("Your Answer:")))
                print(programOutput)
                exit(1)

            test_at += 1

        except Exception:
            test_at -= 1
            print(term.bold(term.green(f"[OK] {test_at} test cases")))
            break

    return 0

if __name__ == '__main__':
    main()