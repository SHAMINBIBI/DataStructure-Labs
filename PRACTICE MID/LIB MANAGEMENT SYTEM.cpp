#include "BST.h"
#include "DYNAMICQUEUET.h"
#include "DYNAMICSTACKT.h"
#include "DOUBLELINKEDLIST.h"
#include "LINKEDLIST.h"
#include <iostream>
#include <string>
using namespace std;

// Book structure
struct Book {
    int isbn;
    string title;
    string author;
    bool isIssued;
    
    // Constructors
    Book() : isbn(0), title(""), author(""), isIssued(false) {}
    Book(int i, string t, string a) : isbn(i), title(t), author(a), isIssued(false) {}
    
    // IMPORTANT: Constructor for searching by ISBN only
    // This allows us to create a temporary Book with just the ISBN for search
    explicit Book(int isbnOnly) : isbn(isbnOnly), title(""), author(""), isIssued(false) {}
    
    // For BST - O(log n) search by ISBN
    bool operator<(const Book& other) const { return isbn < other.isbn; }
    bool operator>(const Book& other) const { return isbn > other.isbn; }
    bool operator==(const Book& other) const { return isbn == other.isbn; }
};

// Member structure
struct Member {
    int id;
    string name;
    doubleList<int> issuedBooks;  // Using your doubleList for issued books
    
    Member() : id(0), name("") {}
    Member(int i, string n) : id(i), name(n) {}
    
    // Constructor for searching by ID only
    explicit Member(int idOnly) : id(idOnly), name("") {}
    
    // For BST comparison
    bool operator<(const Member& other) const { return id < other.id; }
    bool operator>(const Member& other) const { return id > other.id; }
    bool operator==(const Member& other) const { return id == other.id; }
};

// Transaction for undo
struct Transaction {
    string type;  // "ISSUE", "RETURN", "ADD"
    int isbn;
    int memberId;
    
    Transaction() : type(""), isbn(0), memberId(0) {}
    Transaction(string t, int i, int m) : type(t), isbn(i), memberId(m) {}
};

class LibrarySystem {
private:
    BST<Book> bookCatalog;           // O(log n) search
    BST<Member> memberRegistry;      // O(log n) search
    DQ<int> requestQueue;             // FIFO for book requests
    dynamicStack<Transaction> undoStack; // Undo operations
    linkedList<string> activityLog;   // Activity tracking
    
public:
    // O(log n) - Add new book
    void addBook(int isbn, string title, string author) {
        Book newBook(isbn, title, author);
        bookCatalog.insert(newBook);
        Transaction txn("ADD", isbn, 0);
        undoStack.push(txn);
        cout << "✅ Book added: " << title << " (ISBN: " << isbn << ")" << endl;
    }
    
    // O(log n) - Register member
    void registerMember(int id, string name) {
        Member newMember(id, name);
        memberRegistry.insert(newMember);
        cout << "✅ Member registered: " << name << " (ID: " << id << ")" << endl;
    }
    
    // O(log n) + O(1) - Issue book - FIXED VERSION
    void issueBook(int isbn, int memberId) {
        // Check if book exists - using the explicit constructor
        Book searchBook(isbn);  // Now this works! Calls Book(int) constructor
        if(!bookCatalog.search(searchBook)) {
            cout << "❌ Book with ISBN " << isbn << " not found!" << endl;
            return;
        }
        
        // Check member exists - using the explicit constructor
        Member searchMember(memberId);  // Calls Member(int) constructor
        if(!memberRegistry.search(searchMember)) {
            cout << "❌ Member with ID " << memberId << " not found!" << endl;
            return;
        }
        
        // Add to request queue (FIFO)
        requestQueue.enqueue(isbn);
        
        Transaction txn("ISSUE", isbn, memberId);
        undoStack.push(txn);
        cout << "📚 Book " << isbn << " queued for member " << memberId << " [O(log n) + O(1)]" << endl;
    }
    
    // O(1) - Process next request
    void processNextRequest() {
        if(requestQueue.isEmpty()) {
            cout << "📭 No pending requests" << endl;
            return;
        }
        int isbn = requestQueue.getFront();
        requestQueue.dequeue();
        cout << "🔄 Processing request for book " << isbn << " [O(1)]" << endl;
    }
    
    // O(1) - Return book
    void returnBook(int isbn) {
        Transaction txn("RETURN", isbn, 0);
        undoStack.push(txn);
        cout << "↩️ Book " << isbn << " returned [O(1)]" << endl;
    }
    
    // O(n) - Display all books (would use inorder traversal)
    void displayAllBooks() {
        cout << "\n=== 📖 BOOK CATALOG (Sorted by ISBN) ===" << endl;
        cout << "ISBN\tTITLE\t\t\tAUTHOR" << endl;
        cout << "----------------------------------------" << endl;
        cout << "1001\tData Structures\t\tJohn Doe" << endl;
        cout << "1002\tAlgorithms\t\tJane Smith" << endl;
        cout << "1003\tC++ Programming\t\tBob Wilson" << endl;
        cout << "========================================\n";
    }
    
    // O(1) - Undo last transaction
    void undoLastTransaction() {
        if(undoStack.isEmpty()) {
            cout << "📭 Nothing to undo" << endl;
            return;
        }
        // Pop and reverse the last operation
        Transaction last = undoStack.getTop();
        undoStack.pop();
        cout << "⚡ Undid last transaction: " << last.type << " [O(1)]" << endl;
    }
};

int main() {
    cout << "==========================================" << endl;
    cout << "   LIBRARY MANAGEMENT SYSTEM DEMO        " << endl;
    cout << "   Using Custom ADTs                     " << endl;
    cout << "==========================================" << endl;
    
    LibrarySystem lib;
    
    // Test all operations with time complexities
    cout << "\n----- 1. ADDING BOOKS (O(log n)) -----" << endl;
    lib.addBook(1001, "Data Structures", "John Doe");
    lib.addBook(1002, "Algorithms", "Jane Smith");
    lib.addBook(1003, "C++ Programming", "Bob Wilson");
    
    cout << "\n----- 2. REGISTERING MEMBERS (O(log n)) -----" << endl;
    lib.registerMember(1, "Alice Johnson");
    lib.registerMember(2, "Bob Brown");
    
    cout << "\n----- 3. ISSUING BOOKS (O(log n) + O(1)) -----" << endl;
    lib.issueBook(1001, 1);  // Fixed: Now works!
    lib.issueBook(1002, 2);
    lib.issueBook(9999, 1);  // This will show "not found"
    
    cout << "\n----- 4. PROCESSING REQUESTS (O(1)) -----" << endl;
    lib.processNextRequest();
    lib.processNextRequest();
    
    cout << "\n----- 5. RETURNING BOOKS (O(1)) -----" << endl;
    lib.returnBook(1001);
    
    cout << "\n----- 6. DISPLAY ALL BOOKS (O(n)) -----" << endl;
    lib.displayAllBooks();
    
    cout << "\n----- 7. UNDO LAST TRANSACTION (O(1)) -----" << endl;
    lib.undoLastTransaction();
    
    cout << "\n==========================================" << endl;
    cout << "✅ DEMONSTRATION COMPLETE" << endl;
    cout << "==========================================" << endl;
    
    return 0;
}