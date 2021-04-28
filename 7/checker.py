import numpy as np
import networkx as nx

def checker(path_to_input, path_to_output):
    true_output = {}
    user_output = {}
    
    with open(path_to_input, 'r') as f:
        n, m, t = map(int, f.readline().split())
        if t == 3 or t == 4:
            G = nx.Graph()
        else:
            G = nx.DiGraph()
        for _ in range(m):
            if t == 1:
                i, j = map(int, f.readline().split())
                G.add_edge(i, j)
            elif t == 2:
                i, j, k = map(int, f.readline().split())
                G.add_edge(i, j, weight=k)
            elif t == 3:
                i, j = map(int, f.readline().split())
                G.add_edge(i, j)
            elif t == 4:
                i, j, k = map(int, f.readline().split())
                G.add_edge(i, j, weight=k)
    with open(path_to_output, 'r') as f:
        output_len = int(f.readline())
        user_output['n'] = output_len
            
    true_output['n'] = nx.number_strongly_connected_components(G)
    
    return user_output, true_output, user_output['n'] == true_output['n']
