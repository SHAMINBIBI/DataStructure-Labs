#include <iostream>
#include <string>

using namespace std;

// --- 1. Revision Structure (Linked List Stack Node) ---
struct Revision {
    int revNumber;
    string content;
    Revision* next;
    Revision(int num, string cont) : revNumber(num), content(cont), next(nullptr) {}
};

// --- 2. Document Structure (BST Node) ---
struct Document {
    int id;
    string title;
    string author;
    string status; // "Pending", "InReview", "Approved", "Rejected"
    
    Revision* revTop; // Internal Stack for Revisions
    Document *left, *right;

    Document(int _id, string _t, string _a) {
        id = _id; title = _t; author = _a;
        status = "Pending";
        revTop = nullptr;
        left = right = nullptr;
    }

    // O(1) Add Revision
    void addRevision(string content) {
        int nextRev = (revTop == nullptr) ? 1 : revTop->revNumber + 1;
        Revision* newRev = new Revision(nextRev, content);
        newRev->next = revTop;
        revTop = newRev;
    }

    // O(1) Undo Revision
    void undoRevision() {
        if (revTop == nullptr) return;
        Revision* temp = revTop;
        revTop = revTop->next;
        delete temp;
    }
};

// --- 3. Review Queue (Linked List based) ---
struct QueueNode {
    Document* doc;
    QueueNode* next;
    QueueNode(Document* d) : doc(d), next(nullptr) {}
};

class ReviewQueue {
    QueueNode *front, *rear;
public:
    ReviewQueue() : front(nullptr), rear(nullptr) {}

    // O(1) Insertion
    void enqueue(Document* d) {
        QueueNode* newNode = new QueueNode(d);
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    // O(1) Removal
    Document* dequeue() {
        if (front == nullptr) return nullptr;
        QueueNode* temp = front;
        Document* d = front->doc;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        return d;
    }
};

// --- 4. Main Workflow System ---
class WorkflowSystem {
    Document* root; // BST Root
    ReviewQueue reviewQueue;

public:
    WorkflowSystem() : root(nullptr) {}

    // i. Submission (BST Insert) - O(log n)
    Document* submitDocument(int id, string title, string author) {
        root = insertRecursive(root, id, title, author);
        Document* newDoc = searchDocument(id);
        reviewQueue.enqueue(newDoc); // ii. Placement in Workflow - O(1)
        return newDoc;
    }

    Document* insertRecursive(Document* node, int id, string t, string a) {
        if (node == nullptr) return new Document(id, t, a);
        if (id < node->id) node->left = insertRecursive(node->left, id, t, a);
        else if (id > node->id) node->right = insertRecursive(node->right, id, t, a);
        return node;
    }

    // Search - O(log n)
    Document* searchDocument(int id) {
        Document* curr = root;
        while (curr != nullptr) {
            if (id == curr->id) return curr;
            curr = (id < curr->id) ? curr->left : curr->right;
        }
        return nullptr;
    }

    // ii. Reviewal Process
    void processNextReview() {
        Document* d = reviewQueue.dequeue();
        if (d) {
            d->status = "InReview";
            cout << "Document " << d->id << " is now InReview." << endl;
        }
    }

    // v. Final Approval/Rejection
    void finalizeDocument(int id, bool approved) {
        Document* d = searchDocument(id);
        if (d) {
            d->status = approved ? "Approved" : "Rejected";
        }
    }

    // vi. Display Archived (In-order Traversal) - O(n)
    void displayArchived(Document* node) {
        if (node == nullptr) return;
        displayArchived(node->left);
        cout << "ID: " << node->id << " | Title: " << node->title 
             << " | Status: " << node->status << endl;
        displayArchived(node->right);
    }

    void showArchive() {
        cout << "\n--- Archived Documents (Sorted by ID) ---" << endl;
        displayArchived(root);
    }
};

int main() {
    WorkflowSystem govSystem;

    // 1. Submission
    govSystem.submitDocument(105, "Tax Reform", "John Doe");
    govSystem.submitDocument(101, "Health Policy", "Jane Smith");
    govSystem.submitDocument(110, "Education Act", "Bob Wilson");

    // 2. Review Workflow
    govSystem.processNextReview(); // Processes 105 (FIFO)

    // 3. Revisions
    Document* doc = govSystem.searchDocument(105);
    doc->addRevision("Updated Clause 1");
    doc->addRevision("Fixed Typo in Header");
    cout << "Added 2 revisions to Doc 105." << endl;

    // 4. Undo Revision
    doc->undoRevision();
    cout << "Undid most recent revision for Doc 105." << endl;

    // 5. Finalize
    govSystem.finalizeDocument(101, true);

    // 6. Archive Display
    govSystem.showArchive();

    return 0;
}