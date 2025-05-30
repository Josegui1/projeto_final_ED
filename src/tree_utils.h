#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <iostream>
#include <string>
#include <vector>

struct Node{
    std::string word;
    std::vector<int> DocumentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;
};

struct BinaryTree{
    Node* root;
};

struct InsertResult{
    int numComparisons;
    double executionTime;
};

struct SearchResult{
    int found;
    std::vector<int> DocumentIds;
    double executionTime;
    int numComparisons;
};

Node* createNode(const std::string& word, int documentId);
void printIndex(BinaryTree* tree);
void printTree(BinaryTree* tree);
int getHeight(Node* node);
void inorderTraversal(Node* node);

#endif


