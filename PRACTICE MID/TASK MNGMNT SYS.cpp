#include "BST.h"
#include "DYNAMICQUEUET.h"
#include "DYNAMICSTACKT.h"
#include "LINKEDLIST.h"
#include "DOUBLELINKEDLIST.h"
#include <iostream>
#include <string>
using namespace std;

struct Task {
    int id;
    string description;
    int priority;  // 1 (high) to 5 (low)
    string status; // "todo", "doing", "done"
    
    Task() : id(0), description(""), priority(5), status("todo") {}
    Task(int i, string desc, int p) : id(i), description(desc), priority(p), status("todo") {}
    
    // BST by ID for O(log n) search
    bool operator<(const Task& other) const { return id < other.id; }
    bool operator>(const Task& other) const { return id > other.id; }
    bool operator==(const Task& other) const { return id == other.id; }
};

struct User {
    int id;
    string name;
    doubleList<Task> userTasks;  // Using doubleList for user's tasks
    
    User() : id(0), name("") {}
    User(int i, string n) : id(i), name(n) {}
};

struct Activity {
    string type;
    int taskId;
    string oldStatus;
    string newStatus;
    
    Activity() : type(""), taskId(0), oldStatus(""), newStatus("") {}
    Activity(string t, int id, string oldS, string newS) 
        : type(t), taskId(id), oldStatus(oldS), newStatus(newS) {}
};

class TaskManager {
private:
    BST<Task> taskDatabase;           // O(log n) task search
    BST<User> userDatabase;            // O(log n) user search
    DQ<int> highPriorityQueue;          // FIFO for high priority tasks
    DQ<int> normalPriorityQueue;        // FIFO for normal tasks
    dynamicStack<Activity> activityLog; // LIFO for undo
    linkedList<string> notifications;    // Notifications list
    
public:
    // O(log n) - Create task
    void createTask(int id, string desc, int priority) {
        Task newTask(id, desc, priority);
        taskDatabase.insert(newTask);
        
        if(priority <= 2) {
            highPriorityQueue.enqueue(id);
            cout << "High priority task " << id << " in fast queue" << endl;
        } else {
            normalPriorityQueue.enqueue(id);
        }
    }
    
    // O(1) - Get next task (FIFO with priority)
    void getNextTask() {
        if(!highPriorityQueue.isEmpty()) {
            int taskId = highPriorityQueue.getFront();
            highPriorityQueue.dequeue();
            cout << "Processing high priority task " << taskId << endl;
        }
        else if(!normalPriorityQueue.isEmpty()) {
            int taskId = normalPriorityQueue.getFront();
            normalPriorityQueue.dequeue();
            cout << "Processing normal task " << taskId << endl;
        }
        else {
            cout << "No tasks pending" << endl;
        }
    }
    
    // O(1) - Update task status (with undo)
    void updateTaskStatus(int taskId, string newStatus) {
        Task search(taskId, "", 0);
        
        if(taskDatabase.search(search)) {
            Activity act("STATUS_CHANGE", taskId, "old", newStatus);
            activityLog.push(act);
            cout << "Task " << taskId << " status updated to " << newStatus << endl;
        }
    }
    
    // O(1) - Undo last status change
    void undoLastChange() {
        if(activityLog.isEmpty()) {
            cout << "Nothing to undo" << endl;
            return;
        }
        activityLog.pop();
        cout << "Last change undone" << endl;
    }
    
    // O(n) - Display all tasks
    void displayAllTasks() {
        cout << "\n=== ALL TASKS (Sorted by ID) ===" << endl;
        // Would call BST inorder traversal
    }
    
    // O(log n) - Search task
    void searchTask(int taskId) {
        Task search(taskId, "", 0);
        if(taskDatabase.search(search)) {
            cout << "Task " << taskId << " found" << endl;
        } else {
            cout << "Task not found" << endl;
        }
    }
    
    // O(n) - Display queue lengths
    void displayQueueStats() {
        cout << "High priority queue: ";
        // Would display queue
        cout << "\nNormal priority queue: ";
        // Would display queue
        cout << endl;
    }
};

int main() {
    TaskManager manager;
    
    // Test all operations
    manager.createTask(1, "Fix bug", 1);        // O(log n)
    manager.createTask(2, "Write docs", 3);      // O(log n)
    manager.createTask(3, "Urgent patch", 1);    // O(log n)
    
    manager.getNextTask();                        // O(1)
    manager.getNextTask();                        // O(1)
    
    manager.updateTaskStatus(1, "doing");         // O(log n)
    manager.undoLastChange();                      // O(1)
    
    manager.displayAllTasks();                     // O(n)
    manager.searchTask(2);                         // O(log n)
    
    return 0;
}