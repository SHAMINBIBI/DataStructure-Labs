#ifndef DYNAMICSTACKT_H
#define DYNAMICSTACKT_H
#include <iostream>
using namespace std;

template <class T>
struct stack_node {  // Changed from 'node' to 'stack_node'
    T data;
    stack_node<T> * next;
    stack_node(T d) : data(d), next(NULL) {}
};

template <class S>
class dynamicStack
{   
    stack_node<S>* top;
    
public:
    dynamicStack() : top(NULL) {}
    
    dynamicStack(const dynamicStack<S>& obj) : top(NULL) {
        if (obj.top == NULL) {
            return;
        }
        
        // Create a temporary stack to reverse order
        dynamicStack<S> tempStack;
        stack_node<S>* temp = obj.top;
        
        // Push all to temp (reverses)
        while(temp != NULL) {
            tempStack.push(temp->data);
            temp = temp->next;
        }
        
        // Pop from temp and push to this (reverses back)
        while(!tempStack.isEmpty()) {
            push(tempStack.getTop());
            tempStack.pop();
        }
    }
    
    bool isEmpty() {
        return (top == NULL);
    }
    
    void push(S d) {
        stack_node<S>* newNode = new stack_node<S>(d);
        newNode->next = top;
        top = newNode;
    }
    
    void pop() {
        if(isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        
        stack_node<S>* temp = top;
        top = top->next;
        delete temp;
    }
    
    S getTop() {
        if(isEmpty()) {
            cout << "Stack is empty" << endl;
            return S();
        }
        return top->data;
    }
    
    void display() {
        if(isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        
        // Need to display in reverse for correct order
        dynamicStack<S> tempStack;
        stack_node<S>* temp = top;
        
        while(temp != NULL) {
            tempStack.push(temp->data);
            temp = temp->next;
        }
        
        cout << "Stack : ";
        while(!tempStack.isEmpty()) {
            cout << tempStack.getTop() << " ";
            tempStack.pop();
        }
        cout << endl;
    }
    
    ~dynamicStack() {
        while(!isEmpty()) {
            pop();
        }
    }
};
#endif