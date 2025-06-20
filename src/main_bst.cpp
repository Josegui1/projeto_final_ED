#include "bst.h"
#include "data.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>

using namespace std;
using namespace BST;
using namespace DATA;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Uso: ./bst <search|stats> <n_docs> <diretorio>" << endl;
        return 1;
    }

    // Definimos todos nossos argumentos
    string command = argv[1];
    int nDocs = stoi(argv[2]);
    string directory = argv[3];

    // Cria arvore binaria
    BinaryTree* tree = create();

    // Cria um vetor de FileDatas para armazenar nossos dados
    vector<FileData>* files = new vector<FileData>;

    for (int i = 0; i <= nDocs; ++i) {
        // Abre cada .txt
        string path = directory + "/" + to_string(i) + ".txt";
        vector<string> words = readFromFile(path);

        // E os acrescenta
        FileData file;
        file.fileID = i;
        file.words = words;
        files->push_back(file);

        // Insere as palavras na arvore
        for (const string& word : words) {
            insert(tree, word, i);
        }
    }

    // Percorremos a arvore procurando o node com nosso valor. Depois output as informacoes da busca.
    if (command == "search") {
        cout << "Digite palavras para buscar (Ctrl+D para sair):" << endl;
        string word;
        while (cin >> word) {
            SearchResult querry = search(tree, word);
            if (querry.found) {
                cout << "Palavra \"" << word << "\" encontrada nos documentos: ";
                for (int docId : querry.documentIds) {
                    cout << docId << " ";
                }
                cout << "(Comparacoes: " << querry.numComparisons 
                     << ", Tempo: " << querry.executionTime << " ms)" << endl;
            } else {
                cout << "Palavra \"" << word << "\" nao encontrada ("
                     << querry.numComparisons << " comparacoes)" << endl;
            }
        }

    // Caso nao precisarmos achar uma palavra, somente contamos os dados para cada nova palavra adicionada como se fosse nosso querry, 
    // e somamos tudo para saber o desempenho total para a construcao da arvore, palavra por palavra.
    } else if (command == "stats") {
        int totalComparisons = 0;
        double totalTime = 0.0;
        int totalWords = 0;

        for (const auto& file : *files) {
            for (const string& word : file.words) {
                totalWords++;
                SearchResult querry = search(tree, word);
                totalComparisons += querry.numComparisons;
                totalTime += querry.executionTime;
            }
        }

        int minDepth = INT_MAX;
        int maxDepth = 0;
        findLeafDepths(tree->root, 0, minDepth, maxDepth);

        // E output nossos resultados.
        cout << "Estatisticas de busca:" << endl;
        cout << "Total de palavras buscadas: " << totalWords << endl;
        cout << "Comparacoes totais: " << totalComparisons << endl;
        cout << "Comparacoes medias por busca: " << (double)totalComparisons / totalWords << endl;
        cout << "Tempo total de busca: " << totalTime << " ms" << endl;
        cout << "Tempo medio por busca: " << totalTime / totalWords << " ms" << endl;
        cout << "Altura do maior galho: " << maxDepth << "// Altura do menor galho: " << minDepth << endl;
        cout << "Diferença de altura entre o maior e menor galhos: " << maxDepth - minDepth << endl;
    } else {
        cerr << "Comando invalido: use 'search' ou 'stats'" << endl;
    }

    // Liberamos memoria.
    delete files;
    destroy(tree);
    return 0;
}
