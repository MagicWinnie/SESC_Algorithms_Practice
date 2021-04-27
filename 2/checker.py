import numpy as np
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import dijkstra

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
    true_out, aa = dijkstra(csgraph=matrix, directed=True, return_predecessors=True)
        
    true_output['n'] = 0 if true_out[start, finish] == float('inf') else 1
    
    return user_output, true_output, true_output['n'] == user_output['n']
