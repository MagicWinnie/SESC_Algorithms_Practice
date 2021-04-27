import numpy as np
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import depth_first_order

def checker(path_to_input, path_to_output):
    true_output = {}
    user_output = {}
    
    with open(path_to_input, 'r') as f:
        input_len, start = map(int, f.readline().split())
        input_path = [list(map(int, f.readline().split())) for _ in range(input_len)]

    with open(path_to_output, 'r') as f:
        output_len = int(f.readline())
        output_path = []
        if output_len != 0:
            output_path = list(map(int, f.readline().split()))
        
        user_output['n'] = output_len
        user_output['list'] = output_path

    matrix = csr_matrix(input_path)
    true_out, aa = depth_first_order(matrix, start)
    true_out = true_out.tolist()
        
    true_output['n'] = len(true_out)
    true_output['list'] = true_out

    return user_output, true_output, true_output['n'] == user_output['n'] and true_output['list'] == user_output['list']
