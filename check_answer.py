import networkx as nx

# Nome do arquivo de entrada
nome_arquivo = "grafo.txt"

# Abrir o arquivo e pular a primeira linha
with open(nome_arquivo, 'r') as arquivo:
    next(arquivo)  # Pula a primeira linha

    # Lê o grafo a partir das linhas restantes
    G = nx.parse_adjlist(arquivo)

# Encontrar todas as cliques maximais
cliques_maximais = list(nx.find_cliques(G))

# Encontrar a clique máxima (a maior)
clique_maxima = max(cliques_maximais, key=len)

tamanho_clique_maxima = len(max(cliques_maximais, key=len))
cliques_enormes = list()

print("Cliques maximais encontradas:")
for clique in cliques_maximais:
    print(clique)
    if(len(clique) == tamanho_clique_maxima):
        cliques_enormes.append(clique)

print("Clique máxima encontrada:")

for clique in cliques_enormes:
    for i, num in enumerate(clique):
        clique[i] = int(num)
    clique.sort(reverse=True)
    print(clique)