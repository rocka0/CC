#! /usr/bin/python

from blessings import Terminal
from time import time
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

# Compile main code file
def main():

    st = time()
    executed = exec(f"g++ -std=c++17 -O2 {MAIN_CODE_FILE} -o {MAIN_CODE_BASE_NAME}")
    et = time()

    if not executed:
        print(term.bold(term.red("[FAIL] Compilation failed")))
        exit(1)

    print(term.bold(term.green("[OK] Compiled successfully")))
    delta = str(round(et-st, 3)) + 's'
    print(term.blue("Compile Time: "), term.bold(term.green((delta))))

    return 0

if __name__ == '__main__':
    main()