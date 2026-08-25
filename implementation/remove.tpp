/**
 * Determines how to remove data from leaves. Does not
 * focus on removing anywhere else unless needed.
 * 
 * We first traverse the tree recursively until we reach
 * a leaf node. If the target key is in leaves erase it 
 * and update parent data. 
 * 
 * If the node has less children then minDegree - 1 we 
 * check if we can borrow from sibling data if not we merge.
 * 
 * Once leaf data is fixed if underflow occurs we propagate 
 * to the internal nodes (we check this by checking if their 
 * children is less then mindegree)
 * 
 * To deal with underflow of internal nodes we check if parents 
 * siblings have a child they can give or else merge children 
 * and parent data.
 * 
 * This cycle will occur within internal nodes until a merge 
 * does not occur.
 * 
 * @param node the current node
 * @param parent the parent of the current node
 * @param key data to be removed
 * @param index used for traversal to find target data
 */
template <typename T>
void BPlusTree<T>::remove(Node*& node, Node*& parent, T key, int index) {
    if (node->isLeaf) {
        auto it {find(node->keys.begin(), node->keys.end(), key)};
        if (it == node->keys.end()) {
            return;
        }

        node->keys.erase(it);

        if (parent != nullptr && index > 0) {
            parent->keys[index - 1] = node->keys.front();
        }

        if (node->keys.size() < minDegree - 1) {
            if (parent == nullptr) {
                return;
            }
            if (index + 1 < parent->children.size() &&
                parent->children[index + 1]->keys.size() >= minDegree) {
                borrowFromNext(node, parent, index);
            } else if (index > 0 && parent->children[index - 1]->keys.size() >= minDegree) {
                borrowFromPrev(node, parent, index);
            } else {
                merge(node, parent, index);
            }
        }
        return;
    }

    int childIndex =
        upper_bound(node->keys.begin(),
                    node->keys.end(),
                    key) - node->keys.begin();

    remove(node->children[childIndex],
           node,
           key,
           childIndex);

    if (node == root) {
        if (!node->isLeaf && node->keys.empty()) {
            Node* oldRoot = root;
            root = root->children[0];
            delete oldRoot;
        }
        return;
    }

    if (node->children.size() >= minDegree) {
        return;
    }

    if (index > 0 &&
        parent->children[index - 1]->children.size() >= minDegree + 1) {
        borrowInternalFromPrev(node, parent, index);
    }
    else if (index + 1 < parent->children.size() &&
             parent->children[index + 1]->children.size() >= minDegree + 1) {
        borrowInternalFromNext(node, parent, index);
    }
    else {
        mergeInternal(node, parent, index);
    }
}

/**
 * Borrow left sibling data for given leaf node.
 * 
 * We look at the back of the children vector
 * in the left sibling and add it to the vector
 * node was in. We then updata the parent using
 * that data.
 * 
 * @param node node where removed data was
 * @param parent parent of node
 * @param index index where node is located
 */
template <typename T>
void BPlusTree<T>::borrowFromPrev(Node*& node, Node*& parent, int index) {
    Node* prev = parent->children[index - 1];
    T data = prev->keys.back();
    node->keys.insert(node->keys.begin(), data);
    prev->keys.pop_back();
    parent->keys[index - 1] = node->keys.front();
}

/**
 * Borrow right sibling data for given leaf node.
 * 
 * We look at right sibling vector to extract the
 * front data from it and add it to given leaf node.
 * We erase it and update the parent data with new
 * front data of right sibling.
 * 
 * @param node node where removed data was
 * @param parent parent of node
 * @param index index where node is located
 */
template <typename T>
void BPlusTree<T>::borrowFromNext(Node*& node, Node*& parent, int index) {
    Node* next = parent->children[index + 1];
    T data = next->keys.front();
    node->keys.push_back(data);
    next->keys.erase(next->keys.begin());
    parent->keys[index] = next->keys.front();
}

/**
 * Merge leaf data with right sibling if available.
 * If not merge with left.
 * 
 * We take data from sibling and input it into leaf
 * node then we reassign pointers and delete the empty
 * node.
 * 
 * @param node node where removed data was
 * @param parent parent of node
 * @param index index where node is located
 */
