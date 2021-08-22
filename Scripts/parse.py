#! /usr/bin/python

from http.server import BaseHTTPRequestHandler, HTTPServer
from sys import exit
from json import loads
from subprocess import run
from blessings import Terminal
from os import system

# Initialise blessings module for colored output
term = Terminal()

# Name of the file where you write code
MAIN_CODE_BASE_NAME = "app"
MAIN_CODE_EXTENSION = "cpp"
MAIN_CODE_FILE = MAIN_CODE_BASE_NAME + '.' + MAIN_CODE_EXTENSION

# Function to execute command locally
def exec(cmd, cwd="."):
    try:
        res = run(cmd, cwd=cwd, capture_output=True, check=True)
        return (True, res.stdout.decode('utf-8'))
    except:
        res = run(cmd, cwd=cwd, capture_output=True)
        return (False, res.stderr.decode('utf-8'))

# Server to parse the Competitive Companion
class handler(BaseHTTPRequestHandler):
    def do_POST(self):
        # Read post data from Competitive Companion
        content_length = int(self.headers['Content-Length'])
        data = loads(self.rfile.read(content_length).decode('utf-8'))

        # Gets folder name from Competitive Companion
        folderName = data['languages']['java']['taskClass']

        # Create folder
        executed = exec(["mkdir", folderName])[0]
        if not executed:
            exec(["rm", "-rf", folderName])
            exec(["mkdir", folderName])

        # Creates CPP file
        system(f"touch {folderName}/{MAIN_CODE_FILE}")

        # Creates custom input file
        system(f"touch {folderName}/in")

        # Open CPP files in Sublime Text
        system(f"subl {folderName}/{MAIN_CODE_FILE}")

        # Copies Runner python file
        system(f"cp run.py {folderName}/run")

        # Makes Runner python file executable
        system(f"chmod +x {folderName}/run")

        # Adds test from Competitive Companion
        counter = 0
        for test in data['tests']:
            counter += 1
            with open(f"./{folderName}/in{counter}", "w") as file:
                file.write(test['input'])
            with open(f"./{folderName}/out{counter}", "w") as file:
                file.write(test['output'])

        print(term.green(term.bold("[OK]")), term.bold(term.blue("Parsed problem statement!")))
        print(term.blue("Saved to:"), term.bold(term.red(folderName)))

        # Kills program after parsing data
        exit(0)

def main():
    with HTTPServer(('localhost', 1327), handler) as server:
        server.serve_forever()
    return 0

if __name__ == "__main__":
    main()