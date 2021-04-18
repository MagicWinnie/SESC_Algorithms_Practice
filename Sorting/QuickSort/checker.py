def checker(path_to_input, path_to_output):
    true_output = {}
    user_output = {}

    finishTime = -1
    
    with open(path_to_input, 'r') as f:
        input_n = int(f.readline())
        inputLst = list(map(int, f.readline().split()))

        true_output['list'] = inputLst
    with open(path_to_output, 'r') as f:
        finishTime = float(f.readline())
        outputLst = list(map(int, f.readline().split()))

        user_output['list'] = outputLst

    user_output['time'] = finishTime

    return user_output, true_output, sorted(inputLst) == outputLst
