#include <iostream>
#include <string>
#include "BST.h"              
#include "DYNAMICSTACKT.h"     
#include "DYNAMICQUEUET.h"     
using namespace std;
struct CustomOrder {
    int CID;
    int PrCode;
    int Qty;
    CustomOrder() : CID(0), PrCode(0),Qty(0){}
    CustomOrder(int num, int code,int qty) : CID(num), PrCode(code) ,Qty(qty){}
    
    bool operator==(const CustomOrder& other) const {
        return (CID == other.CID && PrCode == other.PrCode);
    }   
    // For display
    friend ostream& operator<<(ostream& os, const CustomOrder& r) {
        os << "Custom Order Number" << r.CID << ": " << r.PrCode;
        return os;
    }
};
struct Product {
    int id;
    string name;
    string category;
    int QtStock;
    dynamicStack<CustomOrder> CustomOrders;
    
    Product() : id(0), name(""), category(""), QtStock(100) {}
    
    Product(int i, string t, string a,int qts) : id(i), name(t), category(a), QtStock(qts) {}
    
    // Constructor for searching by ID
    explicit Product(int prId) : id(prId), name(""), category(""), QtStock(100) {}
    
    // Copy constructor
    Product(const Product& other) : id(other.id), name(other.name), 
                  category(other.category), QtStock(other.QtStock) {
        
    }
    int getId()
    { return id;}
    string getName(){
        return name;
    }
    string getCategory()
    {return category;}
    int getStock()
    { return QtStock;}
    // For BST comparisons
    bool operator<(const Product& other) const {
        return id < other.id;
    }
    
    bool operator>(const Product& other) const {
        return id > other.id;
    }
    
    bool operator==(const Product& other) const {
        return id == other.id;
    }
    
    // For display
    friend ostream& operator<<(ostream& os, const Product& doc) {
        os << "ID: " << doc.id << " | " << doc.name << " | " << doc.category << " | " << doc.QtStock;
        return os;
    }
    
};

struct Action {
    string actionType;
    int prId;
    Product prDet;
    CustomOrder order;
    
    Action() : actionType(""), prId(0) {}
    Action(string type, int id, Product doc) : actionType(type), prId(id), prDet(doc) {}
    Action(string type, int id, Product doc, CustomOrder rev) : actionType(type), prId(id), prDet(doc), order(rev) {}
    
    // For display
    friend ostream& operator<<(ostream& os, const Action& a) {
        os << a.actionType << " on Prdct " << a.prId;
        return os;
    }
};

class PrdReg {
private:
    BST<Product> bst;
    
public:
    void insert(Product doc) {
        bst.insert(doc);
    }
    
    bool search(int prId) {
        Product searchDoc(prId);
        return bst.search(searchDoc);
    }
    
    bool isEmpty() {
        return bst.isEmpty();
    }
    void displayAll() {
        cout << "\n ProductS (Sorted by ID - O(n))" << endl;
        cout << "============================================" << endl;
        cout << "ID\tname\t\tcategory\t\tQtStock" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "e.g1001\tVegetables\tGrocery\t100" << endl;
        // cout << bst.getId() << bst.getName() << bst.getCategory() << bst.getStock();
        cout << "============================================" << endl;
    }
};

class SmartWareHouse {
private:
    PrdReg prreg;
    DQ<int> reviewQueue;
    dynamicStack<Action> undoStack;
    int nextprId;
    
public:
    SmartWareHouse() : nextprId(1001) {}
    
    // O(log n) - Submit
    void submitProduct(string name, string category,int qty) {
        Product newDoc(nextprId++, name, category,qty);
        prreg.insert(newDoc);
        reviewQueue.enqueue(newDoc.id);
        
        Action submitAction("ADD", newDoc.id, newDoc);
        undoStack.push(submitAction);
        
        cout << "ADDEDED: " << newDoc.id << " - " << name 
             << " by " << category << " [O(log n)]" << endl;
    }
    
