#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <mpi.h>

using namespace std;

bool sort_by_id(int id_1, int id_2) { return (id_1 < id_2); }

vector<vector<int>> readGraph(const string &fileName, int &numNodes, int &numEdges)
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

void printOutput(vector<int> &maximumClique)
{
    cout << "Size of the maximum clique: " << maximumClique.size() << endl;
    cout << "Maximum clique found:" << endl;
    cout << "[";

    sort(maximumClique.begin(), maximumClique.end(), sort_by_id);

    unsigned int i = 0;

    for (i = 0; i < maximumClique.size() - 1; i++)
    {
        cout << maximumClique[i] + 1 << ", ";
    }

    cout << maximumClique[i] + 1 << "]" << endl;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) {
            cout << "Run the program with the graph file as an argument (e.g., ./main graph.txt)" << endl;
        }
        MPI_Finalize();
        return 1;
    }

    string fileName = argv[1];

    int numNodes, numEdges;
    vector<vector<int>> graph;

    if (rank == 0) {
        graph = readGraph(fileName, numNodes, numEdges);
    }

    MPI_Bcast(&numNodes, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&numEdges, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Dividing the work among processes
    int startNode = rank * (numNodes / size);
    int endNode = (rank == size - 1) ? numNodes : (rank + 1) * (numNodes / size);

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
            vector<int> clique = {currentNode, connection1};
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

    vector<int> globalMaxClique;
    if (rank == 0) {
        globalMaxClique = maximumClique;
        for (int i = 1; i < size; i++) {
            vector<int> tempMaxClique;
            MPI_Recv(&tempMaxClique[0], maximumClique.size(), MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (tempMaxClique.size() > globalMaxClique.size()) {
                globalMaxClique = tempMaxClique;
            }
        }
    } else {
        MPI_Send(&maximumClique[0], maximumClique.size(), MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        printOutput(globalMaxClique);
    }

    MPI_Finalize();

    return 0;
}