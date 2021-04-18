import numpy as np
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import bellman_ford

def backtrace(Pr, i, j):
    path = [j]
    k = j
    while Pr[i, k] != -9999:
        path.append(Pr[i, k])
        k = Pr[i, k]
    return path[::-1]

def checker(path_to_input, path_to_output):
    true_output = {}
    user_output = {}
    
    with open(path_to_input, 'r') as f:
        input_len, start, finish = map(int, f.readline().split())
        input_path = [list(map(int, f.readline().split())) for _ in range(input_len)]

    with open(path_to_output, 'r') as f:
        output_dist = int(f.readline())
        output_len = int(f.readline())
        output_path = list(map(int, f.readline().split()))
        
        user_output['n'] = output_dist
        user_output['list'] = output_path

    matrix = csr_matrix(input_path)
    dist, aa = bellman_ford(matrix, return_predecessors=True)
    input_dist = dist[start, finish]
        
    true_output['n'] = input_dist
    true_output['list'] = backtrace(aa, start, finish)

    return user_output, true_output, output_dist == input_dist and output_path == backtrace(aa, start, finish)
