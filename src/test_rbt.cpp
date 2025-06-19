#include <iostream>
#include <vector>
#include <string>
#include "rbt.h"

using namespace RBT;
using namespace std;

// Teste 1: Criação da árvore
void testTreeCreation() {
    cout << "=== Teste 1: Criacao da arvore ===" << endl;
    
    BinaryTree* tree = create();
    
    if (tree != nullptr && tree->root == nullptr) {
        cout << "Arvore criada com sucesso" << endl;
    } else {
        cout << "Erro na criação da arvore" << endl;
    }
    
    destroy(tree);
    cout << "Teste concluido" << endl << endl;
}

// Teste 2: Inserção básica
void testBasicInsertion() {
    cout << "=== Teste 2: Insercao basica ===" << endl;
    
    BinaryTree* tree = create();
    
    InsertResult result = insert(tree, "teste", 1);
    
    cout << "Inserindo palavra 'teste' no documento 1" << endl;
    cout << "Tempo de execucao: " << result.executionTime << " ms" << endl;
    cout << "Numero de comparacoes: " << result.numComparisons << endl;
    
    if (tree->root != nullptr && tree->root->word == "teste") {
        cout << "Palavra inserida corretamente como raiz" << endl;
    } else {
        cout << "Erro na insercao" << endl;
    }
    
    destroy(tree);
    cout << endl;
}


// Teste 3: Múltiplas inserções
void testMultipleInsertions() {
    cout << "=== Teste 3: Multiplas insercoes ===" << endl;

    BinaryTree* tree = create();

    vector<string> words = {"delta", "alpha", "epsilon", "beta", "gamma", "ksi", "phi", "psi"};

    for (size_t i = 0; i < words.size(); i++) {
        InsertResult result = insert(tree, words[i], i + 1);
        cout << "Inserindo '" << words[i] << "' - Comparacoes: " << result.numComparisons 
             << " - Tempo: " << result.executionTime << " ms" << endl;
    }

    destroy(tree);
    cout << endl;
}

// Teste 4: Palavra duplicada
void testDuplicateWord() {
    cout << "=== Teste 4: Palavra duplicada ===" << endl;

    BinaryTree* tree = create();

    insert(tree, "filosofia", 1);
    insert(tree, "filosofia", 2);
    insert(tree, "filosofia", 2); // repetido

    SearchResult result = search(tree, "filosofia");

    cout << "Documentos para 'filosofia': ";
    for (int id : result.documentIds) {
        cout << id << " ";
    }
    cout << endl;
    cout << "Total de documentos: " << result.documentIds.size() << endl;

    destroy(tree);
    cout << endl;
}

// Teste 5: Busca por palavra existente
void testSuccessfulSearch() {
    cout << "=== Teste 5: Busca bem-sucedida ===" << endl;

    BinaryTree* tree = create();

    insert(tree, "zenon", 1);
    insert(tree, "epicuro", 2);
    insert(tree, "platao", 3);

    SearchResult result = search(tree, "epicuro");

    cout << "Buscando por 'epicuro':" << endl;
    cout << "Encontrada: " << (result.found ? "Sim" : "Nao") << endl;
    cout << "Tempo de busca: " << result.executionTime << " ms" << endl;
    cout << "Comparacoes: " << result.numComparisons << endl;

    destroy(tree);
    cout << endl;
}

// Teste 6: Busca sem sucesso
void testUnsuccessfulSearch() {
    cout << "=== Teste 6: Busca sem sucesso ===" << endl;

    BinaryTree* tree = create();

    insert(tree, "estoico", 1);
    insert(tree, "cinico", 2);

    SearchResult result = search(tree, "kantiano");

    cout << "Buscando por 'kantiano':" << endl;
    cout << "Encontrada: " << (result.found ? "Sim" : "Nao") << endl;
    cout << "Tempo de busca: " << result.executionTime << " ms" << endl;
    cout << "Comparacoes: " << result.numComparisons << endl;

    destroy(tree);
    cout << endl;
}

// Teste 7: Busca em árvore vazia
void testEmptyTree() {
    cout << "=== Teste 7: Busca em arvore vazia ===" << endl;

    BinaryTree* tree = create();

    SearchResult result = search(tree, "qualquer");

    cout << "Encontrada: " << (result.found ? "Sim" : "Nao") << endl;
    cout << "Comparacoes: " << result.numComparisons << endl;

    destroy(tree);
    cout << endl;
}

// Teste 8: Conjunto maior
void testLargerDataset() {
    cout << "=== Teste 8: Dataset maior ===" << endl;

    BinaryTree* tree = create();

    vector<string> words = {
        "democrito", "pitagoras", "heraclito", "tales", "anaximenes", "parmenides", "anaximandro",
        "empedocles", "leucipo", "protagoras", "gorgias", "socrates", "platao", "aristoteles"
    };

    double totalTime = 0;
    int totalComparisons = 0;

    for (size_t i = 0; i < words.size(); ++i) {
        InsertResult result = insert(tree, words[i], i + 1);
        totalTime += result.executionTime;
        totalComparisons += result.numComparisons;
    }

    cout << "Tempo total: " << totalTime << " ms" << endl;
    cout << "Media por insercao: " << (totalTime / words.size()) << " ms" << endl;
    cout << "Comparacoes totais: " << totalComparisons << endl;

    for (int i = 0; i < 3; ++i) {
        SearchResult result = search(tree, words[i]);
        cout << "Busca '" << words[i] << "': "
             << (result.found ? "Encontrada" : "Nao encontrada")
             << " - Comparacoes: " << result.numComparisons << endl;
    }

    destroy(tree);
    cout << endl;
}

int main() {
    cout << "======================================" << endl;
    cout << "   TESTES RBT - Arvore Rubro-Negra" << endl;
    cout << "======================================" << endl << endl;

    testTreeCreation();
    testBasicInsertion();
    testMultipleInsertions();
    testDuplicateWord();
    testSuccessfulSearch();
    testUnsuccessfulSearch();
    testEmptyTree();
    testLargerDataset();

    cout << "======================================" << endl;
    cout << "   TESTES CONCLUIDOS" << endl;
    cout << "======================================" << endl;

    return 0;
}
