import random
import os, sys, shutil, subprocess

def clearFolder(folder):
    folder = os.path.dirname(os.path.abspath(__file__)) + '\\' + folder
    for filename in os.listdir(folder):
        file_path = os.path.join(folder, filename)
        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)

argv = sys.argv
n = 10
flagCompiled = True

if len(argv) != 2:
    print("Usage:")
    print("\tClear output folder:")
    print("\t\ttest_script.py clear")
    print("\tTesting:")
    print("\t\ttest_script.py <inputFile>")
    exit()
elif len(argv) == 2 and argv[1] == 'clear':
    clearFolder('output\\')
    exit(0)

command = argv[1]
if command.split('.')[-1] == 'cpp':
    print('COMPILING...')
    result = subprocess.run(['g++', command, '-o', command[:-3] + 'o'], stdout=subprocess.PIPE)
    print("Return code:", result.returncode)
    print("stdout:", result.stdout)
    print("stderr:", result.stderr)
    print("FINISHED COMPILING")
    command = command[:-3] + 'o'
    if result.returncode != 0: exit(-1)

for i in range(n):
    result = subprocess.run([command, 'input\\{}.in'.format(i+1), str(i+1)], stdout=subprocess.PIPE)
    with open('output\\{}.txt'.format(i+1), 'r') as f:
        output_len = int(f.readline())
        output_path = []
        if output_len != 0:
            output_path = list(map(int, f.readline().split()))
    with open('true_output\\{}.out'.format(i+1), 'r') as f:
        true_output_len = int(f.readline())
        true_output_path = []
        if true_output_len != 0:
            true_output_path = list(map(int, f.readline().split()))
    if output_len == true_output_len and output_path == true_output_path:
        print("Test #{} passed!".format(i+1))
    else:
        print("Test #{} not passed!".format(i+1))
        print("\tReturn code:", result.returncode)
        print("\tstdout:", result.stdout)
        print("\tstderr:", result.stderr)
