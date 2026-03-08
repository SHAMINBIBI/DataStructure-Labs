#ifndef DYNAMICQUEUET_H
#define DYNAMICQUEUET_H
#include <iostream>
using namespace std;

template <class T>
struct queue_node {  // Changed from 'node' to 'queue_node'
    T d;
    queue_node<T>* next;
    queue_node() : d(T()), next(NULL) {}
    queue_node(T data) : d(data), next(NULL) {}
};

template <class S>
class DQ 
{
    queue_node<S> *front , *rear;

public:
    DQ() : front(NULL), rear(NULL) {}
    
    DQ(const DQ<S>& obj) : front(NULL), rear(NULL) {
        if (obj.front == NULL) {
            return;
        }
        queue_node<S> *temp = obj.front;
        while (temp != NULL) {
            enqueue(temp->d);
            temp = temp->next;
        }
    }
    
    void enqueue(S d) {
        queue_node<S> *n = new queue_node<S>(d);
        if(front == NULL) {
            front = rear = n;
        } else { 
            rear->next = n;
            rear = n;
        }
    }
    
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty! Cannot delete" << endl;
            return;
        }
        
        queue_node<S>* temp = front;
        front = front->next;
        delete temp;
        
        if (front == NULL) {
            rear = NULL;
        }
    }
    
    S getFront() {
        if(front != NULL) {
            return front->d;
        }
        return S();
    }
    
    bool isEmpty() {
        return front == NULL;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        
        cout << "Queue : ";
        queue_node<S>* current = front;
        while (current != NULL) {
            cout << current->d << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    bool search(S value) {
        queue_node<S>* current = front;
        while (current != NULL) {
            if (current->d == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    ~DQ() {
        while(!isEmpty()) {
            dequeue();
        }
    }
};
#endif