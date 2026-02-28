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
    node<T>* copyTree(node<T>* originalRoot) {
        if(originalRoot == nullptr) {
            return nullptr;
        }
        node<T>* newNode = createNode(originalRoot->data);
        newNode->left = copyTree(originalRoot->left);
        newNode->right = copyTree(originalRoot->right);
        return newNode;
    }   
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
            return;}
        else
        {cout<< "Element  inserted\n";
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
            cout << "Element = " << val << " exists in tree" << endl;
            return true;
        } else {
            cout << "Element= " << val << " does not exist in the tree" << endl;
            return false;
        }
    }   
    node<T>* findMin(node<T>* root) {
        while(root && root->left != nullptr) {
            root = root->left;
        }
        return root;
    }  
    node <T>* findMax(node<T>*root)
    {
        while (root && root->right !=nullptr)
        {
            root= root->right;
        }
        return root;
    } 
    T getMax() {
     if (root == nullptr) {
         cout<< "Tree is empty\n";
         return T(); 
    }
    node<T>* maxNode = findMax(root);
    return maxNode->data;
}

    T getMin() {    
     if (root == nullptr) {
         cout<< "Tree is empty\n";
         return T(); 
    }
    node<T>* minNode = findMin(root);
    return minNode->data;
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
    int calculateHeight(node<T>* root) {
        if (root == nullptr)
        {
            return 0;
        }
        else 
        {
            int leftHeight = calculateHeight(root->left);
            int rightHeight = calculateHeight(root->right);
            return max(leftHeight, rightHeight) + 1;
        }
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
    node <T>* getRoot()
    {
        return root;
    }
    bool isEmpty() {
        if(root == nullptr) {
            return true;
        } else {
            return false;
        }
    }
};
int main()
{   BST<int> myTree;
    int arr[] = {100, 50, 150, 20, 75};
    int n = sizeof(arr) / sizeof(arr[0]);
    for(int i = 0; i < n; i++) {  //Constructing BST from array
        myTree.insert(arr[i]);    //recursve func call
    }
    cout << "\nIn-order Traversal:" << endl;
    myTree.inorderTraverse();
    myTree.search(55);  // Existing element
    myTree.search(100); // Non-existing element
    cout << "Height of the BST: " << myTree.calculateHeight(myTree.getRoot()) << endl;
    cout << "Min Element: " << myTree.getMin() << endl;
    cout << "Max Element: " << myTree.getMax() << endl;
    return 0;

}