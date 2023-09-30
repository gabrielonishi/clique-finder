'''
Utiliza a biblioteca netorkx para encontrar a clique máxima
para fins de correção

Baseado no arquivo cedido pelos professores
'''

import networkx as nx
import sys

def convert_items_to_int(clique:list)->list:
    for i, node in enumerate(clique):
        clique[i] = int(node)
    
    return clique

if(len(sys.argv)!= 2):
    raise ValueError("Rode o arquivo com o grafo como argumento (ex: python3 main.py grafo.txt)")

file_name = sys.argv[1]

with open(file_name, 'r') as file:
    next(file)
    G = nx.parse_adjlist(file)

cliques = list(nx.find_cliques(G))

largest_clique_size = len(max(cliques, key=len))

print('Tamanho da clique máxima: ', largest_clique_size)
print('Cliques máximas encontradas:')
for clique in cliques:
    if(len(clique) == largest_clique_size):
        converted_clique = convert_items_to_int(clique)
        converted_clique.sort()
        print(converted_clique)