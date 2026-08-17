template <typename T>
bool BPlusTree<T>::search(T key) {
    Node* cur = root;

    while (cur != nullptr) {
        int idx = 0;
        while (idx < cur->keys.size() && key > cur->keys[idx]) {
            idx++;
        }
        if (idx < cur->keys.size() && cur->keys[idx].size() == key) {
            return true;
        }
        if (cur->isLeaf) {
            return false;
        }
        cur = cur->children[idx];
    }
}

template <typename T>
std::vector<T> BPlusTree<T>::rangeQuery(T lower, T upper) {
    Node* cur = root;
    std::vector<T> query;

    while (cur != nullptr) {
        int idx = 0;
        while (idx < cur->keys.size() && lower > cur->keys[idx]) {
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
