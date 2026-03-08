#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;

template <typename T>
struct bst_node {  // Changed from 'node' to 'bst_node'
    T data;
    bst_node<T>* left;
    bst_node<T>* right;
};

template <typename T>
class BST {
private:
    bst_node<T>* root;  // Updated type
    
public:
    BST() {
        root = nullptr;
    }
    
    bst_node<T>* createNode(T val) {  // Updated return type
        bst_node<T>* newNode = new bst_node<T>;
        newNode->data = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    
    bst_node<T>* insert(bst_node<T>* btNode, T val) {  // Updated parameter type
        if(btNode == nullptr) {
            return createNode(val);
        } else { 
            if (val < btNode->data) {
                btNode->left = insert(btNode->left, val);
            } else if (val > btNode->data) {
                btNode->right = insert(btNode->right, val);
            }
            return btNode;
        }
    }
    
    void insert(T val) {
        if(search(val)) {
            cout << "Number already exists" << endl;
            return;
        }
        root = insert(root, val);
    }
    
    void inorder(bst_node<T>* root) {  // Updated parameter type
        if(root) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }
    
    T inorderTraverse() {
        inorder(root);
        if(root == nullptr) {
            cout << "Tree is empty";
        }
        cout << endl;
        return root;
    }
    
    void preorder(bst_node<T>* root) {  // Updated parameter type
        if(root) {
            cout << root->data << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }
    
    T preorderTraverse() {
        preorder(root);
        cout << endl;
        return root;
    }
    
    void postorder(bst_node<T>* root) {  // Updated parameter type
        if(root) {
            postorder(root->left);
            postorder(root->right);
            cout << root->data << " ";
        }
    }
    
    T postorderTraverse() {
        postorder(root);
        cout << endl;
        return root;
    }
    
    bst_node<T>* findNode(bst_node<T>* root, T val) {  // Updated return/parameter types
        if(root == nullptr) {
            return nullptr;
        }
        if(root->data == val) {
            return root;
        }
        if(val < root->data) {
            return findNode(root->left, val);
        } else {
            return findNode(root->right, val);
        }
    }
    
    bool search(T val) {
        bst_node<T>* result = findNode(root, val);  // Updated type
        if(result) {
            cout << "Element found" << endl;
            return true;
        } else {
            cout << "Element not found" << endl;
            return false;
        }
    }
    
    bst_node<T>* findMin(bst_node<T>* root) {  // Updated return/parameter types
        while(root && root->left != nullptr) {
            root = root->left;
        }
        return root;
    }
    
    bst_node<T>* deleteNode(bst_node<T>* root, T val) {  // Updated parameter types
        if(root == nullptr) {
            return root;
        }
        
        if(val < root->data) {
            root->left = deleteNode(root->left, val);
        } else if(val > root->data) {
            root->right = deleteNode(root->right, val);
        } else {
            if(root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            } else if(root->left == nullptr) {
                bst_node<T>* temp = root->right;
                delete root;
                return temp;
            } else if(root->right == nullptr) {
                bst_node<T>* temp = root->left;
                delete root;
                return temp;
            } else {
                bst_node<T>* temp = findMin(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }
        return root;
    }
    
    void remove(T val) {
        if(!search(val)) {
            cout << "Element not found" << endl;
            return;
        }
        root = deleteNode(root, val);
    }
    
    bst_node<T>* copyTree(bst_node<T>* originalRoot) {  // Updated parameter types
        if(originalRoot == nullptr) {
            return nullptr;
        }
        bst_node<T>* newNode = createNode(originalRoot->data);
        newNode->left = copyTree(originalRoot->left);
        newNode->right = copyTree(originalRoot->right);
        return newNode;
    }
    
    BST(const BST &other) {
        root = copyTree(other.root);
    }
    
    void freeTree(bst_node<T>* root) {  // Updated parameter type
        if(root) {
            freeTree(root->left);
            freeTree(root->right);
            delete root;
        }
    }
    
    ~BST() {
        freeTree(root);
        root = nullptr;
    }
    
    bool isEmpty() {
        return root == nullptr;
    }
};
#endif