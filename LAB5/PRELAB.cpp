#include <iostream>
#include <string>
using namespace std;
struct Book {
    int id;
    string title;
    string author;
    int popularity;  
    Book() {
        id = 0;
        title = "";
        author = "";
        popularity = 0;
    }  
    Book(int bookId, string bookTitle, string bookAuthor, int popScore) {
        id = bookId;
        title = bookTitle;
        author = bookAuthor;
        popularity = popScore;
    }  
    bool operator<(const Book& other) const {  // Overloading < operator for BST ordering by popularity
        if(popularity == other.popularity) {
            return id < other.id;  // If same popularity, order by ID
        }
        return popularity < other.popularity;
    } 
    bool operator>(const Book& other) const {
        if(popularity == other.popularity) {
            return id > other.id;
        }
        return popularity > other.popularity;
    }   
    bool operator==(const Book& other) const {
        return id == other.id;  // Books are uniquely identified by ID
    }
    friend ostream& operator<<(ostream& os, const Book& book) {   // For outputting book details
        os << "ID: " << book.id << ", Title: " << book.title 
           << ", Author: " << book.author << ", Popularity: " << book.popularity;
        return os;
    }
};
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
        }   }       
    void insert(T val) {
        if(search(val)) {
            cout << "Book with ID " << val.id << " already exists!" << endl;
            return;
        }
        root = insert(root, val);
        cout << "Book \"" << val.title << "\" added successfully!" << endl;
    }      
    void inorder(node<T>* root) {
        if(root) {
            inorder(root->left);
            cout << root->data << endl;
            inorder(root->right);
        }
    }       
    void inorderTraverse() {
        if(root == nullptr) {
            cout << "Catalog is empty!" << endl;
            return;
        }
        cout << "\nAll Books Sorted by Popularity" << endl;
        inorder(root);
        cout  << endl;
    }       
    void preorder(node<T>* root) {
        if(root) {
            cout << root->data << endl;
            preorder(root->left);
            preorder(root->right);
        }
    }     
    void preorderTraverse() {
        if(root == nullptr) {
            cout << "Catalog is empty!" << endl;
            return;
        }
        cout << "\nPreorder Traversal" << endl;
        preorder(root);
        cout  << endl;
    }      
    void postorder(node<T>* root) {
        if(root) {
            postorder(root->left);
            postorder(root->right);
            cout << root->data << endl;
        }
    }      
    void postorderTraverse() {
        if(root == nullptr) {
            cout << "Catalog is empty!" << endl;
            return;
        }
        cout << "\nPostorder Traversal" << endl;
        postorder(root);
        cout << endl;
    }    
    node<T>* findNodeByValue(node<T>* root, T val) {
        if(root == nullptr) {
            return nullptr;
        }
        if(root->data == val) {
            return root;
        }
        if(val < root->data) {
            return findNodeByValue(root->left, val);
        } else {
            return findNodeByValue(root->right, val);
        }
    }   
    bool search(T val) {
        node<T>* result = findNodeByValue(root, val);
        if(result) {
            cout << "Book found:" << endl;
            cout << result->data << endl;
            return true;
        } else {
            cout << "Book not found!" << endl;
            return false;
        }
    }       
    node<T>* searchByPopularity(node<T>* root, int popularity, int id = -1) {
    if(root == nullptr) {
        return nullptr;
    } 
    if(popularity < root->data.popularity) {
        return searchByPopularity(root->left, popularity, id);
    } else if(popularity > root->data.popularity) {
        return searchByPopularity(root->right, popularity, id);
    } else {
        if(root->data.id == id) {
            return root;
        }
        // First try the left subtree
        node<T>* leftResult = searchByPopularity(root->left, popularity, id);
        if(leftResult) return leftResult;
        // Then try the right subtree
        return searchByPopularity(root->right, popularity, id);
    }
}  
    void searchByPopularity(int popularity) {
        node<T>* result = searchByPopularity(root, popularity);
        if(result) {
            cout << "Book found with popularity " << popularity << ":" << endl;
            cout << result->data << endl;
        } else {
            cout << "No book found with popularity: " << popularity << endl;
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
            cout << "Book not found in catalog!" << endl;
            return;
        }
        root = deleteNode(root, val);
        cout << "Book removed successfully!" << endl;
    }  
    void remove(int popularity, int id) {  // Remove by popularity and ID
    Book searchBook(id, "", "", popularity);
    node<T>* result = searchByPopularity(root, popularity, id);
    if(result == nullptr) {
        cout << "Book not found in catalog!" << endl;
        return;
    }
    string bookTitle = result->data.title;  // Store title before deletion
    root = deleteNode(root, searchBook);
    cout << "Book \"" << bookTitle << "\" removed successfully!" << endl;
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
            cout << "Catalog is empty" << endl;
            return true;
        } else {
            cout << "Catalog is not empty" << endl;
            return false;
        }
    }  
    int countNodes(node<T>* root) {
        if(root == nullptr) {
            return 0;
        }
        return 1 + countNodes(root->left) + countNodes(root->right);
    }  
    int countNodes() {
        int count = countNodes(root);
        cout << "Total books in catalog: " << count << endl;
        return count;
    } 
    void topKBooks(node<T>* root, int& count, int k) {
        if(root == nullptr || count >= k) {
            return;
        }     
        topKBooks(root->right, count, k);
        if(count < k) {
            cout << root->data << endl;
            count++;
        }
        topKBooks(root->left, count, k);
    }  
    void topKBooks(int k) {  
        if(root == nullptr) {
            cout << "Catalog is empty!" << endl;
            return;
        }
        if(k <= 0) {
            cout << "Invalid value of k!" << endl;
            return;
        }
        int total = countNodes(root);
        if(k > total) {
            cout << "k is greater than total books. Displaying all books:" << endl;
            inorderTraverse();
            return;
        }     
        cout << "\nTop " << k << " Books (Highest Popularity)" << endl;
        int count = 0;
        topKBooks(root, count, k);
        cout  << endl;
    }  
    void rangeQuery(node<T>* root, int minScore, int maxScore) { 
        if(root == nullptr) {
            return;
        }   
        if(root->data.popularity > minScore) {
            rangeQuery(root->left, minScore, maxScore);
        }  
        if(root->data.popularity >= minScore && root->data.popularity <= maxScore) {
            cout << root->data << endl;
        }
        if(root->data.popularity < maxScore) {
            rangeQuery(root->right, minScore, maxScore);
        }
    }
    void rangeQuery(int minScore, int maxScore) {
        if(root == nullptr) {
            cout << "Catalog is empty!" << endl;
            return;
        }
        if(minScore > maxScore) {
            cout << "Invalid range: minScore > maxScore" << endl;
            return;
        }
        cout << "\nBooks with Popularity between " << minScore << " and " << maxScore  << endl;
        rangeQuery(root, minScore, maxScore);
        cout  << endl;
    }
};
int main() {
    BST<Book> catalog;   
    cout << "Maktaba-e-Meen Library Management System" << endl;
    catalog.insert(Book(101, "The Great Gatsby", "F. Scott Fitzgerald", 85));
    catalog.insert(Book(102, "Bab e Dehar","Merunnisa", 92));
    catalog.insert(Book(103, "A Thousand Splendid Suns", "Khaled Hosseini", 78));
    catalog.insert(Book(104, "Jannat ke Pattay","Umera Ahmed", 88));
    catalog.insert(Book(105, "The Kite Runner", "Khaled Hosseini", 72));
    catalog.insert(Book(106, "Bakht","Merhrunnisa", 65));
    catalog.insert(Book(107, "Maze Runner", "James Dashner", 95));
    catalog.insert(Book(108, "The Hobbit", "J.R.R. Tolkien", 89));
    catalog.insert(Book(109, "Ab e Hayat","Nimra Ahmed", 82));
    catalog.insert(Book(110, "Brave New World", "Aldous Huxley", 79));
    cout << "INORDER TRAVERSAL:" << endl;
    catalog.inorderTraverse();
    cout << "\nTOTAL BOOKS: " ;
    catalog.countNodes();
    cout<< "\nSEARCH BY ID: " << endl;
    catalog.search(Book(102, "", "", 0)); 
    cout << "\nSEARCH BY POPULARITY : " ;
    catalog.searchByPopularity(88);
    cout << "\nTOP 3 OF HIGH POP." << endl;
    catalog.topKBooks(3);
    cout << "\nRANGE QUERY (75 to 90):" << endl;
    catalog.rangeQuery(75, 90);   
    cout << "\nREMOVE A BOOK (ID: 108, Popularity: 89)" ;
    catalog.remove(89, 108); 
    cout << "\nDISPLAY ALL BOOKS AFTER REMOVAL:" << endl;
    catalog.inorderTraverse();
    cout << "\nCOUNT NODES AFTER REMOVAL:" << endl;
    catalog.countNodes();
    cout << "\nCHECK IF CATALOG IS EMPTY:" << endl;
    catalog.isEmpty();
    cout << "\nINSERTING A DUPLICATE BOOK (ID: 101)" << endl;
    catalog.insert(Book(101, "The Great Gatsby", "F. Scott Fitzgerald", 85));
    cout << endl; 
    return 0;
}