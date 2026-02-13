#ifndef DYNAMICSTACKT_H
#define DYNAMICSTACKT_H
#include <iostream>
using namespace std;
template <class T>
struct node {
    T data;
    node<T> * next;
    node(T d) : data(d), next(NULL) {}
};
template <class S>
class dynamicStack
{   node<S>* top;    
    public:
    dynamicStack() : top(NULL) {}  
    dynamicStack <S>(const dynamicStack<S>& obj) : top(NULL) {
        if (obj.top == NULL) {
            return;
        }
        node<S> *temp = obj.top;
        node<S> *temp2;
        node<S>* n= new node<S>(temp->data);
        temp2=n;
        top = n;
        temp = temp->next;  
        while(temp != NULL) {
            n = new node<S>(temp->data);
            temp2->next = n;
            temp2 = n;
            temp = temp->next;
        }   
    }
    bool isEmpty()
    {
        return (top == NULL);
    }    
    void push(S d)
    {
        node<S>* newNode = new node<S>(d);
        newNode->next = top;
        top = newNode;
        cout << "Inserted: " << d << endl;
    }    
    void pop()
    {
        if(isEmpty())
        {
            cout << "Stack is empty" << endl;
            return;
        }        
        node<S>* temp = top;
        top = top->next;
        cout << "Deleted: " << temp->data << endl;
        delete temp;
    }    
    S getTop()
    {
        if(isEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return top->data;
    }    
    void display()
    {
        if(isEmpty())
        {
            cout << "Stack is empty" << endl;
            return;
        }        
        cout << "Stack : ";
        node* temp = top;
        while(temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }    
    ~dynamicStack()
    {
        while(!isEmpty())
        {
            pop();
        }
    }
};
#endif
