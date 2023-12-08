#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <mpi.h>

using namespace std;

bool sort_by_id(int id_1, int id_2) { return (id_1 < id_2); }

vector<int> readGraph(const string &fileName, int &numNodes, int &numEdges)
{
    ifstream file(fileName);
    file >> numNodes >> numEdges;

    vector<int> flattenedGraph(numNodes * numNodes, 0);

    for (int i = 0; i < numEdges; ++i)
    {
        int u, v;
        file >> u >> v;
        flattenedGraph[(u - 1) * numNodes + (v - 1)] = 1;
        flattenedGraph[(v - 1) * numNodes + (u - 1)] = 1;
    }

    file.close();

    return flattenedGraph;
}

void printIntVector(vector<int> &vector)
{
    for (unsigned int i = 0; i < vector.size(); i++)
    {
        cout << vector[i] << " ";
    }

    cout << endl;
}

void printOutput(vector<int> &maximumClique, int numNodes)
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
    int tag = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk_size;
    int numNodes, numEdges;
    vector<int> flattenedGraph;

    if (argc != 2)
    {
        cout << "Run the program with the graph file as an argument (e.g., ./main graph.txt)" << endl;
        return 1;
    }

    if (rank == 0) {
    string fileName = argv[1];
    flattenedGraph = readGraph(fileName, numNodes, numEdges);

    for (int i = 1; i < size; i++) 
    {
        MPI_Send(&numNodes, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
        MPI_Send(&numEdges, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
        MPI_Send(flattenedGraph.data(), numNodes * numNodes, MPI_INT, i, tag, MPI_COMM_WORLD);
    }
    } else 
    {
        MPI_Recv(&numNodes, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&numEdges, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        flattenedGraph.resize(numNodes * numNodes);
        MPI_Recv(flattenedGraph.data(), numNodes * numNodes, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    vector<int> maximumClique;
    for (int currentNode = 0; currentNode < numNodes; currentNode++)
    {
        vector<int> connections;
        for (int node = 0; node < numNodes; node++)
        {
            if (flattenedGraph[currentNode * numNodes + node] == 1)
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
                    if (flattenedGraph[member * numNodes + connection2] == 0)
                        inClique = false;
                }
                if (inClique)
                    clique.push_back(connection2);
            }
            if (clique.size() > maximumClique.size())
                maximumClique = clique;
        }
    }

    // Send maximum clique back to rank 0
    if (rank != 0) 
    {
        MPI_Send(maximumClique.data(), maximumClique.size(), MPI_INT, 0, tag, MPI_COMM_WORLD);
    } else 
    {
        vector<int> temp;

        for (int i = 1; i < size; i++) 
        {
            temp.resize(maximumClique.size());
            MPI_Recv(temp.data(), maximumClique.size(), MPI_INT, i, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (temp.size() > maximumClique.size()) 
            {
                maximumClique = temp;
            }
        }
        printOutput(maximumClique, numNodes);
    }

    MPI_Finalize();
    return 0;
}
