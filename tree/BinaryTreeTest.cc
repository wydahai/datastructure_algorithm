#include <iostream>

#include "BinaryTree.h"

int main() {
    using RealBTNode= BTNodeType<int>;
    BinaryTree<RealBTNode> bitree;
    std::cout << "TreeSize: " << bitree.Size() << std::endl;
    std::cout << "TreeHeight: " << bitree.Height() << std::endl;
    std::cout << "TraverseTree: " << std::endl;
    bitree.TraverseNoRecursion();


    return 0;
}
