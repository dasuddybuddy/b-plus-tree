#include "../include/BPlusTree.h"

int main() {
    BPlusTree<int> tree(3);

    tree.insert(50);

    std::cout << "Printing tree:\n";

    tree.printTree();

    return 0;

}
