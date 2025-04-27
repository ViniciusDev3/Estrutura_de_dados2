#include "tree.hpp"
#include <iostream>

using namespace std;

int main (){
    BinaryTree tree1, tree2;
    tree1.insertVal(4);
    tree1.insertVal(5);
    tree1.insertVal(2);
    tree1.insertVal(7);

    tree2.insertVal(4);
    tree2.insertVal(6);
    tree2.insertVal(7);
    tree2.insertVal(8);

    if (tree1.estruturalmenteSimilar(tree2)) {
        std::cout << "As árvores têm a mesma altura!" << std::endl;
    } else {
        std::cout << "As árvores têm alturas diferentes!" << std::endl;
    }
}