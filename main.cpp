#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<vector<int>> ReadGraph(const string &fileName, int &numNodes, int &numEdges)
{
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

void printIntVector(vector<int> &vector)
{
    for (unsigned int i = 0; i < vector.size(); i++)
    {
        cout << vector[i] << " ";
    }

    cout << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Rode o arquivo com o arquivo do grafo como argumento (ex: ./main arquivo.txt)" << endl;
        return 1;
    }

    string fileName = argv[1];

    int numNodes, numEdges;

    vector<vector<int>> graph = ReadGraph(fileName, numNodes, numEdges);

    cout << numNodes << " " << numEdges << endl;

    vector<int> maximumClique;
    for (int currentNode = 0; currentNode < numNodes; currentNode++)
    {
        vector<int> connections;
        for (int node = 0; node < numNodes; node++)
        {
            if (graph[currentNode][node] == 1)
                connections.push_back(node);
        }

        for (int connection1 : connections)
        {
            vector<int> clique = {currentNode, connection1}; // Move initialization here
            for (int connection2 : connections)
            {
                bool inClique = true;
                for (int member : clique)
                {
                    if (graph[member][connection2] == 0)
                        inClique = false;
                }
                if (inClique)
                    clique.push_back(connection2);
            }
            if (clique.size() > maximumClique.size())
                maximumClique = clique;
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