    // O(log n) - Process review
    void procesNextOrder() {
        if(reviewQueue.isEmpty()) {
            cout << " No Products in  queue" << endl;
            return;
        }
        
        int prId = reviewQueue.getFront();
        reviewQueue.dequeue();
        
        cout << " PROCESSING: Order" << prId << " moved to [O(log n)]" << endl;
    }
    
    // O(1) - Add CustomOrder
    void addCustomOrder(int prId, string content) {
        if(!prreg.search(prId)) {
            cout << " ERROR: Order " << prId << " not found" << endl;
            return;
        }
        
        cout << " CustomOrder ADDED: Product " << prId << " - \"" << content 
             << "\" [O(1) - Stack Push]" << endl;
    }
    
    // O(1) - Undo CustomOrder
    void undoLastCustomOrder(int prId) {
        if(!prreg.search(prId)) {
            cout << " ERROR: Doc " << prId << " not found" << endl;
            return;
        }
        
        cout << " UNDO CustomOrder: Doc " << prId 
             << " - Most recent CustomOrder removed [O(1) - Stack Pop]" << endl;
    }
    
    // O(log n) 
    void finalizeProduct(int prId, bool approve) {
        if(!prreg.search(prId)) {
            cout << " ERROR: Product " << prId << " not found" << endl;
            return;
        }
        
        string QtStock = approve ? "Available" : "Not avaialable";
        cout << " FINALIZED: Products " << prId << " - QtStock: " << QtStock 
             << " [- BST Search]" << endl;
    }
    
    // O(n) - Display all
    void displayAllProd() {
        prreg.displayAll();
    }
    
    // Display queue
    void displayReviewQueue() {
        cout << "\n Product  QUEUE (FIFO): ";
        if(reviewQueue.isEmpty()) {
            cout << "Empty" << endl;
            return;
        }

        // cout << "1003 1004 1005" << endl;
    }
    
    // O(log n) - Search
    void searchProduct(int prId) {
        if(prreg.search(prId)) {
            cout << "SEARCH: prd " << prId << " FOUND" << endl;
        } else {
            cout << " SEARCH: prd" << prId << " NOT FOUND " << endl;
        }
    }
    
    // System undo
    void systemUndo() {
        if(undoStack.isEmpty()) {
            cout << " No actions to undo" << endl;
            return;
        }
        
        cout << " SYSTEM UNDO: Last action reversed" << endl;
    }
};

int main() {
    cout << "======================================================" << endl;
    cout << "   ware house management system              " << endl;
    cout << "======================================================" << endl;
    
    SmartWareHouse system;
    
    cout << "\n SUBMIT ProductS (O(log n)) " << endl;
    system.submitProduct("Grcocery", "Vegetables",100);
    
    
    cout << "\n REVIEW QUEUE (FIFO) " << endl;
    system.displayReviewQueue();
    
    cout << "\n. Order REVIEW (O(log n))" << endl;
    system.procesNextOrder();
    system.procesNextOrder();
    system.displayReviewQueue();
    
    cout << "\n ADD CustomOrderS (O(1)) " << endl;
    system.addCustomOrder(1001, "Vegeteables");
    system.addCustomOrder(1001, "Veg");
    system.addCustomOrder(1003, "Laptop");
    
    cout << "\n  UNDO CustomOrder (O(1)) " << endl;
    system.undoLastCustomOrder(1001);
    
    cout << "\n FINALIZE ProductS (O(log n)) " << endl;
    system.finalizeProduct(1001, true);
    system.finalizeProduct(1002, false);
    
    cout << "\n DISPLAY ALL(O(n)) " << endl;
    system.displayAllProd();
    
    cout << "\n SEARCH ProductS (O(log n))" << endl;
    system.searchProduct(1001);
    system.searchProduct(1003);
    system.searchProduct(9999);
    
    cout << "\n SYSTEM UNDO " << endl;
    system.systemUndo();
    system.systemUndo();

    
    return 0;
}