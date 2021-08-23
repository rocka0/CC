#! /usr/bin/python

from os import system
from blessings import Terminal

MAIN_CODE_BASE_NAME = "app"
MAIN_CODE_EXTENSION = "cpp"
MAIN_CODE_FILE = MAIN_CODE_BASE_NAME + '.' + MAIN_CODE_EXTENSION

# Initialise blessings module for colored output
term = Terminal()

# Function to check if a file exists
def fileExists(fileName):
    try:
        open(fileName, "r")
        return True
    except FileNotFoundError:
        return False

# Function to execute command locally
def exec(cmd):
    res = system(cmd)
    return res == 0

# Removes temp created files
def cleanup():
    exec("rm stress_test_in")
    exec("rm prog_stress_test_out")
    exec("rm brute_stress_test_out")

def main():

    assert fileExists("brute"), "Brute Force must exist as ./brute"
    assert fileExists("gen"), "Generator must exist as ./gen"

    t = int(input("Enter the number of tests: "))

    test_at = 0

    while t > 0:
        test_at += 1

        executed = exec("./gen > stress_test_in")
        if not executed:
            print(term.bold(term.red(f"[FAIl] Generator Failed")))
            exit(1)
        else:
            with open(f"stress_test_in", "r") as file:
                stressInData = file.read().strip()

        ok = exec(f"./{MAIN_CODE_BASE_NAME} < stress_test_in > prog_stress_test_out")
        if not ok:
            print(term.bold(term.red(f"[RTE] Run Time Error on {MAIN_CODE_FILE}")))
            print(term.bold(term.red("Test Data:")))
            print(stressInData)
            exit(1)
        else:
            with open("prog_stress_test_out", "r") as file:
                programOutput = "\n".join([x.strip() for x in file.read().strip().splitlines()])

        ok = exec(f"./brute < stress_test_in > brute_stress_test_out")
        if not ok:
            print(term.bold(term.red(f"[RTE] Run Time Error on ./brute")))
            print(term.bold(term.red("Test Data:")))
            print(stressInData)
            exit(1)
        else:
            with open("brute_stress_test_out", "r") as file:
                bruteOutput = "\n".join([x.strip() for x in file.read().strip().splitlines()])

        if bruteOutput == programOutput:
            print(term.bold(term.green(f"[AC] Test {test_at}")))
        else:
            print(term.bold(term.red(f"[WA] Wrong Answer on Test {test_at}")))
            print(term.bold(term.blue("Test Data:")))
            print(stressInData)
            print(term.bold(term.green("Expected Answer:")))
            print(bruteOutput)
            print(term.bold(term.red("Your Answer:")))
            print(programOutput)
            system("cp stress_test_in breaking_case")
            cleanup()
            exit(1)

        cleanup()

        t -= 1

    return 0

if __name__ == '__main__':
    main()