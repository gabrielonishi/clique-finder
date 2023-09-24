'''
Utiliza a biblioteca netorkx para encontrar a clique máxima
para fins de correção

Baseado no arquivo cedido pelos professores
'''

import networkx as nx

def convert_items_to_int(clique:list)->list:
    for i, node in enumerate(clique):
        clique[i] = int(node)
    
    return clique

file_name = "grafo20nos.txt"

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
        converted_clique.sort(reverse=True)
        print(converted_clique)