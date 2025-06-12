#include <iostream>
#include <vector>
#include <string>
#include "bst.h"

using namespace BST;
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
    
    vector<string> words = {"jupter", "vesta", "janus", "venus", "silvano", "marte", "diana", "baco"};
    
    for (size_t i = 0; i < words.size(); i++) {
        InsertResult result = insert(tree, words[i], i + 1);
        cout << "Inserindo '" << words[i] << "' - Comparacoes: " << result.numComparisons 
             << " - Tempo: " << result.executionTime << " ms" << endl;
    }
    
    cout << "\nEstrutura da arvore criada:" << endl;
    printTree(tree);
    
    destroy(tree);
    cout << endl;
}

// Teste 4: Inserção de palavra duplicada
void testDuplicateWord() {
    cout << "=== Teste 4: Palavra duplicada ===" << endl;
    
    BinaryTree* tree = create();
    
    // Primeira inserção
    InsertResult result1 = insert(tree, "agnihotra", 1);
    cout << "1 insercao 'agnihotra' doc 1 - Comparacoes: " << result1.numComparisons << endl;
    
    // Segunda inserção (mesma palavra, documento diferente)
    InsertResult result2 = insert(tree, "agnihotra", 2);
    cout << "2 insercao 'agnihotra' doc 2 - Comparacoes: " << result2.numComparisons << endl;
    
    // Terceira inserção (mesma palavra, mesmo documento)
    InsertResult result3 = insert(tree, "agnihotra", 2);
    cout << "3 insercao 'agnihotra' doc 2 - Comparacoes: " << result3.numComparisons << endl;
    
    if (tree->root != nullptr) {
        cout << "Documentos para 'agnihotra': ";
        for (int id : tree->root->documentIds) {
            cout << id << " ";
        }
        cout << endl;
        cout << "Total de documentos: " << tree->root->documentIds.size() << endl;
    }
    
    destroy(tree);
    cout << endl;
}

// Teste 5: Busca por palavra existente
void testSuccessfulSearch() {
    cout << "=== Teste 5: Busca bem-sucedida ===" << endl;
    
    BinaryTree* tree = create();
    
    // Inserir algumas palavras
    insert(tree, "aristoteles", 1);
    insert(tree, "platao", 2);
    insert(tree, "diogenes", 3);
    insert(tree, "socrates", 4);
    
    // Buscar por "platao"
    SearchResult result = search(tree, "platao");
    
    cout << "Buscando por 'platao':" << endl;
    cout << "Encontrada: " << (result.found ? "Sim" : "Nao") << endl;
    cout << "Tempo de busca: " << result.executionTime << " ms" << endl;
    cout << "Comparacoes: " << result.numComparisons << endl;
    
    if (result.found) {
        cout << "Documentos encontrados: ";
        for (int id : result.documentIds) {
            cout << id << " ";
        }
        cout << endl;
    }
    
    destroy(tree);
    cout << endl;
}

// Teste 6: Busca por palavra inexistente
void testUnsuccessfulSearch() {
    cout << "=== Teste 6: Busca sem sucesso ===" << endl;
    
    BinaryTree* tree = create();
    
    // Inserir algumas palavras
    insert(tree, "anacreonte", 1);
    insert(tree, "sofocles", 2);
    insert(tree, "euripedes", 3);
    
    // Buscar por palavra que não existe
    SearchResult result = search(tree, "inexistente");
    
    cout << "Buscando por 'inexistente':" << endl;
    cout << "Encontrada: " << (result.found ? "Sim" : "Nao") << endl;
    cout << "Tempo de busca: " << result.executionTime << " ms" << endl;
    cout << "Comparacoes: " << result.numComparisons << endl;
    
    destroy(tree);
    cout << endl;
}

// Teste 7: Árvore vazia
void testEmptyTree() {
    cout << "=== Teste 7: Busca em arvore vazia ===" << endl;
    
    BinaryTree* tree = create();
    
    SearchResult result = search(tree, "qualquer");
    
    cout << "Buscando em arvore vazia:" << endl;
    cout << "Encontrada: " << (result.found ? "Sim" : "Nao") << endl;
    cout << "Comparacoes: " << result.numComparisons << endl;
    
    destroy(tree);
    cout << endl;
}

// Teste 8: Teste com mais dados
void testLargerDataset() {
    cout << "=== Teste 8: Dataset maior ===" << endl;
    
    BinaryTree* tree = create();
    
    vector<string> words = {
        "aquiles", "helena", "odisseus", "diomedes", "ajax", "herakles", "febo", "zeus", "hera",
        "homero", "dioniso", "afrodite", "athena", "briseis", "criseis", "heitor", "hecuba", "andromaca",
        "agamemnon", "menelau"

    };
    
    double totalTime = 0;
    int totalComparisons = 0;
    
    cout << "Inserindo " << words.size() << " palavras..." << endl;
    for (size_t i = 0; i < words.size(); i++) {
        InsertResult result = insert(tree, words[i], i + 1);
        totalTime += result.executionTime;
        totalComparisons += result.numComparisons;
    }

    // Adicionando em outros lugares para ver se o indice repete
    InsertResult result = insert(tree, words[3], 2);
    result = insert(tree, words[5], 3);
    result = insert(tree, words[2], 10);
    result = insert(tree, words[7], 1);
    result = insert(tree, words[12], 7);
    
    cout << "Tempo total de insercao: " << totalTime << " ms" << endl;
    cout << "Tempo medio por insercao: " << (totalTime / words.size()) << " ms" << endl;
    cout << "Total de comparacoes: " << totalComparisons << endl;
    cout << "Media de comparacoes: " << (double)totalComparisons / words.size() << endl;
    
    // Testar algumas buscas
    cout << "\nTestando buscas:" << endl;
    for (int i = 0; i < 3; i++) {
        SearchResult result = search(tree, words[i]);
        cout << "Busca '" << words[i] << "': " 
             << (result.found ? "Encontrada" : "Nao encontrada")
             << " - Comparacoes: " << result.numComparisons << endl;
    }
    
    // Comparamos o maior e o menor galho
    int minDepth = INT_MAX;
    int maxDepth = 0;
    findLeafDepths(tree->root, 0, minDepth, maxDepth);
    cout << "Altura do maior galho: " << maxDepth << "// Altura do menor galho: " << minDepth << endl;
    cout << "Diferença de altura entre o maior e menor galhos: " << maxDepth - minDepth << endl;
    printTree(tree);

    cout << "\nIndice final:" << endl;
    printIndex(tree);
    
    destroy(tree);
    cout << endl;
}

int main() {
    cout << "======================================" << endl;
    cout << "    TESTES BST - Arvore Binaria de Busca" << endl;
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
    cout << "    TESTES CONCLUIDOS" << endl;
    cout << "======================================" << endl;
    
    return 0;
}