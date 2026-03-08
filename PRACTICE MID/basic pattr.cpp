#include <iostream>
#include <string>
#include "BST.h"
#include "dynamicQueueT.h"
#include "DYNAMICSTACKT.h"
#include "doubleLinkedList.h"
#include "LINKEDLIST.h"

using namespace std;

//=============================================
// STEP 1: ENTITY - FIXED with proper copy operations
//=============================================
struct Entity {
    int id;
    string name;
    string status;
    
    // Constructors
    Entity() : id(0), name(""), status("pending") {}
    Entity(int i, string n) : id(i), name(n), status("pending") {}
    
    // COPY CONSTRUCTOR - IMPORTANT! This fixes the error
    Entity(const Entity& other) : id(other.id), name(other.name), status(other.status) {}
    
    // ASSIGNMENT OPERATOR - IMPORTANT! This fixes the error
    Entity& operator=(const Entity& other) {
        if(this != &other) {
            id = other.id;
            name = other.name;
            status = other.status;
        }
        return *this;
    }
    
    // For searching by ID
    explicit Entity(int idOnly) : id(idOnly), name(""), status("") {}
    
    // For BST comparison
    bool operator<(const Entity& other) const { return id < other.id; }
    bool operator>(const Entity& other) const { return id > other.id; }
    bool operator==(const Entity& other) const { return id == other.id; }
    
    void display() {
        cout << "ID: " << id << " | Name: " << name << " | Status: " << status << endl;
    }
};

//=============================================
// STEP 2: PROCESSOR - FIXED with proper copy operations
//=============================================
struct Processor {
    int id;
    string name;
    bool isAvailable;
    Entity currentTask;
    
    // Constructors
    Processor() : id(0), name(""), isAvailable(true), currentTask() {}
    Processor(int i, string n) : id(i), name(n), isAvailable(true), currentTask() {}
    
    // COPY CONSTRUCTOR - IMPORTANT!
    Processor(const Processor& other) : id(other.id), name(other.name), 
                                        isAvailable(other.isAvailable), 
                                        currentTask(other.currentTask) {}
    
    // ASSIGNMENT OPERATOR - IMPORTANT!
    Processor& operator=(const Processor& other) {
        if(this != &other) {
            id = other.id;
            name = other.name;
            isAvailable = other.isAvailable;
            currentTask = other.currentTask;
        }
        return *this;
    }
    
    void assign(Entity e) {
        currentTask = e;  // Now works with proper assignment operator
        isAvailable = false;
    }
    
    void complete() {
        isAvailable = true;
    }
    
    void display() {
        cout << "Processor " << id << ": " << name 
             << " | Available: " << (isAvailable ? "Yes" : "No");
        if(!isAvailable) {
            cout << " | Current Task: " << currentTask.name;
        }
        cout << endl;
    }
};

//=============================================
// STEP 3: ACTION for undo
//=============================================
struct Action {
    string type;
    int entityId;
    Entity snapshot;
    
    Action() : type(""), entityId(0), snapshot() {}
    Action(string t, int id, Entity e) : type(t), entityId(id), snapshot(e) {}
    
    // Copy constructor
    Action(const Action& other) : type(other.type), entityId(other.entityId), snapshot(other.snapshot) {}
    
    // Assignment operator
    Action& operator=(const Action& other) {
        if(this != &other) {
            type = other.type;
            entityId = other.entityId;
            snapshot = other.snapshot;
        }
        return *this;
    }
};

//=============================================
// STEP 4: MAIN SYSTEM CLASS - FIXED for doubleLinkedList
//=============================================
class System {
private:
    BST<Entity> database;
    DQ<Entity> waitingQueue;
    dynamicStack<Action> history;
    doubleList<Processor> processors;  // Using doubleLinkedList
    
    int nextId;
    
public:
    System() : nextId(1001) {
        // Initialize with 5 processors
        for(int i = 0; i < 5; i++) {
            Processor p(i+1, "Processor " + to_string(i+1));
            processors.insertAtEnd(p);
        }
        cout << "✅ System initialized with 5 processors" << endl;
    }
    
    // OPERATION 1: ADD ENTITY
    void addEntity(string name) {
        Entity newEntity(nextId++, name);
        
        database.insert(newEntity);
        waitingQueue.enqueue(newEntity);
        
        Action act("ADD", newEntity.id, newEntity);
        history.push(act);
        
        cout << "✅ Added: " << name << " (ID: " << newEntity.id << ")" << endl;
    }
    
