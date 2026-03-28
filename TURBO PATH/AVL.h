#ifndef AVL_H
#define AVL_H
#pragma once
#include <iostream>

using namespace std;

template <class KeyType, class ValueType>
struct ANode {   
    KeyType data;     // Search key (the filename)
    ValueType value;  // The actual FileNode pointer
    int height;
    ANode<KeyType, ValueType> *left;
    ANode<KeyType, ValueType> *right;
    
    // Constructor to initialize a new node
    ANode(KeyType d, ValueType v) {
        data = d;
        value = v;
        height = 1; // New nodes start at height 1
        left = nullptr;
        right = nullptr;
    }
};

template <class KeyType, class ValueType>
class AVL { 
private:
    ANode<KeyType, ValueType> *root;

    // Simple height check that handles null pointers
    int height(ANode<KeyType, ValueType> *node) { 
        if(node == nullptr) return 0;
        return node->height;
    }

    // To find the larger of two numbers
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // Calculates the balance factor
    int getBalance(ANode<KeyType, ValueType> *node) {
        if(node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    // Standard Right Rotation
    ANode<KeyType, ValueType>* rightRotate(ANode<KeyType, ValueType> *y) {
        ANode<KeyType, ValueType> *x = y->left;
        ANode<KeyType, ValueType> *t = x->right;
        
        x->right = y;
        y->left = t;
        
        // Update heights 
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        
        return x;
    }

    // Standard Left Rotation 
    ANode<KeyType, ValueType>* leftRotate(ANode<KeyType, ValueType> *x) {
        ANode<KeyType, ValueType> *y = x->right;
        ANode<KeyType, ValueType> *t = y->left; 
        
        y->left = x;
        x->right = t;
        
        // Update heights 
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        
        return y;
    }

    // Recursive helper to handle  insertion and AVL rebalancing
    ANode<KeyType, ValueType>* insertHelper(ANode<KeyType, ValueType> *node, KeyType d, ValueType v) {
        //  To do normal BST insertion logic
        if(node == nullptr) return new ANode<KeyType, ValueType>(d, v);
        
        if (d < node->data) 
            node->left = insertHelper(node->left, d, v);
        else if (d > node->data) 
            node->right = insertHelper(node->right, d, v);
        else 
            return node; // Duplicate keys are ignored by the tree 
        
        //  Update node height
        node->height = 1 + max(height(node->left), height(node->right));
        
        //  Check balance and perform rotations if needed
        int balance = getBalance(node); 
        
        // Left Left Case
        if(balance > 1 && d < node->left->data) return rightRotate(node);     
        
        // Right Right Case
        if(balance < -1 && d > node->right->data) return leftRotate(node);
        
        // Left Right Case
        if(balance > 1 && d > node->left->data) {   
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if(balance < -1 && d < node->right->data) { 
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }

    // Recursive search to find a specific key
    ValueType* searchHelper(ANode<KeyType, ValueType>* node, KeyType d) {
        if (node == nullptr) return nullptr;
        
        // If found, return the address of the value field
        if (node->data == d) return &(node->value); 
        
        if (d < node->data) return searchHelper(node->left, d);
        return searchHelper(node->right, d);
    }

    // Post-order traversal to delete every node and free memory
    void clearHelper(ANode<KeyType, ValueType>* node) {
        if (node != nullptr) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }

public:
    AVL() { root = nullptr; }
    
    // Destructor ensures no memory leaks when the tree goes out of scope
    ~AVL() { clear(); }

    // Public wrapper for insertion
    void insert(KeyType d, ValueType v) { 
        root = insertHelper(root, d, v); 
    }
    
    // Public wrapper for search
    ValueType* search(KeyType d) { 
        return searchHelper(root, d); 
    }
    
    // Public wrapper to manually reset the tree
    void clear() {
        clearHelper(root);
        root = nullptr;
    }
};

#endif