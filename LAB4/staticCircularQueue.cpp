#include <iostream>
using namespace std;
const int SIZE = 5; 
class staticCircularQueue {
private:
    int arr[SIZE];    
    int front, rear;
    int currentSize;      
public:
    staticCircularQueue() : front(-1), rear(-1), currentSize(0) {
    }   
    bool isFull() {
        return currentSize == SIZE;
    }   
    bool isEmpty() {
        return currentSize == 0;
    }    
    void enqueue(int d) {
        if (isFull()) {  
            cout << "Queue is full! Cannot insert " << d << endl;
            return;
        }        
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;  
        }        
        arr[rear] = d;
        currentSize++;
        cout << "Inserted: " << d << endl;
    }    
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty! Cannot delete" << endl;
            return;
        }        
        cout << "Deleted: " << arr[front] << endl;        
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;  
        }        
        currentSize--;
    }    
    int getFront() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return arr[front];
    }    
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }        
        cout << "Queue: ";
        int i = front;
        int count = 0;
        while (count < currentSize) {
            cout << arr[i] << " ";
            i = (i + 1) % SIZE;
            count++;
        }
        cout << endl;
    }
};
int main() {
    staticCircularQueue q;    
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);
    q.display();    
    q.enqueue(60);  // Shows "Queue is full!"
    
    cout << "Front: " << q.getFront() << endl;
    q.dequeue();
    q.display();
    
    q.enqueue(60);  // Circular 
    q.display();
    
    return 0;
}