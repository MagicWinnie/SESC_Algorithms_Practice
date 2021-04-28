import numpy as np
import networkx as nx
from networkx.algorithms import tree

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
                G.add_edge(i, j, k)
            elif t == 3:
                i, j = map(int, f.readline().split())
                G.add_edge(i, j)
            elif t == 4:
                i, j, k = map(int, f.readline().split())
                G.add_edge(i, j, k)
    with open(path_to_output, 'r') as f:
        output_len = int(f.readline())
        
        user_output['n'] = output_len

    return user_output, true_output, true_output['n'] == user_output['n']
