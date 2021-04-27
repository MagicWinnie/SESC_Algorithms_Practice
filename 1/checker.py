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
        start, finish = map(int, f.readline().split())
        n, m, t = map(int, f.readline().split())
        input_path = [[0 for _ in range(n)] for _ in range(n)]
        for _ in range(m):
            i, j = map(int, f.readline().split())
            input_path[i][j] = 1
    with open(path_to_output, 'r') as f:
        output_len = int(f.readline())
        
        user_output['n'] = output_len

    matrix = csr_matrix(input_path)
    true_out, aa = breadth_first_order(matrix, start)
    true_out = true_out.tolist()
    true_output['n'] = len(backtrace(aa, start, finish)) - 1

    return user_output, true_output, true_output['n'] == user_output['n']
[11, 14, 2, 1, 0, 12, 9]