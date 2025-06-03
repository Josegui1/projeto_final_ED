#include <iostream>

#include "bst.h"

using namespace BST;
using namespace std;


int main() {

    BinaryTree* treeA = create();

    printTree(treeA);

    std::string word = "banana";
    insert(treeA, word, 1);

    std::string word2 = "bolognesa";
    insert(treeA, word2, 1);

    std::string word3 = "carpete";
    insert(treeA, word3, 1);

    std::string word4 = "ballet";
    insert(treeA, word4, 1);

    std::string word5 = "mar";
    insert(treeA, word5, 1);

    std::string word6 = "zumba";
    insert(treeA, word6, 1);

    std::string word7 = "helio";
    insert(treeA, word7, 1);

    std::string word8 = "batata";
    InsertResult iresult8 = insert(treeA, word8, 1);
    cout<<iresult8.executionTime<<endl;
    cout<<iresult8.numComparisons<<endl;

    printTree(treeA);

    SearchResult sresult1 = search(treeA, word3);
    cout<<word3<<endl;
    cout<<"Found: "<<sresult1.found<<endl;
    cout<<"Time: "<<sresult1.executionTime<<endl;
    cout<<"Comparisons: "<<sresult1.numComparisons<<endl;

    SearchResult sresult2 = search(treeA, word6);
    cout<<word6<<endl;
    cout<<"Found: "<<sresult2.found<<endl;
    cout<<"Time: "<<sresult2.executionTime<<endl;
    cout<<"Comparisons: "<<sresult2.numComparisons<<endl;

    std::string word9 = "pepino";
    SearchResult sresult3 = search(treeA, word9);
    cout<<word9<<endl;
    cout<<"Found: "<<sresult3.found<<endl;
    cout<<"Time: "<<sresult3.executionTime<<endl;
    cout<<"Comparisons: "<<sresult3.numComparisons<<endl;

}