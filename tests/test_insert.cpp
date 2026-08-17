#include "../include/BPlusTree.h"

int main() {
    BPlusTree<int> tree(2);

    // Insert values
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);
    tree.insert(70);

    return 0;

}
