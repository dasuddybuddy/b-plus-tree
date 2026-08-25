template <typename T>
void BPlusTree<T>::printTree(Node* node, int level, bool isLast, std::string prefix) {
    if (node == nullptr) return;

    std::cout << prefix;
    std::cout << (isLast ? "└── " : "├── ");

    if (node->isLeaf) {
        std::cout << "{ ";
        for (size_t i = 0; i < node->keys.size(); i++) {
            if (i > 0) std::cout << ", ";
            std::cout << node->keys[i];
        }
        std::cout << " }";
        if (node->next != nullptr) {
            std::cout << " ->";
        }
        std::cout << std::endl;
    } else {
        std::cout << "[ ";
        for (size_t i = 0; i < node->keys.size(); i++) {
            if (i > 0) std::cout << ", ";
            std::cout << node->keys[i];
        }
        std::cout << " ]" << std::endl;

        for (size_t i = 0; i < node->children.size(); i++) {
            std::string childPrefix = prefix + (isLast ? "    " : "│   ");
            printTree(node->children[i], level + 1, i == node->children.size() - 1, childPrefix);
        }
    }
}

template <typename T>
void BPlusTree<T>::printTree() {
    if (root == nullptr) {
        std::cout << "(empty tree)" << std::endl;
        return;
    }

    if (root->isLeaf) {
        std::cout << "{ ";
        for (size_t i = 0; i < root->keys.size(); i++) {
            if (i > 0) std::cout << ", ";
            std::cout << root->keys[i];
        }
        std::cout << " }" << std::endl;
        return;
    }

    std::cout << "[ ";
    for (size_t i = 0; i < root->keys.size(); i++) {
        if (i > 0) std::cout << ", ";
        std::cout << root->keys[i];
    }
    std::cout << " ]" << std::endl;

    for (size_t i = 0; i < root->children.size(); i++) {
        printTree(root->children[i], 1, i == root->children.size() - 1, "");
    }

    std::cout << "\nLeaves: ";
    Node* leaf = root;
    while (!leaf->isLeaf) {
        leaf = leaf->children[0];
    }
    while (leaf != nullptr) {
        std::cout << "{ ";
        for (size_t i = 0; i < leaf->keys.size(); i++) {
            if (i > 0) std::cout << ", ";
            std::cout << leaf->keys[i];
        }
        std::cout << " }";
        if (leaf->next != nullptr) std::cout << " -> ";
        leaf = leaf->next;
    }
    std::cout << std::endl;
}
