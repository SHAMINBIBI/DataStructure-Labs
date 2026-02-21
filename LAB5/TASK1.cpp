#include <iostream>
using namespace std;
template <typename T>
struct node {
    T data;
    node<T>* left;
    node<T>* right;
};
template <typename T>
class BST {
private:
    node<T>* root;    
public:
    BST() {
        root = nullptr;
    }    
    node<T>* createNode(T val) {
        node<T>* newNode = new node<T>;
        newNode->data = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }    
    node<T>* insert(node<T>* btNode, T val) {
        if(btNode == nullptr) {
            node<T>* newNode = createNode(val);
            return newNode;
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
    void inorder(node<T>* root) {
        if(root) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }    
    void inorderTraverse() {
        inorder(root);
        if(root == nullptr) {
            cout << "Tree is empty";
        }
        cout << endl;
    }    
    void preorder(node<T>* root) {
        if(root) {
            cout << root->data << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }    
    void preorderTraverse() {
        preorder(root);
        cout << endl;
    }    
    void postorder(node<T>* root) {
        if(root) {
            postorder(root->left);
            postorder(root->right);
            cout << root->data << " ";
        }
    }   
    void postorderTraverse() {
        postorder(root);
        cout << endl;
    }    
    node<T>* findNode(node<T>* root, T val) {
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
        node<T>* result = findNode(root, val);
        if(result) {
            cout << "Element found" << endl;
            return true;
        } else {
            cout << "Element not found" << endl;
            return false;
        }
    }   
    node<T>* findMin(node<T>* root) {
        while(root && root->left != nullptr) {
            root = root->left;
        }
        return root;
    }    
    node<T>* deleteNode(node<T>* root, T val) {
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
                node<T>* temp = root->right;
                delete root;
                return temp;
            } else if(root->right == nullptr) {
                node<T>* temp = root->left;
                delete root;
                return temp;
            } else {
                node<T>* temp = findMin(root->right);
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
    node<T>* copyTree(node<T>* originalRoot) {
        if(originalRoot == nullptr) {
            return nullptr;
        }
        node<T>* newNode = createNode(originalRoot->data);
        newNode->left = copyTree(originalRoot->left);
        newNode->right = copyTree(originalRoot->right);
        return newNode;
    }   
    BST(const BST &other) {
        root = copyTree(other.root);
    }   
    void freeTree(node<T>* root) {
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
        if(root == nullptr) {
            return true;
        } else {
            return false;
        }
    }
};
int main() {
    BST<int> tree1;    
    tree1.insert(21);  // Insert numbers 21, 22, 10, 19, 17
    tree1.insert(22);
    tree1.insert(10);
    tree1.insert(19);
    tree1.insert(17);   
    tree1.inorderTraverse();   // Inorder Traverse 
    tree1.preorderTraverse();  // Preorder Traverse 
    tree1.postorderTraverse(); // Postorder Traverse    
    tree1.search(6);  // Search 6 in the tree
    tree1.search(21); // Search 21 in the tree   
    tree1.insert(22); // Insert 22 in the tree   
    tree1.remove(78); // Delete 78 from the tree
    tree1.remove(10); // Delete 10 from the tree    
    tree1.inorderTraverse(); // Inorder Traverse    
    cout << tree1.isEmpty() << "\n1.Tree Empty 0.Tree Not Empty" << endl;  
    BST<int> tree2(tree1); // Create a tree copyTree from tree1  
    cout << tree2.isEmpty() << "\n1.Copy Empty 0.Copy Not Empty" << endl;    
    tree2.remove(17); // Delete 17 from copyTree    
    tree1.inorderTraverse(); // Inorder Traverse myTree
    tree2.inorderTraverse(); // Inorder Traverse copyTree  
    tree2.remove(19); // Delete 19 from copyTree
    tree2.remove(21); // Delete 21 from copyTree
    tree2.remove(22); // Delete 22 from copyTree   
    tree2.inorderTraverse(); // Inorder Traverse copyTree
    tree1.inorderTraverse(); // Inorder Traverse myTree
    tree1.preorderTraverse(); // Preorder Traverse myTree
    tree1.postorderTraverse(); // Postorder Traverse myTree   
    return 0;
}