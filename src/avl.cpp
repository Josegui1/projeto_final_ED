#include "avl.h"
#include <chrono>
#include <algorithm>

namespace AVL{

    // Funcao para criar uma arvore AVL
    BinaryTree* create(){
        BinaryTree* tree = new BinaryTree;
        tree->root = nullptr;
        tree->NIL = nullptr;
        return tree;
    }

    // Criando uma funcao para atualizar a altura de um no. Ela sera usada mais a frente no insert da AVL
    void updateHeight(Node* node){
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    // Criando uma funcao para calcular o fator de balanceamento de um no
    int getBalance(Node* node){
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);

    }

    //Criando as funcoes auxiliares de rotacao simples para a esquerda e para a direita
    Node* rotateLeft(Node* nodeA) {
        //Definimos pointers para nodes que estaremos manipulando 
        Node* nodeB = nodeA->right;
        nodeA->right = nodeB->left;

        //Mudamos local para filhos de B
        if (nodeB->left != nullptr)
            nodeB->left->parent = nodeA;

        //Mudamos os pais de B
        nodeB->parent = nodeA->parent;

        //Definimos a nova ordem para que encaixe na arvore original
        if (nodeA->parent != nullptr) {
            if (nodeA == nodeA->parent->left)
                nodeA->parent->left = nodeB;
            else
                nodeA->parent->right = nodeB;
        }

        //Efetivamos a rotaçao em si
        nodeB->left = nodeA;
        nodeA->parent = nodeB;

        //Atulizamos os dados dos nos manipulados
        updateHeight(nodeA);
        updateHeight(nodeB);

        return nodeB;
    }

    Node* rotateRight(Node* nodeA) {
        //Definimos pointers
        Node* nodeB = nodeA->left;
        nodeA->left = nodeB->right;

        //Realocamos filhos
        if (nodeB->right != nullptr)
            nodeB->right->parent = nodeA;

        //Mudamos pais de B
        nodeB->parent = nodeA->parent;

        //Reencaixamos na arvore
        if (nodeA->parent != nullptr) {
            if (nodeA == nodeA->parent->left)
                nodeA->parent->left = nodeB;
            else
                nodeA->parent->right = nodeB;
        }

        //Efetuamos rotacao
        nodeB->right = nodeA;
        nodeA->parent = nodeB;

        updateHeight(nodeA);
        updateHeight(nodeB);

        return nodeB;
    }

    // Criando funcoes de rotacoes duplas para os casos 
    Node* rotateLeftRight(Node* node) {
        //Para os casos de rotacao dupla, primeiro definimos os nodes que mudaremos com nossos pointers, e em seguida efeutamos as duas rotacao em sequencia,
        //onde os detalhes e possiveis filhos no outro galho simplesmente sao realocados nas nossas rotacoes simples
        node->left = rotateLeft(node->left);
        if (node->left) node->left->parent = node;
        return rotateRight(node);
    }

    Node* rotateRightLeft(Node* node) {
        node->right = rotateRight(node->right);
        if (node->right) node->right->parent = node;
        return rotateLeft(node);
    }

    // Indo para as funcoes de insercao. Parte da funcao e igual ao da bst, exceto que ocorre o rebalanceamento no final de todo o processo
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
        InsertResult result;
        result.numComparisons = 0;

        auto startTime = std::chrono::high_resolution_clock::now();

        Node* parent = nullptr;
        Node* current = tree->root;

        // Caso que cobre quando a palavra ja existe
        while (current != nullptr){
            result.numComparisons++;
            parent = current;

            if (word == current->word){
                if (std::find(current->documentIds.begin(), current->documentIds.end(), documentId) == current->documentIds.end()) {
                current->documentIds.push_back(documentId);
                }

                auto endTime = std::chrono::high_resolution_clock::now();
                result.executionTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
                return result;
            }

            if (word < current->word) {
                current = current->left;
            } 
            else {
                current = current->right;
            }
        }

        // Caso que cobre quando a palavra ainda nao existe, ou seja, ainda e primeira insercao
        Node* newNode = createNode(word, documentId);
        newNode->parent = parent;

        if (parent == nullptr){
            tree->root = newNode;
        }
        else if (word < parent->word){
            parent->left = newNode;
        }
        else{
            parent->right = newNode;
        }

        // Trabalhando o rebalanceamento
        Node* nodeToCheck = newNode;
        while (nodeToCheck != nullptr){
            updateHeight(nodeToCheck);
            int balance = getBalance(nodeToCheck);

            if (balance > 1){
                if (getBalance(nodeToCheck->left) >= 0){
                    nodeToCheck = rotateRight(nodeToCheck);
                }
                else{
                    nodeToCheck = rotateLeftRight(nodeToCheck);
                }
            }
            else if (balance < -1){
                if (getBalance(nodeToCheck->right) <= 0){
                    nodeToCheck = rotateLeft(nodeToCheck);
                }
                else{
                    nodeToCheck = rotateRightLeft(nodeToCheck);
                }
            }

            if (nodeToCheck->parent == nullptr) {
                tree->root = nodeToCheck;
                break;
            }

            nodeToCheck = nodeToCheck->parent;
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

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;
        destroyHelper(tree->root);
        tree->root = nullptr;
        delete tree;
    }
}