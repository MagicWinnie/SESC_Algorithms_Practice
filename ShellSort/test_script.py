import random
import time, os, sys, shutil, subprocess
try:
    import matplotlib.pyplot as plt
except ModuleNotFoundError:
    print('Without plotting')
    flagPlotting = False

def clearFolder(folder):
    folder = os.path.dirname(os.path.abspath(__file__)) + '\\' + folder
    for filename in os.listdir(folder):
        file_path = os.path.join(folder, filename)
        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)

argv = sys.argv
n = 100
flag = False
flagPlotting = True
flagCompiled = True

if len(argv) < 2:
    print("Usage:")
    print("\tGenerate input data:")
    print("\t\ttest_script.py gen")
    print("\tClear input folder:")
    print("\t\ttest_script.py clear")
    print("\tTesting:")
    print("\t\ttest_script.py <inputFile>")
    exit()
elif len(argv) == 2 and argv[1] == 'clear':
    clearFolder('input\\')
    clearFolder('output\\')
    exit(0)
elif len(argv) == 2 and argv[1] == 'gen':
    flag = True

# generating input
iterators = [10*i for i in range(1, n+1)]

if flag:
    if 'input' not in os.listdir('.'): os.mkdir('input')
    for i in range(n):
        lst = [random.randint(-10**5, 10**5) for _ in range(iterators[i])]
        with open('input\\{}.txt'.format(i+1), 'w') as f:
            f.write(str(iterators[i]) + '\n')
            f.write(" ".join(map(str, lst)))
    exit(0)

arr = []

command = argv[1]
if command.split('.')[-1] == 'cpp':
    print('COMPILING...')
    result = subprocess.run(['g++', command, '-o', command[:-3]+'o'], stdout=subprocess.PIPE)
    print("Return code:", result.returncode)
    print("stdout:", result.stdout)
    print("stderr:", result.stderr)
    print("FINISHED COMPILING")
    command = command[:-3]+'o'
    if result.returncode != 0: exit(-1)

for i in range(n):
    result = subprocess.run([command, 'input\\{}.txt'.format(i+1), str(i+1)], stdout=subprocess.PIPE)
    finishTime = -1
    with open('input\\{}.txt'.format(i+1), 'r') as f:
        input_n = int(f.readline())
        inputLst = list(map(int, f.readline().split()))
    with open('output\\{}.txt'.format(i+1), 'r') as f:
        finishTime = float(f.readline())
        outputLst = list(map(int, f.readline().split()))
    if sorted(inputLst) == outputLst:
        if flagPlotting: arr.append(finishTime)
        print("Test #{} passed!".format(i+1))
    else:
        if flagPlotting: arr.append(-1)
        print("Test #{} not passed!".format(i+1))
        print("Return code:", result.returncode)
        print("stdout:", result.stdout)
        print("stderr:", result.stderr)
        
if flagPlotting:
    plt.xlabel("Length of array")
    plt.ylabel("Time, ms")
    plt.plot(iterators, arr, 'o', markersize=5)
    plt.savefig('plot.png')