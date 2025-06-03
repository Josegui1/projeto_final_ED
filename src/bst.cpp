#include "bst.h"
#include <chrono>

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
        // Caso palavra nao esteja ja presente, se adiciona
        if (word < current->word) {
            current = current->left;
        } 
        else {
            current = current->right;
        }
    }

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

void destroy(BinaryTree* tree);

}