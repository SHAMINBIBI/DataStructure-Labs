#include <iostream>
#include <string>

using namespace std;

// ============================================================
// 1. REVISION STRUCTURE
// ============================================================
struct Revision {
    int revNumber;
    string content;
    Revision() : revNumber(0), content("") {}
    Revision(int n, string c) : revNumber(n), content(c) {}
};

// ============================================================
// 2. DYNAMIC STACK ADT (Your Code)
// ============================================================
template <class T>
struct StackNode {
    T data;
    StackNode<T>* next;
    StackNode(T d) : data(d), next(NULL) {}
};

template <class S>
class dynamicStack {
    StackNode<S>* top;
public:
    dynamicStack() : top(NULL) {}
    bool isEmpty() { return (top == NULL); }
    void push(S d) {
        StackNode<S>* newNode = new StackNode<S>(d);
        newNode->next = top;
        top = newNode;
    }
    void pop() {
        if (isEmpty()) return;
        StackNode<S>* temp = top;
        top = top->next;
        delete temp;
    }
    S getTop() {
        if (isEmpty()) return S();
        return top->data;
    }
    ~dynamicStack() { while (!isEmpty()) pop(); }
};

// ============================================================
// 3. DOCUMENT CLASS (Metadata + Internal Stack)
// ============================================================
class Document {
public:
    int id;
    string title;
    string author;
    string status; // pending, approved, inreview, rejected
    dynamicStack<Revision> revisions;

    Document(int i, string t, string a) : id(i), title(t), author(a), status("pending") {}
    Document() : id(0), title(""), author(""), status("") {}

    // Overloading for BST logic (Requirement i)
    bool operator<(const Document& other) const { return id < other.id; }
    bool operator>(const Document& other) const { return id > other.id; }
    bool operator==(const Document& other) const { return id == other.id; }
};

// ============================================================
// 4. BST ADT (Your Code - Modified for Document Pointers)
// ============================================================
template <typename T>
struct BSTNode {
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;
};

template <typename T>
class BST {
    BSTNode<T>* root;
public:
    BST() : root(nullptr) {}
    BSTNode<T>* getRoot() { return root; }

    BSTNode<T>* insert(BSTNode<T>* node, T val) {
        if (node == nullptr) {
            BSTNode<T>* newNode = new BSTNode<T>;
            newNode->data = val;
            newNode->left = newNode->right = nullptr;
            return newNode;
        }
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node;
    }

    void insert(T val) { root = insert(root, val); }

    // Helper to get a pointer to the actual data inside the tree
    T* findDataPtr(BSTNode<T>* node, int id) {
        if (node == nullptr) return nullptr;
        if (node->data.id == id) return &(node->data);
        if (id < node->data.id) return findDataPtr(node->left, id);
        return findDataPtr(node->right, id);
    }

    void inorder(BSTNode<T>* r) {
        if (r) {
            inorder(r->left);
            cout << "ID: " << r->data.id << " | Title: " << r->data.title 
                 << " | Status: " << r->data.status << endl;
            inorder(r->right);
        }
    }
};

// ============================================================
// 5. DYNAMIC QUEUE ADT (Your Code)
// ============================================================
template <class T>
struct QueueNode {
    T d;
    QueueNode<T>* next;
    QueueNode(T data) : d(data), next(NULL) {}
};

template <class S>
class DQ {
    QueueNode<S> *front, *rear;
public:
    DQ() : front(NULL), rear(NULL) {}
    bool isEmpty() { return front == NULL; }
    void enqueue(S d) {
        QueueNode<S>* n = new QueueNode<S>(d);
        if (front == NULL) front = rear = n;
        else { rear->next = n; rear = n; }
    }
    void dequeue() {
        if (isEmpty()) return;
        QueueNode<S>* temp = front;
        front = front->next;
        delete temp;
        if (front == NULL) rear = NULL;
    }
    S getFront() { return (front) ? front->d : S(); }
};

// ============================================================
// 6. WORKFLOW MANAGEMENT SYSTEM (The Logic)
// ============================================================

