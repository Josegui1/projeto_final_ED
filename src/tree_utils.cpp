#include "tree_utils.h"
#include <iostream>

Node* createNode(const std::string& word, int documentId){
    Node* newNode = new Node;
    newNode->word = word;
    newNode->documentIds.push_back(documentId);
    newNode->parent = nullptr;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    newNode->isRed = 1; 
    return newNode;
}

int getHeight(Node* node){
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

void inorderTraversal(Node* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        
        std::cout << node->word << ": ";
        for (size_t i = 0; i < node->documentIds.size(); i++) {
            std::cout << node->documentIds[i];
            if (i < node->documentIds.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        
        inorderTraversal(node->right);
    }
}

void printIndex(BinaryTree* tree) {
    if (tree == nullptr || tree->root == nullptr) {
        std::cout << "Indice vazio." << std::endl;
        return;
    }
    
    std::cout << "=== INDICE INVERTIDO ===" << std::endl;
    inorderTraversal(tree->root);
    std::cout << "========================" << std::endl;
}

void printTreeHelper(Node* node, const std::string& prefix, bool isLast) {
    if (node != nullptr) {
        std::cout << prefix;
        std::cout << (isLast ? "└── " : "├── ");
        std::cout << node->word << std::endl;
        
        // Contar filhos não nulos
        bool hasLeft = (node->left != nullptr);
        bool hasRight = (node->right != nullptr);
        
        if (hasLeft || hasRight) {
            if (hasLeft) {
                printTreeHelper(node->left, prefix + (isLast ? "    " : "│   "), !hasRight);
            }
            if (hasRight) {
                printTreeHelper(node->right, prefix + (isLast ? "    " : "│   "), true);
            }
        }
    }
}

void printTree(BinaryTree* tree) {
    if (tree == nullptr || tree->root == nullptr) {
        std::cout << "Arvore vazia." << std::endl;
        return;
    }
    
    std::cout << "=== ESTRUTURA DA ARVORE ===" << std::endl;
    std::cout << tree->root->word << std::endl;
    
    bool hasLeft = (tree->root->left != nullptr);
    bool hasRight = (tree->root->right != nullptr);
    
    if (hasLeft || hasRight) {
        if (hasLeft) {
            printTreeHelper(tree->root->left, "", !hasRight);
        }
        if (hasRight) {
            printTreeHelper(tree->root->right, "", true);
        }
    }
    std::cout << "===============================" << std::endl;
}