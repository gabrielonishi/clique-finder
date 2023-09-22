#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Função para ler o grafo a partir do arquivo de entrada
vector<vector<int>> LerGrafo(const string& nomeArquivo, int& numVertices, int& numArestas) {
    ifstream arquivo(nomeArquivo);
    arquivo >> numVertices >> numArestas;

    vector<vector<int>> grafo(numVertices, vector<int>(numVertices, 0));

    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        arquivo >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;  // O grafo é não direcionado
    }

    arquivo.close();

    return grafo;
}

int main(){
    string nomeArquivo = "grafo.txt";

    int numVertices, numArestas;

    vector<vector<int>> grafo = LerGrafo(nomeArquivo, numVertices, numArestas);


    cout << numVertices << " " << numArestas << endl;

    vector<int> cliqueMaxima, candidatos;

    for(int i=0; i<numVertices; i++){
        candidatos.push_back(i);
    }

    while (candidatos.size()!=0){
        int v = candidatos.back();
        candidatos.pop_back();
        
        bool podeAdicionar = true;

        for(int& u : cliqueMaxima){
            if(grafo[u][v] == 0){
                podeAdicionar = false;
                break;
            }
        }

        if(podeAdicionar){
            cliqueMaxima.push_back(v);
            vector<int> novosCandidatos;
            for(int& u : candidatos){
                bool ajdacentesATodos = true;
                for(int& c : cliqueMaxima){
                    if(grafo[u][c] == 0){
                        ajdacentesATodos = false;
                        break;
                    }
                }

                if(ajdacentesATodos){
                    novosCandidatos.push_back(u);
                }
            }
            candidatos = novosCandidatos;
        }
    }
    
    for(unsigned int i = 0; i<cliqueMaxima.size(); i++){
        cout << cliqueMaxima[i] << " ";
    }

    cout << endl;

    return 0;

}