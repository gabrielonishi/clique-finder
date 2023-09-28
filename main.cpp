#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<vector<int>> ReadGraph(const string &fileName, int &numNodes, int &numEdges)
{
    /*
    Lê grafo de um arquivo txt, preenche informações sobre número de
    vértices e números de arestas e cria uma matriz de adjacência para
    representar o grafo
    */
    ifstream file(fileName);
    file >> numNodes >> numEdges;

    vector<vector<int>> graph(numNodes, vector<int>(numNodes, 0));

    for (int i = 0; i < numEdges; ++i)
    {
        int u, v;
        file >> u >> v;
        graph[u - 1][v - 1] = 1;
        graph[v - 1][u - 1] = 1;
    }

    file.close();

    return graph;
}

vector<int> FindClique(vector<vector<int>> &graph, int &startingNode, int &numNodes)
{
    startingNode++;
    vector<int> clique = {startingNode};

    for (int candidate = startingNode + 1; candidate < numNodes; candidate++)
    {
        int inClique = true;
        for (int nodeInClique : clique)
        {
            if (graph[nodeInClique][candidate] == 0)
            {
                inClique = false;
            }
        }

        if (inClique)
        {
            clique.push_back(candidate);
        }
    }

    return clique;
}

int main()
{
    string fileName = "grafo20nos.txt";

    int numNodes, numEdges;

    vector<vector<int>> graph = ReadGraph(fileName, numNodes, numEdges);

    cout << numNodes << " " << numEdges << endl;

    int startingNode = 0;

    vector<int> maximumClique = FindClique(graph, startingNode, numNodes);

    for (int currentNode = 1; currentNode < numNodes; currentNode++)
    {
        vector<int> currentClique = FindClique(graph, currentNode, numNodes);
        if (currentClique.size() > maximumClique.size()){
            maximumClique = currentClique;
        }
    }

    cout << "Clique máxima encontrada:" << endl;

    for (unsigned int i = 0; i < maximumClique.size(); i++)
    {
        cout << maximumClique[i] + 1 << " ";
    }

    cout << endl;

    return 0;
}