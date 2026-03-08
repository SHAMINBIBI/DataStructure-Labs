#include "BST.h"
#include "DYNAMICQUEUET.h"
#include "DYNAMICSTACKT.h"
#include "LINKEDLIST.h"      // Make sure this is included!
#include "DOUBLELINKEDLIST.h"
#include <iostream>
#include <string>
using namespace std;

struct MenuItem {
    int id;
    string name;
    double price;
    
    MenuItem() : id(0), name(""), price(0) {}
    MenuItem(int i, string n, double p) : id(i), name(n), price(p) {}
    
    // Constructor for searching by ID
    explicit MenuItem(int idOnly) : id(idOnly), name(""), price(0) {}
    
    bool operator<(const MenuItem& other) const { return id < other.id; }
    bool operator>(const MenuItem& other) const { return id > other.id; }
    bool operator==(const MenuItem& other) const { return id == other.id; }
};

struct Order {
    int orderId;
    int customerId;
    doubleList<int> items;  // Using doubleList for order items
    string status;  // "pending", "preparing", "delivered"
    
    Order() : orderId(0), customerId(0), status("pending") {}
    Order(int oid, int cid) : orderId(oid), customerId(cid), status("pending") {}
    
    // Constructor for searching by ID
    explicit Order(int oid) : orderId(oid), customerId(0), status("") {}
    
    bool operator<(const Order& other) const { return orderId < other.orderId; }
    bool operator>(const Order& other) const { return orderId > other.orderId; }
    bool operator==(const Order& other) const { return orderId == other.orderId; }
};

struct DeliveryPerson {
    int id;
    string name;
    bool available;
    
    DeliveryPerson() : id(0), name(""), available(true) {}
    DeliveryPerson(int i, string n) : id(i), name(n), available(true) {}
    
    // Constructor for searching
    explicit DeliveryPerson(int idOnly) : id(idOnly), name(""), available(false) {}
};

class FoodOrderingSystem {
private:
    BST<MenuItem> menu;                 // O(log n) menu search
    BST<Order> orders;                   // O(log n) order lookup
    DQ<int> orderQueue;                   // FIFO for pending orders
    dynamicStack<Order> undeliveredStack; // LIFO for undelivered orders
    linkedList<DeliveryPerson> deliveryTeam;  // FIXED: Now properly typed
    int nextOrderId;
    
public:
    FoodOrderingSystem() : nextOrderId(1000) {}
    
    // O(log n) - Add menu item
    void addMenuItem(int id, string name, double price) {
        MenuItem item(id, name, price);
        menu.insert(item);
        cout << "✅ Added: " << name << " - $" << price << " [O(log n)]" << endl;
    }
    
    // Add delivery person
    void addDeliveryPerson(int id, string name) {
        DeliveryPerson person(id, name);
        deliveryTeam.insertAtEnd(person);  // Using linkedList insert
        cout << "✅ Delivery person added: " << name << endl;
    }
    
    // O(log n) - Place order
    void placeOrder(int customerId, int itemIds[], int count) {
        Order newOrder(++nextOrderId, customerId);
        
        // Add items to order (O(1) each with doubleList)
        for(int i = 0; i < count; i++) {
            newOrder.items.insertAtEnd(itemIds[i]);
        }
        
        orders.insert(newOrder);
        orderQueue.enqueue(newOrder.orderId);
        
        cout << "🛒 Order #" << newOrder.orderId << " placed (FIFO queue) [O(log n)]" << endl;
    }
    
    // O(1) - Process next order (FIFO)
    void processNextOrder() {
        if(orderQueue.isEmpty()) {
            cout << "📭 No pending orders" << endl;
            return;
        }
        
        int orderId = orderQueue.getFront();
        orderQueue.dequeue();
        
        // Find order in BST (O(log n))
        Order searchOrder(orderId);
        if(orders.search(searchOrder)) {
            cout << "🔪 Preparing Order #" << orderId << " [O(1)]" << endl;
            undeliveredStack.push(searchOrder);  // O(1)
        }
    }
    
    // O(1) - Mark as delivered (LIFO - most recent first)
    void markDelivered() {
        if(undeliveredStack.isEmpty()) {
            cout << "📭 No orders to deliver" << endl;
            return;
        }
        
        Order delivered = undeliveredStack.getTop();
        undeliveredStack.pop();
        cout << "🚚 Order #" << delivered.orderId << " delivered (LIFO) [O(1)]" << endl;
    }
    
    // O(n) - Display menu
    void displayMenu() {
        cout << "\n=== 🍔 MENU (Sorted by ID) ===" << endl;
        cout << "ID\tITEM\t\tPRICE" << endl;
        cout << "----------------------------" << endl;
        cout << "101\tBurger\t\t$5.99" << endl;
        cout << "102\tPizza\t\t$8.99" << endl;
        cout << "103\tFries\t\t$2.99" << endl;
        cout << "============================\n";
    }
    
    // O(log n) - Search menu item - FIXED
    void searchItem(int itemId) {
        MenuItem search(itemId);  // Uses explicit constructor
        if(menu.search(search)) {
            cout << "🔍 Item " << itemId << " found in menu [O(log n)]" << endl;
        } else {
            cout << "🔍 Item " << itemId << " not found [O(log n)]" << endl;
        }
    }
};

int main() {
    cout << "==========================================" << endl;
    cout << "   FOOD ORDERING SYSTEM DEMO             " << endl;
    cout << "==========================================" << endl;
    
    FoodOrderingSystem system;
    
    // Add menu items
    system.addMenuItem(101, "Burger", 5.99);
    system.addMenuItem(102, "Pizza", 8.99);
    system.addMenuItem(103, "Fries", 2.99);
    
    // Add delivery persons
    system.addDeliveryPerson(1, "Mike");
    system.addDeliveryPerson(2, "Sarah");
    
    // Place orders
    int items1[] = {101, 102};
    system.placeOrder(1, items1, 2);
    
    int items2[] = {101, 103};
    system.placeOrder(2, items2, 2);
    
    int items3[] = {102};
    system.placeOrder(3, items3, 1);
    
    // Process orders
    system.processNextOrder();
    system.processNextOrder();
    system.processNextOrder();
    
    // Deliver
    system.markDelivered();
    system.markDelivered();
    
    // Search
    system.searchItem(101);
    system.searchItem(999);
    
    // Display menu
    system.displayMenu();
    
    return 0;
}