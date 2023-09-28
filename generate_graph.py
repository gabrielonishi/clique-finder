import networkx as nx
import random

num_vertices = 20
probabilidade_conexao = 0.7

grafo = nx.fast_gnp_random_graph(num_vertices, probabilidade_conexao)

nome_arquivo = "grafo.txt"

with open(nome_arquivo, 'w') as arquivo:
    arquivo.write(f"{num_vertices} {grafo.number_of_edges()}\n")
    for aresta in grafo.edges():
        arquivo.write(f"{aresta[0]+1} {aresta[1]+1}\n")

print(f"Grafo densamente conectado gerado e salvo em '{nome_arquivo}'.")