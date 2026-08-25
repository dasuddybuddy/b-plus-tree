#include "../include/BPlusTree.h"

#include <iostream>

using namespace std;

int main() {

    BPlusTree<int> tree(2);

    int choice;
    int key;
    int upper;
    int lower;
    vector<int> res;

    while (true) {

        cout << "\n===== B+ Tree =====\n";
        cout << "1. Insert\n";
        cout << "2. Remove\n";
        cout << "3. Search\n";
        cout << "4. Query\n";
        cout << "5. Print Tree\n";
        cout << "6. Exit\n";
        cout << "Choice: ";

        cin >> choice;

        switch (choice) {

            case 1:
                cout << "Enter key to insert: ";
                cin >> key;

                tree.insert(key);

                cout << "Inserted " << key << "\n";
                break;


            case 2:
                cout << "Enter key to remove: ";
                cin >> key;

                tree.remove(key);

                cout << "Removed " << key << "\n";
                break;


            case 3:
                cout << "Enter key to search: ";
                cin >> key;

                if (tree.search(key)) {
                    cout << key << " exists in the tree.\n";
                } else {
                    cout << key << " does not exist in the tree.\n";
                }

                break;


            case 4:
                cout << "Enter lower bound: ";
                cin >> lower;
                cout << "Enter upper bound: ";
                cin >> upper;

                res = tree.rangeQuery(lower, upper);

                for (const int& val : res) {
                    cout << val << " ";
                }
                cout << '\n';
                break;

            case 5:
                cout << "\nB+ Tree:\n";
                tree.printTree();
                break;
            
            case 6:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }
}
