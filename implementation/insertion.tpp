/**
 * Helper function for insert to deal with overflow.
 * This function will promote leaf data to parent while keeping
 * data in leaves.
 * 
 * Create an empty sibling and insert it into the parents children
 * vector.
 * Insert the middle child of the full vector into parent array.
 * Assign second half of array to sibling and first half to child.
 * If the child is not a leaf reassign child pointers, else link the
 * child and sibling together since they are leaves.
 * 
 * @param parent parent of child node being split
 * @param index index of which data in parent
 */
template <typename T>
void BPlusTree<T>::splitChild(Node* parent, int index, Node* child) {
    Node* sibling = new Node(child->isLeaf);
    parent->children.insert(parent->children.begin() + index + 1, sibling);
    parent->keys.insert(parent->keys.begin() + index, child->keys[minDegree - 1]);
    sibling->keys.assign(child->keys.begin() + minDegree, child->keys.end());
    child->keys.resize(minDegree - 1);
    if (!child->isLeaf) {
        sibling->children.assign(child->children.begin() + minDegree + 1, child->children.end());
        child->children.resize(minDegree);
    }
    else {
        child->next = sibling;
        sibling->next = child;
    }
}

template <typename T>
void BPlusTree<T>::insertNonFull(Node* node, T key) {
    if (node->isLeaf) {
        node->keys.insert(std::upper_bound(node->keys.begin(), node->keys.end(), key), key);
    } else {
        int idx = 0;
        while (idx < node->keys.size() && key > node->keys[idx]) {
            idx++;
        }
        idx--;
        if (node->children.size() == 2 * minDegree - 1) {
            splitChild(node, idx, node->children[idx]);
        }
        insertNonFull(node->children[idx], key);
    }
}

/**
 * Generic insert function for B plus tree.
 * Checks if a root exists if not creates one.
 * If size of root keys violates limit factor 2 * minDegree - 1
 * we create a new root and call the split child helper function
 * to deal with overflow.
 * Call insertNonFull helper if no overflow.
 * 
 * @param key the value being inserted
 */
template <typename T> 
void BPlusTree<T>::insert(T key) {
    if (root == nullptr) {
        Node* root = new Node(true);
        root->keys.push_back(key);
        return;
    }
    if (root->keys.size() == 2*minDegree - 1) {
        Node* newRoot = new Node();
        newRoot->children.push_back(root);
        splitChild(newRoot, 0, root);
        root = newRoot;
    }
    insertNonFull(root, key);
}
