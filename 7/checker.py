import numpy as np
import networkx as nx

def checker(path_to_input, path_to_output):
    true_output = {}
    user_output = {}
    
    G = nx.DiGraph()

    with open(path_to_input, 'r') as f:
        n, m, t = map(int, f.readline().split())
        for _ in range(m):
            i, j = map(int, f.readline().split())
            G.add_edge(i, j)
    with open(path_to_output, 'r') as f:
        output_len = int(f.readline())
        user_output['n'] = output_len
            
    true_output['n'] = nx.number_strongly_connected_components(G)
    
    return user_output, true_output, user_output['n'] == true_output['n']
