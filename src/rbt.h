#ifndef RBT_H
#define RBT_H

#include "tree_utils.h"
#include <string>

namespace RBT {

enum Color { RED = 0, BLACK = 1 };

BinaryTree* create();
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
SearchResult search(BinaryTree* tree, const std::string& word);
void destroy(BinaryTree* tree);

} 

#endif
