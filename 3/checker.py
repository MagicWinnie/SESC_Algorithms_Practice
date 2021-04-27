import numpy as np
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import bellman_ford

def checker(path_to_input, path_to_output):
    true_output = {}
    user_output = {}
    
    with open(path_to_input, 'r') as f:
        start, finish = map(int, f.readline().split())
        n, m, t = map(int, f.readline().split())
        input_path = [[0 for _ in range(n)] for _ in range(n)]
        for _ in range(m):
            i, j, k = map(int, f.readline().split())
            input_path[i][j] = k
    with open(path_to_output, 'r') as f:
        output_dist = int(f.readline())
        if output_dist == 100000: output_dist = 0
        user_output['n'] = output_dist

    matrix = csr_matrix(input_path)
    try:
        dist, aa = bellman_ford(matrix, return_predecessors=True)
    except:
        input_dist = -1
    else:
        input_dist = 0 if dist[start, finish] == float('inf') else dist[start, finish]
    true_output['n'] = input_dist
    return user_output, true_output, output_dist == input_dist
