#include "rbt.h"
#include "data.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>

using namespace std;
using namespace RBT;
using namespace DATA;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Uso: ./rbt <search|stats> <n_docs> <diretorio>" << endl;
        return 1;
    }

    string command = argv[1];
    int nDocs = stoi(argv[2]);
    string directory = argv[3];

    // Cria a árvore rubro-negra
    BinaryTree* tree = create();

    // Vetor para armazenar todos os arquivos carregados
    vector<FileData>* files = new vector<FileData>;

    for (int i = 0; i <= nDocs; ++i) {
        string path = directory + "/" + to_string(i) + ".txt";
        vector<string> words = readFromFile(path);

        FileData file;
        file.fileID = i;
        file.words = words;
        files->push_back(file);

        for (const string& word : words) {
            insert(tree, word, i);
        }
    }

    if (command == "search") {
        cout << "Digite palavras para buscar (Ctrl+D para sair):" << endl;
        string word;
        while (cin >> word) {
            SearchResult result = search(tree, word);
            if (result.found) {
                cout << "Palavra \"" << word << "\" encontrada nos documentos: ";
                for (int id : result.documentIds) {
                    cout << id << " ";
                }
                cout << "(Comparacoes: " << result.numComparisons 
                     << ", Tempo: " << result.executionTime << " ms)" << endl;
            } else {
                cout << "Palavra \"" << word << "\" nao encontrada ("
                     << result.numComparisons << " comparacoes)" << endl;
            }
        }

    } else if (command == "stats") {
        int totalComparisons = 0;
        double totalTime = 0.0;
        int totalWords = 0;

        for (const auto& file : *files) {
            for (const string& word : file.words) {
                totalWords++;
                SearchResult result = search(tree, word);
                totalComparisons += result.numComparisons;
                totalTime += result.executionTime;
            }
        }

        int minDepth = INT_MAX;
        int maxDepth = 0;
        findLeafDepths(tree->root, 0, minDepth, maxDepth);

        cout << " ==== Estatisticas de busca ====:" << endl;
        cout << "Total de palavras buscadas: " << totalWords << endl;
        cout << "Comparacoes totais: " << totalComparisons << endl;
        cout << "Comparacoes medias por busca: " << (double)totalComparisons / totalWords << endl;
        cout << "Tempo total de busca: " << totalTime << " ms" << endl;
        cout << "Tempo medio por busca: " << totalTime / totalWords << " ms" << endl;
        cout << "Altura do maior galho: " << maxDepth << " // Altura do menor galho: " << minDepth << endl;
        cout << "Diferenca de altura entre o maior e menor galhos: " << maxDepth - minDepth << endl;

    } else {
        cerr << "Comando invalido: use 'search' ou 'stats'" << endl;
    }

    delete files;
    destroy(tree);
    return 0;
}
