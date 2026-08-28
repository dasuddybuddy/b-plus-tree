#include "int_bpt_wrapper.h"
#include "../../include/BPlusTree.h"

BPTHandle bpt_create(int degree) {
    return new BPlusTree<int>(degree);
}

void bpt_destory(BPTHandle tree) {
    delete static_cast<BPlusTree<int>*>(tree);
}
void bpt_insert(BPTHandle tree, int key) {
    auto* bpt = static_cast<BPlusTree<int>*>(tree);
    bpt->insert(key);
}
void bpt_search(BPTHandle tree, int key) {
    auto* bpt = static_cast<BPlusTree<int>*>(tree);
    bpt->search(key);
}
void bpt_remove(BPTHandle tree, int key) {
    auto* bpt = static_cast<BPlusTree<int>*>(tree);
    bpt->remove(key);
}

