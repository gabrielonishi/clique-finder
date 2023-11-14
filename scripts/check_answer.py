'''
Uses the networkx library to find the maximum clique
for grading purposes

Based on the file provided by the instructors
'''

import networkx as nx
import sys

def convert_items_to_int(clique: list) -> list:
    for i, node in enumerate(clique):
        clique[i] = int(node)
    
    return clique

if len(sys.argv) != 2:
    raise ValueError("Run the program with the graph as an argument (e.g., python3 main.py graph.txt)")

file_name = sys.argv[1]

with open(file_name, 'r') as file:
    next(file)
    G = nx.parse_adjlist(file)

cliques = list(nx.find_cliques(G))

largest_clique_size = len(max(cliques, key=len))

print('Size of the maximum clique: ', largest_clique_size)
print('Maximum cliques found:')

first_first_index = 10e7

right_answer = None

max_cliques = list()

for clique in cliques:
    if len(clique) == largest_clique_size:
        converted_clique = convert_items_to_int(clique)
        converted_clique.sort()
        print(converted_clique)
        max_cliques.append(converted_clique)