// AdminAction uses an int 'type' instead of enum:
// 1 = SUBMISSION, 2 = REVISION_ADD, 3 = FINALIZATION
struct AdminAction {
    int type; 
    int docID;
    string oldStatus;
    AdminAction() : type(0), docID(0) {}
    AdminAction(int t, int id, string s = "") : type(t), docID(id), oldStatus(s) {}
};

class WorkflowManager {
    BST<Document> archive;             // O(log n) Search/Insert
    DQ<Document*> reviewWorkflow;      // O(1) FIFO Queue
    dynamicStack<AdminAction> adminLog; // System-wide Undo

public:
    // i. Submission - O(log n)
    void submitDocument(int id, string title, string author) {
        Document newDoc(id, title, author);
        archive.insert(newDoc);
        
        // ii. Placement in workflow - O(1)
        Document* ptr = archive.findDataPtr(archive.getRoot(), id);
        reviewWorkflow.enqueue(ptr);
        
        adminLog.push(AdminAction(1, id)); // 1 = Submission
        cout << "[System] Doc " << id << " submitted and queued.\n";
    }

    // ii. Process Workflow (FIFO) - O(1)
    void processReview() {
        if (reviewWorkflow.isEmpty()) return;
        Document* d = reviewWorkflow.getFront();
        reviewWorkflow.dequeue();
        d->status = "inreview";
        cout << "[Workflow] Doc " << d->id << " is now being reviewed (inreview).\n";
    }

    // iii. Adding a revision - O(1)
    void addRevision(int id, string content) {
        Document* d = archive.findDataPtr(archive.getRoot(), id);
        if (d && d->status == "inreview") {
            d->revisions.push(Revision(0, content)); 
            adminLog.push(AdminAction(2, id)); // 2 = Revision
            cout << "[Revision] Added to Doc " << id << ": " << content << endl;
        }
    }

    // iv. Undoing most recent revision - O(1)
    void undoDocRevision(int id) {
        Document* d = archive.findDataPtr(archive.getRoot(), id);
        if (d) {
            d->revisions.pop();
            cout << "[Revision] Last revision removed from Doc " << id << endl;
        }
    }

    // v. Final approval or rejection
    void finalize(int id, string newStatus) {
        Document* d = archive.findDataPtr(archive.getRoot(), id);
        if (d) {
            string old = d->status;
            d->status = newStatus;
            adminLog.push(AdminAction(3, id, old)); // 3 = Finalization
            cout << "[Finalize] Doc " << id << " marked as " << newStatus << endl;
        }
    }

    // vi. Display Archived (In-order) - O(n)
    void showArchive() {
        cout << "\n--- ARCHIVE (Sorted by ID) ---\n";
        archive.inorder(archive.getRoot());
    }

    // vii. System wide administrative undo
    void systemUndo() {
        if (adminLog.isEmpty()) return;
        AdminAction last = adminLog.getTop();
        adminLog.pop();

        Document* d = archive.findDataPtr(archive.getRoot(), last.docID);
        if (!d) return;

        if (last.type == 1) { // Undo Submission
            d->status = "Cancelled/Removed"; 
            cout << "[Undo] Submission of Doc " << last.docID << " reversed.\n";
        } else if (last.type == 2) { // Undo Revision
            d->revisions.pop();
            cout << "[Undo] Revision of Doc " << last.docID << " reversed.\n";
        } else if (last.type == 3) { // Undo Finalization
            d->status = last.oldStatus;
            cout << "[Undo] Finalization of Doc " << last.docID << " reversed.\n";
        }
    }
};

// ============================================================
// 7. MAIN EXECUTION
// ============================================================
int main() {
    WorkflowManager govSystem;

    // i. Submission (O(log n))
    govSystem.submitDocument(105, "Tax Reform", "Ali");
    govSystem.submitDocument(102, "Health Memo", "Sara");

    // ii. Workflow (FIFO - O(1))
    govSystem.processReview(); // Processes 105 first

    // iii. Revision (O(1))
    govSystem.addRevision(105, "Updated Clause 2");

    // v. Finalize
    govSystem.finalize(102, "approved");

    // vi. Archive (O(n))
    govSystem.showArchive();

    // vii. Admin Undo
    cout << "\n--- Performing Administrative Undo ---\n";
    govSystem.systemUndo(); // Reverses the approval of 102
    govSystem.showArchive();

    return 0;
}