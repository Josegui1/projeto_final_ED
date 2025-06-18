#include "rbt.h"
#include <chrono>
#include <algorithm>

namespace RBT {

// Criando uma funcao para atualizar a altura de um nó
void updateHeight(Node* node){
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

// Rotação a esquerda
static void rotateLeft(BinaryTree** treePtr, Node* x) {
    BinaryTree* tree = *treePtr;
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    // Atualiza alturas após rotação
    updateHeight(x);
    updateHeight(y);
}

// Rotação a direita
static void rotateRight(BinaryTree** treePtr, Node* x) {
    BinaryTree* tree = *treePtr;
    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
    // Atualiza alturas após rotação
    updateHeight(x);
    updateHeight(y);
}

// Corrige propriedades Red-Black após inserção
static void fixInsertion(BinaryTree** treePtr, Node* z) {
    BinaryTree* tree = *treePtr;
    while (z != tree->root && z->parent->color == RED) {
        Node* p = z->parent;
        Node* g = p->parent;
        if (p == g->left) {
            Node* u = g->right;
            if (u && u->color == RED) {
                // Caso 1: tio vermelho
                g->color = RED;
                p->color = BLACK;
                u->color = BLACK;
                z = g;
            } else {
                if (z == p->right) {
                    // Caso 2: zig-zag
                    z = p;
                    rotateLeft(treePtr, z);
                    p = z->parent;
                    g = p->parent;
                }
                // Caso 3: zig-zig
                p->color = BLACK;
                g->color = RED;
                rotateRight(treePtr, g);
                z = p;
            }
        } else {
            Node* u = g->left;
            if (u && u->color == RED) {
                g->color = RED;
                p->color = BLACK;
                u->color = BLACK;
                z = g;
            } else {
                if (z == p->left) {
                    z = p;
                    rotateRight(treePtr, z);
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;
                g->color = RED;
                rotateLeft(treePtr, g);
                z = p;
            }
        }
    }
    // Garante root sempre preta
    tree->root->color = BLACK;
}

// Cria uma árvore vazia
BinaryTree* create() {
    BinaryTree* tree = new BinaryTree();
    tree->root = nullptr;
    tree->NIL = nullptr;
    return tree;
}

// Insere palavra, mantendo unicidade de documentId e atualizando alturas
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    InsertResult res{};
    res.numComparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();

    Node* y = nullptr;
    Node* x = tree->root;
    // Busca posição de inserção
    while (x) {
        res.numComparisons++;
        y = x;
        if (word == x->word) {
            // Palavra já existe: adiciona docId se novo
            if (std::find(x->documentIds.begin(), x->documentIds.end(), documentId) == x->documentIds.end()) {
                x->documentIds.push_back(documentId);
            }
            // Atualiza altura nos ancestrais
            Node* h = x;
            while (h) { updateHeight(h); h = h->parent; }
            auto end = std::chrono::high_resolution_clock::now();
            res.executionTime = std::chrono::duration<double,std::milli>(end-start).count();
            return res;
        } else if (word < x->word) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    // Cria novo nó vermelho
    Node* z = createNode(word, documentId);
    z->color = RED;
    z->left = z->right = nullptr;
    z->parent = y;

    if (!y) {
        tree->root = z;
    } else if (z->word < y->word) {
        y->left = z;
    } else {
        y->right = z;
    }
    // Atualiza altura do novo nó e ancestrais
    Node* h = z;
    while (h) { updateHeight(h); h = h->parent; }
    // Corrige propriedades RBT
    fixInsertion(&tree, z);

    auto end = std::chrono::high_resolution_clock::now();
    res.executionTime = std::chrono::duration<double,std::milli>(end-start).count();
    return res;
}

// Busca palavra
SearchResult search(BinaryTree* tree, const std::string& word) {
    SearchResult res{};
    res.found = 0;
    res.numComparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();

    Node* x = tree->root;
    while (x) {
        res.numComparisons++;
        if (word == x->word) {
            res.found = 1;
            res.documentIds = x->documentIds;
            break;
        } else if (word < x->word) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    // Execução e retorno
    auto end = std::chrono::high_resolution_clock::now();
    res.executionTime = std::chrono::duration<double,std::milli>(end-start).count();
    return res;
}

// Destrói a árvore
static void destroyHelper(Node* node) {
    if (!node) return;
    destroyHelper(node->left);
    destroyHelper(node->right);
    delete node;
}

void destroy(BinaryTree* tree) {
    if (!tree) return;
    destroyHelper(tree->root);
    delete tree;
}

}