template <typename T>
void BPlusTree<T>::merge(Node*& node, Node*& parent, int index) {
    if (index + 1 < parent->children.size()) {
        Node* next = parent->children[index + 1];

        node->keys.insert(
            node->keys.end(),
            next->keys.begin(),
            next->keys.end()
        );

        node->next = next->next;

        parent->keys.erase(
            parent->keys.begin() + index
        );

        parent->children.erase(
            parent->children.begin() + index + 1
        );

        delete next;
    }
    else if (index > 0) {
        Node* prev = parent->children[index - 1];

        prev->keys.insert(
            prev->keys.end(),
            node->keys.begin(),
            node->keys.end()
        );

        prev->next = node->next;

        parent->keys.erase(
            parent->keys.begin() + index - 1
        );

        parent->children.erase(
            parent->children.begin() + index
        );

        delete node;
    }
}

/**
 * Borrow left sibling data for internal nodes.
 * 
 * We insert the parent data into given node and
 * take the parents right child node.
 * 
 * We then take the biggest child in the left sibling
 * node to update parent and remove that child
 * afterwards.
 * 
 * @param node node where removed data was
 * @param parent parent of node
 * @param index index where node is located
 */
template <typename T>
void BPlusTree<T>::borrowInternalFromPrev(Node*& node, Node*& parent, int index) {
    Node* prev = parent->children[index - 1];

    node->keys.insert(node->keys.begin(), parent->keys[index - 1]);
    node->children.insert(node->children.begin(), prev->children.back());

    parent->keys[index - 1] = prev->keys.back();

    prev->keys.pop_back();
    prev->children.pop_back();
}

/**
 * Borrow right sibling data for internal nodes.
 * 
 * We insert the parent data into given node and
 * take the parents left child node.
 * 
 * We then take the smallest child in the right sibling
 * node to update parent and remove that child
 * afterwards.
 * 
 * @param node node where removed data was
 * @param parent parent of node
 * @param index index where node is located
 */
template <typename T>
void BPlusTree<T>::borrowInternalFromNext(Node*& node, Node*& parent, int index) {
    Node* next = parent->children[index + 1];

    node->keys.push_back(parent->keys[index]);
    node->children.push_back(next->children.front());

    parent->keys[index] = next->keys.front();

    next->keys.erase(next->keys.begin());
    next->children.erase(next->children.begin());
}

/**
 * Merge function for internal nodes.
 * 
 * We check right then left for an available
 * sibling merging data.
 * We merge the siblings and their child pointers
 * then bringing down the parent into the node.
 * 
 * @param node node where removed data was
 * @param parent parent of node
 * @param index index where node is located
 */
template <typename T>
void BPlusTree<T>::mergeInternal(Node*& node, Node*& parent, int index) {
    if (index + 1 < parent->children.size()) {
        Node* next = parent->children[index + 1];

        node->keys.push_back(parent->keys[index]);
        node->keys.insert(node->keys.end(), next->keys.begin(), next->keys.end());
        node->children.insert(node->children.end(), next->children.begin(), next->children.end());

        parent->keys.erase(parent->keys.begin() + index);
        parent->children.erase(parent->children.begin() + index + 1);

        delete next;
    }
    else if (index > 0) {
        Node* prev = parent->children[index - 1];

        prev->keys.push_back(parent->keys[index - 1]);
        prev->keys.insert(prev->keys.end(), node->keys.begin(), node->keys.end());
        prev->children.insert(prev->children.end(), node->children.begin(), node->children.end());

        parent->keys.erase(parent->keys.begin() + index - 1);
        parent->children.erase(parent->children.begin() + index);

        delete node;
    }
}

/**
 * Caller function for acutal remove function.
 * 
 * Removes root if it is null calls 2-arg remove
 * function.
 * 
 * @param key data to remove
 */
template <typename T>
void BPlusTree<T>::remove(T key) {
    if (root == nullptr) {
        return;
    }

    Node* parent = nullptr;
    remove(root, parent, key, 0);

    if (!root->isLeaf && root->keys.empty()) {
        Node* oldRoot = root;
        root = root->children[0];
        delete oldRoot;
    }
}
