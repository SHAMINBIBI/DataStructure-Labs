#include <iostream>
using namespace std;
template <class T>
struct ANode {   
    T data;
    int height;
    ANode<T> *left;
    ANode<T> *right;
    ANode() { 
        data = T();
        height = 1;
        left = nullptr;
        right = nullptr;
    } 
    ANode(T d) {
        data = d;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};
template <class T>
class AVL { 
private:
    ANode<T> *root;
    //   Private Helper Functions 
    int height(ANode<T> *node) { 
        if(node == nullptr) return 0;
        return node->height;
    }
    int max(int a, int b) {
        return (a > b) ? a : b;
    }
    int getBalance(ANode<T> *node) {
        if(node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }
    ANode<T>* rightRotate(ANode<T> *y) {
        ANode<T> *x = y->left;
        ANode<T> *t = x->right;     
        x->right = y;
        y->left = t;     
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));       
        return x;
    }
    ANode<T>* leftRotate(ANode<T> *x) {
        ANode<T> *y = x->right;
        ANode<T> *t = y->left;      
        y->left = x;
        x->right = t;      
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));      
        return y;
    }
    // ADT FUNCTIONS 
    ANode<T>* insertHelper(ANode<T> *node, T d) {
        if(node == nullptr) return new ANode<T>(d);     
        if (d < node->data) {
            node->left = insertHelper(node->left, d);
        }
        else if (d > node->data) {
            node->right = insertHelper(node->right, d);
        }
        else {
            return node; // Duplicates not allowed in standard AVL
        }        
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);         
        // Rotations
        if(balance > 1 && d < node->left->data) return rightRotate(node);     
        if(balance < -1 && d > node->right->data) return leftRotate(node);
        if(balance > 1 && d > node->left->data) {   
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if(balance < -1 && d < node->right->data) { 
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    // Helper to find the smallest node 
    ANode<T>* minVal(ANode<T>* node) {
        ANode<T>* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    ANode<T>* removeHelper(ANode<T>* node, T d) {
        if (node == nullptr) return node;
        if (d < node->data) {
            node->left = removeHelper(node->left, d);
        }
        else if (d > node->data) {
            node->right = removeHelper(node->right, d);
        }
        else {
            if ((node->left == nullptr) || (node->right == nullptr)) {
                ANode<T>* temp = node->left ? node->left : node->right;
                if (temp == nullptr) { // No children
                    temp = node;
                    node = nullptr;
                } else { // One child
                    *node = *temp; // Copy child data
                }
                delete temp;
            }
            else { // Two children
                // Get inorder successor (smallest in right subtree)
                ANode<T>* temp = minVal(node->right);
                node->data = temp->data; // Copy successor data to this node
                node->right = removeHelper(node->right, temp->data); // Delete successor
            }
        }
        if (node == nullptr) return node;
       
        node->height = 1 + max(height(node->left), height(node->right));

        
        int balance = getBalance(node);

        //  Rotations
        // Left Left 
        if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
        // Left Right 
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Right 
        if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
        // Right Left 
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    ANode<T>* searchHelper(ANode<T>* node, T d) {
        // Base Case: root is null or d is present at root
        if (node == nullptr || node->data == d) {
            return node;
        }
        // d is greater than root's d
        if (node->data < d) {
            return searchHelper(node->right, d);
        }
        // d is smaller than root's d
        return searchHelper(node->left, d);
    }
    void clearHelper(ANode<T>* node) {
        if (node != nullptr) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }
    void preOrderHelper(ANode<T> *node) {
        if(node != nullptr) {
            cout << node->data << " "; 
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }
public:
    // Constructor
    AVL() { 
        root = nullptr;
    }
    // Destructor 
    ~AVL() {
        clear();
    }
    void insert(T d) {
        root = insertHelper(root, d);
    }
    void remove(T d) {
        root = removeHelper(root, d);
    }
    bool search(T d) {
        ANode<T>* result = searchHelper(root, d);
        return (result != nullptr); // Returns true if found, false if not
    }
    void clear() {
        clearHelper(root);
        root = nullptr;
    }
    void printPreOrder() {
        if (root == nullptr) {
            cout << "Tree is empty.";
        } else {
            preOrderHelper(root);
        }
        cout << endl;
    }
};
int main() {
    AVL<int> myTree;
    myTree.insert(10);
    myTree.insert(20);
    myTree.insert(30);
    myTree.insert(40);
    myTree.insert(50);
    myTree.insert(25);
    
    cout << "PreOrder Traversal: ";
    myTree.printPreOrder(); // Should output properly balanced tree

    // Test Search
    cout << "\n--- SEARCHING ---" << endl;
    if (myTree.search(30)) cout << "Found 30 in the tree!" << endl;
    else cout << "30 not found." << endl;

    if (myTree.search(99)) cout << "Found 99 in the tree!" << endl;
    else cout << "99 not found." << endl;

    // Test Deletion
    cout << "\n--- DELETING ---" << endl;
    cout << "Deleting 30..." << endl;
    myTree.remove(30);
    cout << "PreOrder Traversal after deleting 30: ";
    myTree.printPreOrder();

    // Test Clear
    cout << "\n--- CLEARING TREE ---" << endl;
    myTree.clear();
    myTree.printPreOrder();

    return 0;
}