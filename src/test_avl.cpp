#include <iostream>
#include <vector>
#include <string>
#include "avl.h"

using namespace AVL;
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

// Teste 3: Múltiplas inserções (com rotaçoes)
void testMultipleInsertions() {
    cout << "=== Teste 3: Multiplas insercoes ===" << endl;
    
    BinaryTree* tree = create();
    
    vector<string> words = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
    
    for (size_t i = 0; i < words.size(); i++) {
        InsertResult result = insert(tree, words[i], i + 1);
        cout << "Inserindo '" << words[i] << "' - Comparacoes: " << result.numComparisons 
             << " - Tempo: " << result.executionTime << " ms" << endl;
    }
    
    cout << "\nEstrutura da arvore criada: \n(Note que, mesmo que inserido alfabeticamente, a árvore apresenta galhos balanceados, tendo empregado rotações após as inserções)" << endl;
    printTree(tree);
    
    destroy(tree);
    cout << endl;
}

// Teste 4: Inserção de palavra duplicada
void testDuplicateWord() {
    cout << "=== Teste 4: Palavra duplicada ===" << endl;
    
    BinaryTree* tree = create();
    
    // Primeira inserção
    InsertResult result1 = insert(tree, "azul", 1);
    cout << "1 insercao 'azul' doc 1 - Comparacoes: " << result1.numComparisons << endl;
    
    // Segunda inserção (mesma palavra, documento diferente)
    InsertResult result2 = insert(tree, "azul", 2);
    cout << "2 insercao 'azul' doc 2 - Comparacoes: " << result2.numComparisons << endl;
    
    // Terceira inserção (mesma palavra, mesmo documento)
    InsertResult result3 = insert(tree, "azul", 2);
    cout << "3 insercao 'azul' doc 2 - Comparacoes: " << result3.numComparisons << endl;
    
    if (tree->root != nullptr) {
        cout << "Documentos para 'azul': ";
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
    insert(tree, "azul", 1);
    insert(tree, "roxo", 2);
    insert(tree, "rosa", 3);
    insert(tree, "verde", 4);
    
    // Buscar por "verde"
    SearchResult result = search(tree, "verde");
    
    cout << "Buscando por 'verde':" << endl;
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
    insert(tree, "amarelo", 1);
    insert(tree, "vermelho", 2);
    insert(tree, "preto", 3);
    
    // Buscar por palavra que não existe
    SearchResult result = search(tree, "lilaz");
    
    cout << "Buscando por 'lilaz':" << endl;
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
    
    SearchResult result = search(tree, "branco");
    
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
        "red", "green", "blue", "yellow", "orange", "purple", "pink", "brown", "black", "white",
        "gray", "cyan", "magenta", "lime", "teal", "navy", "maroon", "olive", "silver", "gold",
        "coral", "beige", "ivory", "turquoise", "indigo", "lavender", "violet", "crimson", "khaki", "salmon",
        "plum", "orchid", "mint", "peach", "apricot", "tan", "amber", "chocolate", "rose", "aqua",
        "azure", "periwinkle", "burgundy", "cerulean", "chartreuse", "mustard", "sepia", "saffron", "rust", "mauve",
        "ochre", "eggplant", "jade", "emerald", "ruby", "sapphire", "bronze", "copper", "smoke", "snow",
        "steel", "charcoal", "sand", "cloud", "stone", "lead", "ash", "ink", "bubblegum", "denim",
        "fuchsia", "honey", "cinnamon", "alabaster", "canary", "lemon", "flamingo", "blush", "mulberry", "sangria",
        "pine", "forest", "seafoam", "midnight", "sunset", "sunflower", "sky", "storm", "mocha", "latte",
        "cobalt", "mulch", "pearl", "powder", "rosewood", "raspberry", "cherry", "wine", "melon", "glacier",
        "papaya", "cantaloupe", "tangerine", "bronze", "brass", "mintcream", "honeydew", "cornflower", "wheat", "basil",
        "clay", "pistachio", "moss", "asparagus", "zucchini", "sienna", "mahogany", "ebony", "snowdrift", "fog",
        "vanilla", "ice", "eggnog", "ocean", "bay", "lagoon", "reed", "iris", "dandelion", "sorbet",
        "poppy", "blueberry", "platinum", "rosegold", "topaz", "opal", "skyblue", "aquamarine", "lilac", "neonpink",
        "neongreen", "neonblue", "hotpink", "pastelpink", "pastelgreen", "pastelblue", "tawny", "taupe", "shamrock", "mintgreen"
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

    // Comparamos o maior e o menor galho
    int minDepth = INT_MAX;
    int maxDepth = 0;
    findLeafDepths(tree->root, 0, minDepth, maxDepth);
    cout << "Altura do maior galho: " << maxDepth << "// Altura do menor galho: " << minDepth << endl;
    cout << "Diferença de altura entre o maior e menor galhos: " << maxDepth - minDepth << endl;
    printTree(tree);

    
    // Testar algumas buscas
    cout << "\nTestando buscas:" << endl;
    for (int i = 0; i < 3; i++) {
        SearchResult result = search(tree, words[i]);
        cout << "Busca '" << words[i] << "': " 
             << (result.found ? "Encontrada" : "Nao encontrada")
             << " - Comparacoes: " << result.numComparisons << endl;
    }
    
    cout << "\nIndice final:" << endl;
    printIndex(tree);
    
    destroy(tree);
    cout << endl;
}

int main() {
    cout << "======================================" << endl;
    cout << "    TESTES AVL - Arvore Balanceada" << endl;
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