#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <iostream>
#include <string>
#include <vector>

struct Node{
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;
    int Color;
};

struct BinaryTree{
    Node* root;
    Node* NIL;
};

struct InsertResult{
    int numComparisons;
    double executionTime;
};

struct SearchResult{
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
};

Node* createNode(const std::string& word, int documentId);
void printIndex(BinaryTree* tree);
void printTree(BinaryTree* tree);
int getHeight(Node* node);
void inorderTraversal(Node* node);
void printTreeHelper(Node* node, const std::string& prefix, bool isLast);
void findLeafDepths(Node* node, int depth, int& minDepth, int&maxDepth);

#endif


