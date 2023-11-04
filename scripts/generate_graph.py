import networkx as nx
import sys, os

num_vertices = int(sys.argv[1])
connection_probability = float(sys.argv[2])
graph_name = sys.argv[3].split('.')[0]

graph = nx.fast_gnp_random_graph(num_vertices, connection_probability)

output_directory = os.path.join(os.pardir, "graphs")
os.makedirs(output_directory, exist_ok=True)

filename = os.path.join(output_directory, f"{graph_name}.txt")

with open(filename, 'w') as f:
    f.write(f"{num_vertices} {graph.number_of_edges()}\n")
    for edge in graph.edges():
        f.write(f"{edge[0]+1} {edge[1]+1}\n")

print(f"Grafo densamente conectado gerado e salvo em ../graphs/{filename}'.")