/**
 * Search for a value in tree.
 * 
 * This method will search assuming all data is stored
 * at the leaves. It creates a pointer towards the root
 * and iterates through tree until it reaches leaf node.
 * Then it iterates through leaf until value is found if
 * not return false.
 * 
 * @param key value being searched for
 * @return if value is in tree
 */
template <typename T>
bool BPlusTree<T>::search(T key) {
    Node* cur {root};

    while (!cur->isLeaf) {
        int idx = 0;
        while (idx < cur->keys.size() && key >= cur->keys[idx]) {
            idx++;
        }
        cur = cur->children[idx];
    }
    for (const T& val : cur->keys) {
        if (val == key) {
            return true;
        }
    }
    return false;
}

/**
 * Returns elements within a range.
 * 
 * We traverse the tree then iterate through the 
 * leaves of the tree until we find the first occurence 
 * of a child that is greater than or equal to the
 * lower bound of the query. We traverse leaves until
 * upper bound is violated
 * 
 * @param lower lower bound of query
 * @param upper upper bound of query
 * @return a vector of elements queried within range
 */
template <typename T>
std::vector<T> BPlusTree<T>::rangeQuery(T lower, T upper) {
    Node* cur = root;
    std::vector<T> query;

    while (cur != nullptr) {
        int idx {0};
        while (idx < cur->keys.size() && lower >= cur->keys[idx]) {
            idx++;
        }
        if (cur->isLeaf) {
            break;
        }
        cur = cur->children[idx];
    }

    while (cur != nullptr) {
        for (const T& val : cur->keys) {
            if (val >= lower && val <= upper) {
                query.push_back(val);
            }
            else {
                return query;
            }
        }
        cur = cur->next;
    }
    return query;
}
