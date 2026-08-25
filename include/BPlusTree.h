#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/**
 * B+ Tree Class
 */
template <typename T> class BPlusTree {
private:
    /**
     * Node structure for B+ Tree
     */
    struct Node {
        bool isLeaf;
        std::vector<T> keys;
        std::vector<Node*> children;
        Node* next;

        /**
         * Construct Node object
         */
        Node(bool leaf = false) : isLeaf(leaf), next(nullptr) {}
    };

    Node* root;
    // Minimum degree (defines the range for the number of
    // keys)
    int minDegree;

    // Function to split a child node
    void splitChild(Node* parent, int index, Node* child);

    // Function to insert a key in a non-full node
    void insertNonFull(Node* node, T key);

    // Function to remove a key from a node
    void remove(Node* node, Node* parent, T key, int index);

    // Function to borrow a key from the previous sibling
    void borrowFromPrev(Node* node, Node* parent, int index);

    // Function to borrow a key from the next sibling
    void borrowFromNext(Node* node, Node* parent, int index);

    // Function to merge two nodes
    void merge(Node* node, Node* parent, int index);

    // Function to borrow a key from previous sibling (internal nodes)
    void borrowInternalFromPrev(Node* node, Node* parent, int index);

    // Function to borrow a key from next sibling (internal nodes)
    void borrowInternalFromNext(Node* node, Node* parent, int index);

    // Function to merge two internal nodes
    void mergeInternal(Node* node, Node* parent, int index);

    // Function to print the tree
    void printTree(Node* node, int level, bool isLast, std::string prefix);

public:
    BPlusTree(int degree): root(nullptr), minDegree(degree){}

    void insert(T key);
    bool search(T key);
    void remove(T key);
    std::vector<T> rangeQuery(T lower, T upper);
    void printTree();

    size_t getKeySize() {
        return root->keys.size();
    }
    size_t getChildrenSize() {
        return root->children.size();
    }
    size_t getChildKeySize(int index) {
        return root->children[index]->keys.size();
    }
};

#include "../implementation/insertion.tpp"
#include "../implementation/query.tpp"
#include "../implementation/remove.tpp"
#include "../implementation/print.tpp"

#endif
