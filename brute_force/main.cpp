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

int main()
{
    string fileName = "grafo20nos.txt";

    int numNodes, numEdges;

    vector<vector<int>> graph = ReadGraph(fileName, numNodes, numEdges);

    cout << numNodes << " " << numEdges << endl;

    vector<int> maximumClique, candidates;

    for (int i = 0; i < numNodes; i++)
    {
        candidates.push_back(i);
    }

    while (candidates.size() != 0)
    {
        int currentCandidate = candidates.back();
        candidates.pop_back();

        bool alreadyInClique = false;

        for(int i = 0; i<maximumClique.size();i++){
            if(maximumClique[i] == currentCandidate){
                alreadyInClique = true;
                break;
            }
        }

        for (int &node : maximumClique)
        {
            if (graph[candidate][currentCandidate] == 1)
            {
                alreadyInClique = true;
                break;
            }
        }

        if (!alreadyInClique)
        {
            maximumClique.push_back(currentCandidate);
            vector<int> newCandidates;
            for (int &candidate : candidates)
            {
                bool belongsToClique = true;
                for (int &c : maximumClique)
                {
                    if (graph[candidate][c] == 0)
                    {
                        belongsToClique = false;
                        break;
                    }
                    if (belongsToClique)
                    {
                        newCandidates.push_back(candidate);
                    }
                }

                if (newCandidates.size() > candidates.size())
                {
                    candidates = newCandidates;
                }
            }
        }

        cout << "Clique máxima encontrada:" << endl;

        for (unsigned int i = 0; i < maximumClique.size(); i++)
        {
            cout << maximumClique[i] << " ";
        }

        cout << endl;

        return 0;
    }