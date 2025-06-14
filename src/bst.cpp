#include "bst.h"
#include <chrono>
#include <algorithm>

namespace BST {

BinaryTree* create() {
    BinaryTree* newTree = new BinaryTree;
    newTree->root = nullptr;
    newTree->NIL = nullptr;
    return newTree;
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    InsertResult result;
    result.numComparisons = 0;

    auto startTime = std::chrono::high_resolution_clock::now();

    Node* parent = nullptr;
    Node* current = tree->root;

    while (current != nullptr) {
        result.numComparisons++;
        parent = current;

        if (word == current->word) {
            // Palavra ja existe, so editamos o vetor para incluir esse doc. Conferimos somente uma presença no documneto, sem recontar.
            if (std::find(current->documentIds.begin(), current->documentIds.end(), documentId) == current->documentIds.end()) {
                current->documentIds.push_back(documentId);
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            result.executionTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
            return result;
        }
        // Percorremos para proxima iteracao
        if (word < current->word) {
            current = current->left;
        } 
        else {
            current = current->right;
        }
    }

    // Caso palavra nao esteja presente, ou seja a 1a palavra, a inserimos como novo node.
    Node* newNode = createNode(word, documentId);
    if (parent == nullptr) {
        tree->root = newNode;
    } else if (word < parent->word) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    result.executionTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return result;

    }

SearchResult search(BinaryTree* tree, const std::string& word) {
    SearchResult result;
    result.found = 0;
    result.numComparisons = 0;
    result.documentIds.clear();

    auto startTime = std::chrono::high_resolution_clock::now();

    Node* current = tree->root;

    while (current != nullptr) {
        result.numComparisons++;

        if (word == current->word) {
            // Encontrado, catalogamos Ids
            result.found = 1;
            result.documentIds = current->documentIds;
            break;
        }
        else if (word < current->word) {
            current = current->left;
        } 
        else {
            current = current->right;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    result.executionTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return result;
}

void destroyHelper(Node* node) {
    if (node == nullptr) return;
    destroyHelper(node->left);
    destroyHelper(node->right);
    delete node;
}

// Recursivamente apagamos cada nó, e após isso, a arvore.
void destroy(BinaryTree* tree) {
    if (tree == nullptr) return;
    destroyHelper(tree->root);
    tree->root = nullptr;
    delete tree;
}
}