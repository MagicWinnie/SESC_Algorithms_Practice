import random
import os
import sys
import shutil
import subprocess
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import bellman_ford
from subprocess import TimeoutExpired


def clearFolder(folder):
    folder = os.path.join(os.path.dirname(os.path.abspath(__file__)), folder)
    for filename in os.listdir(folder):
        file_path = os.path.join(folder, filename)
        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)


def get_path(Pr, i, j):
    path = [j]
    k = j
    while Pr[i, k] != -9999:
        path.append(Pr[i, k])
        k = Pr[i, k]
    return path[::-1]


argv = sys.argv
n = 5
TIME_LIMIT = 2
flagCompiled = True

if len(argv) != 2:
    print("Usage:")
    print("\tTesting:")
    print("\t\ttest_script.py <inputFile>")
    exit()

command = argv[1]
if command.split('.')[-1] == 'cpp':
    print('COMPILING...')
    result = subprocess.run(
        ['g++', command, '-o', command[:-3] + 'exe'], stdout=subprocess.PIPE)
    print("Return code:", result.returncode)
    if result.returncode != 0:
        print("stdout:", result.stdout.decode('utf-8'))
        print("stderr:", result.stderr)
        exit(-1)
    print("FINISHED COMPILING")
    command = command[:-3] + 'exe'
elif command.split('.')[-1] == 'c':
    print('COMPILING...')
    result = subprocess.run(
        ['gcc', command, '-o', command[:-3] + 'exe'], stdout=subprocess.PIPE)
    print("Return code:", result.returncode)
    if result.returncode != 0:
        print("stdout:", result.stdout.decode('utf-8'))
        print("stderr:", result.stderr)
        exit(-1)
    print("FINISHED COMPILING")
    command = command[:-3] + 'exe'

if 'output' not in os.listdir('.'):
    os.mkdir('output')
else:
    clearFolder('output')

for i in range(n):
    try:
        result = subprocess.run([command, os.path.join('input', '{}.in'.format(
            i + 1)), str(i + 1)], stdout=subprocess.PIPE, timeout=TIME_LIMIT)
    except TimeoutExpired:
        print("-"*10)
        print("Test #{} not passed!".format(i+1))
        print("\tTIME LIMIT EXCEEDED")
        print("-"*10)
        continue
    except KeyboardInterrupt:
        exit(-1)
    with open(os.path.join('output', '{}.txt'.format(i + 1)), 'r') as f:
        output_dist = int(f.readline())
        output_len = int(f.readline())
        output_path = list(map(int, f.readline().split()))
    with open(os.path.join('input', '{}.in'.format(i + 1)), 'r') as f:
        size, start, finish = map(int, f.readline().split())
        matrix = [list(map(int, f.readline().split())) for _ in range(size)]
        matrix = csr_matrix(matrix)
        dist, aa = bellman_ford(matrix, return_predecessors=True)
        input_dist = dist[start, finish]
    if output_dist == input_dist and output_path == get_path(aa, start, finish):
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
        print(f"\t{input_dist}")
        print(f"\t{get_path(aa, start, finish)}")
        print("User answer:")
        print(f"\t{output_dist}")
        print(f"\t{output_path}")
        print("-" * 10)
