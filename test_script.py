import os
import sys
from pprint import pprint

import subprocess
from subprocess import TimeoutExpired

# sanity checks for libs
try:
    import numpy as np
except ModuleNotFoundError:
    raise Exception(
        "You don't have numpy installed. Install it using: 'python -m pip install numpy'")
try:
    import scipy
except ModuleNotFoundError:
    raise Exception(
        "You don't have scipy installed. Install it using: 'python -m pip install scipy'")
try:
    import matplotlib.pyplot as plt
except ModuleNotFoundError:
    raise Exception(
        "You don't have matplotlib installed. Install it using: 'python -m pip install matplotlib'")
try:
    import networkx as nx
except ModuleNotFoundError:
    raise Exception(
        "You don't have networkx installed. Install it using: 'python -m pip install networkx'")

WORKING_FOLDER = os.path.dirname(os.path.abspath(__file__))

def get_task_name(path):
    root = os.path.join(os.path.dirname(os.path.abspath(__file__)), path)
    work_file = list(set(['main.cpp', 'main.c']).intersection(os.listdir(root)))[0]
    with open(os.path.join(root, work_file), 'r', encoding='utf-8') as raw_data:
        first_line = raw_data.readline()
    if '//' in first_line:
        return first_line.replace('\n', '').replace('//', '').strip()
    return -1

# getting available folders
TO_PRINT = []
WHITELIST = ['main.cpp', 'main.c']
i = 0
for x in os.walk('.'):
    if x[0] == '.':
        continue
    if len(set(WHITELIST).intersection(os.listdir(x[0]))) > 0:
        path = x[0].replace('\\', '/')
        if len(path.split('/')) > 1:
            TO_PRINT.append({'path': path.replace('./', '') + '/'})
            i += 1

# pprint folders
TO_PRINT.sort(key=lambda x: x['path'])
TO_INPUT = {}
used = set()
for i in range(len(TO_PRINT)):
    path = TO_PRINT[i]['path'].split('/')[:-1]
    for j in range(len(path)):
        if path[j] not in used:
            print('\t'*j, end='')
            if j == len(path) - 1:
                print(i, end=': ')
                task_name = get_task_name(TO_PRINT[i]['path'])
                if task_name != -1:
                    print(task_name)
                else:
                    print(path[j])
            else:
                print(path[j])
            TO_INPUT[i] = None
            used.add(path[j])
print(f"{-1}: Exit")

# getting right input from user
while True:
    inp = input(f"Enter a number in from {0} to {len(TO_PRINT) - 1}: ")
    if inp == '-1':
        print('Quitting')
        exit(0)
    if not(inp.isdigit()):
        print("Not a number. Try again")
        continue
    inp = int(inp)
    if inp not in list(range(len(TO_PRINT))):
        print(f"Enter a number in from {0} to {len(TO_PRINT) - 1}. Try again")
        continue
    break

ROOT_SUBFOLDER = os.path.join(os.path.dirname(
    os.path.abspath(__file__)), TO_PRINT[inp]['path'])


def clearFolder(path, BLACKLIST=['txt', 'out', 'o', 'exe']):
    for filename in os.listdir(path):
        if filename.split('.')[-1] not in BLACKLIST:
            continue
        file_path = os.path.join(path, filename)
        os.remove(file_path)


# some init vars
assert 'tests' in os.listdir(ROOT_SUBFOLDER), "[ERROR] No input folder"

n = len(os.listdir(os.path.join(ROOT_SUBFOLDER, 'tests')))

assert n > 0, "[ERROR] No input files found in '" + os.path.join(ROOT_SUBFOLDER, 'tests') + "'"

TIME_LIMIT = 5

FILE_TO_RUN = set(WHITELIST).intersection(set(os.listdir(ROOT_SUBFOLDER)))
assert len(FILE_TO_RUN) > 0, "[ERROR] No 'main.cpp' or 'main.c' file"
FILE_TO_RUN = list(FILE_TO_RUN)[0]

clearFolder(ROOT_SUBFOLDER)

# compiling
print('COMPILING...')
path = os.path.join(ROOT_SUBFOLDER, FILE_TO_RUN)
result = subprocess.run(
    [('g++' if ('.cpp' in path) else 'gcc'), path, '-o', os.path.join(ROOT_SUBFOLDER, 'main.exe')], stdout=subprocess.PIPE)
print("Return code:", result.returncode)
if result.returncode != 0:
    print("stdout:", result.stdout.decode('utf-8'))
    print("stderr:", result.stderr)
    exit(-1)
print("FINISHED COMPILING")

# clear output folder
if 'output' not in os.listdir(ROOT_SUBFOLDER):
    os.mkdir(os.path.join(ROOT_SUBFOLDER, 'output'))
else:
    clearFolder(os.path.join(ROOT_SUBFOLDER, 'output'))

# loading the checker
assert 'checker.py' in os.listdir(
    ROOT_SUBFOLDER), "[ERROR] No 'checker.py' file"
sys.path.append(os.path.join(ROOT_SUBFOLDER))
from checker import checker


sorting = False
if 'Sorting' in ROOT_SUBFOLDER:
    sorting = True
    arr = []

# run tests
for i in range(n):
    # running the binary file
    try:
        result = subprocess.run([os.path.join(ROOT_SUBFOLDER, 'main.exe'), os.path.join(ROOT_SUBFOLDER, 'tests', '{}.in'.format(
            i + 1)), os.path.join(ROOT_SUBFOLDER, 'output', '{}.txt'.format(str(i + 1)))], stdout=subprocess.PIPE, timeout=TIME_LIMIT)
    except TimeoutExpired:
        print("-" * 10)
        print("Test #{} not passed!".format(i + 1))
        print("\tTIME LIMIT EXCEEDED")
        print("-" * 10)
        continue
    except KeyboardInterrupt:
        print("Stopping...")
        exit(-1)

    user_output, true_output, checker_result = checker(os.path.join(ROOT_SUBFOLDER, 'tests', '{}.in'.format(
        i + 1)), os.path.join(ROOT_SUBFOLDER, 'output', '{}.txt'.format(i + 1)))

    if sorting:
        arr.append(user_output['time'])

    if checker_result:
        print("-" * 10)
        print("Test #{} passed!".format(i + 1))
        print("-" * 10)
    else:
        print("-" * 10)
        print("Test #{} not passed!".format(i + 1))
        print("\tWRONG ANSWER")
        print("\tstdout:", result.stdout.decode("utf-8"))
        print("\tstderr:", result.stderr)
        print("Correct answer:")
        pprint(true_output)
        print("User answer:")
        pprint(user_output)
        print("-" * 10)

if sorting:
    iterators = [10 * i for i in range(1, n + 1)]
    plt.xlabel("Length of array")
    plt.ylabel("Time, ms")
    plt.plot(iterators, arr, 'o', markersize=5)
    plt.savefig(os.path.join(ROOT_SUBFOLDER, 'plot.png'))