    // OPERATION 2: PROCESS NEXT - FIXED for doubleLinkedList (NO getHead)
    void processNext() {
        if(waitingQueue.isEmpty()) {
            cout << "📭 Nothing to process" << endl;
            return;
        }
        
        // Get next in line
        Entity next = waitingQueue.getFront();
        waitingQueue.dequeue();
        
        // FIXED: doubleLinkedList doesn't have getHead()
        // We need to access head directly or modify doubleLinkedList
        // Since doubleLinkedList has private head, we need to add a getter
        // For now, let's assume we've added a getHead() function to doubleLinkedList.h
        
        // If you CAN modify doubleLinkedList.h, add this public function:
        /*
        dnode<S>* getHead() const {
            return head;
        }
        */
        
        // OPTION 1: Add getHead() to doubleLinkedList.h (RECOMMENDED)
        // OPTION 2: Make doubleLinkedList a friend class
        // OPTION 3: Add traversal functions to doubleLinkedList
        
        // For this solution, I'll show you what to add to doubleLinkedList.h
        
        // Once getHead() is added, use it:
        dnode<Processor>* temp = processors.getHead();  // Now works!
        
        while(temp != nullptr) {
            if(temp->d.isAvailable) {
                // Assign to processor
                temp->d.assign(next);
                
                cout << "🔄 Processing " << next.name << " (ID: " << next.id 
                     << ") with Processor " << temp->d.id << endl;
                
                Action act("PROCESS", next.id, next);
                history.push(act);
                
                return;
            }
            temp = temp->next;
        }
        
        // No available processor
        cout << "❌ No available processors. " << next.name << " back in queue." << endl;
        waitingQueue.enqueue(next);
    }
    
    // OPERATION 3: SEARCH BY ID
    void searchById(int id) {
        Entity searchEntity(id);
        if(database.search(searchEntity)) {
            cout << "🔍 Found entity with ID: " << id << endl;
        } else {
            cout << "🔍 Entity with ID " << id << " not found" << endl;
        }
    }
    
    // OPERATION 4: CANCEL BY ID
    void cancelById(int id) {
        if(waitingQueue.isEmpty()) {
            cout << "📭 Nothing to cancel" << endl;
            return;
        }
        
        DQ<Entity> tempQueue;
        bool found = false;
        
        while(!waitingQueue.isEmpty()) {
            Entity current = waitingQueue.getFront();
            waitingQueue.dequeue();
            
            if(current.id != id) {
                tempQueue.enqueue(current);
            } else {
                found = true;
                cout << "✅ Cancelled ID: " << id << endl;
                
                Action act("CANCEL", id, current);
                history.push(act);
            }
        }
        
        while(!tempQueue.isEmpty()) {
            waitingQueue.enqueue(tempQueue.getFront());
            tempQueue.dequeue();
        }
        
        if(!found) {
            cout << "❌ ID " << id << " not found in queue" << endl;
        }
    }
    
    // OPERATION 5: DISPLAY PENDING
    void displayPending() {
        if(waitingQueue.isEmpty()) {
            cout << "📭 No pending items" << endl;
            return;
        }
        
        cout << "\n=== PENDING ITEMS (FIFO Order) ===" << endl;
        
        DQ<Entity> tempQueue;
        int count = 0;
        
        while(!waitingQueue.isEmpty()) {
            Entity current = waitingQueue.getFront();
            waitingQueue.dequeue();
            
            current.display();
            count++;
            
            tempQueue.enqueue(current);
        }
        
        while(!tempQueue.isEmpty()) {
            waitingQueue.enqueue(tempQueue.getFront());
            tempQueue.dequeue();
        }
        
        cout << "Total: " << count << " pending" << endl;
        cout << "===================================\n";
    }
    
    // OPERATION 6: UNDO
    void undo() {
        if(history.isEmpty()) {
            cout << "📭 Nothing to undo" << endl;
            return;
        }
        
        Action last = history.getTop();
        history.pop();
        
        cout << "↩️ Undid: " << last.type << " on ID " << last.entityId << endl;
    }
    
    // OPERATION 7: DISPLAY PROCESSORS - FIXED for doubleLinkedList
    void displayProcessors() {
        cout << "\n=== PROCESSORS ===" << endl;
        
        // Need getHead() or a traversal function
        // For now, let's assume getHead() exists
        dnode<Processor>* temp = processors.getHead();
        
        if(temp == nullptr) {
            cout << "No processors" << endl;
        } else {
            while(temp != nullptr) {
                temp->d.display();
                temp = temp->next;
            }
        }
        cout << "==================\n";
    }
};

//=============================================
// MAIN FUNCTION
//=============================================
int main() {
    cout << "==========================================" << endl;
    cout << "   SYSTEM WITH FIXED COPY OPERATIONS     " << endl;
    cout << "==========================================" << endl;
    
    System system;
    
    system.addEntity("Task 1");
    system.addEntity("Task 2");
    system.addEntity("Task 3");
    
    system.displayPending();
    
    system.processNext();
    system.processNext();
    
    system.displayPending();
    system.displayProcessors();
    
    return 0;
}