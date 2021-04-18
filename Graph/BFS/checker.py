import numpy as np
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import breadth_first_order

def backtrace(Pr, i, j):
    if Pr[j] == -9999: return []
    path = [j]
    k = j
    while Pr[k] != -9999:
        path.append(Pr[k])
        k = Pr[k]
    return path[::-1]

def checker(path_to_input, path_to_output):
    true_output = {}
    user_output = {}
    
    with open(path_to_input, 'r') as f:
        input_len, start, finish = map(int, f.readline().split())
        input_path = [list(map(int, f.readline().split())) for _ in range(input_len)]

    with open(path_to_output, 'r') as f:
        output_len = int(f.readline())
        output_path = []
        if output_len != 0:
            output_path = list(map(int, f.readline().split()))
        
        user_output['n'] = output_len
        user_output['list'] = output_path

    matrix = csr_matrix(input_path)
    true_out, aa = breadth_first_order(matrix, start)
    true_out = true_out.tolist()
        
    true_output['n'] = len(backtrace(aa, start, finish))
    true_output['list'] = backtrace(aa, start, finish)

    return user_output, true_output, true_output['n'] == user_output['n'] and true_output['list'] == user_output['list']
