#ifndef DYNAMICQUEUET_H
#define DYNAMICQUEUET_H
#include <iostream>
using namespace std;
template <class T>
struct node {
	T d;
	node<T>* next;
	node() : d(T()), next(NULL) {}
    node(T data) : d(data), next(NULL) {}
};
template <class S>
class DQ 
{
    node<S> *front , *rear;

    public:
    DQ() : front(NULL), rear(NULL) {}
    DQ <S> (const DQ<S>& obj) : front(NULL), rear(NULL) {
        if (obj.front == NULL) {
            return;
        }
        node<S> *temp = obj.front;
        while (temp!=NULL)
        {
            enqueue(temp->d);
            temp = temp->next;
        }
    }
    void enqueue(S d)
    {
        node<S> *n = new node<S>(d);
        if(front == NULL)
        { front = rear = n;}
        else 
        { rear->next =n;
        rear=n;}
    }
    void dequeue()
    {   if (isEmpty()) {
            cout << "Queue is empty! Cannot delete" << endl;
            return;
        }
        if (front!= NULL)
        {
            node<S>*temp = front;
            front = front->next;
            delete temp;
            temp = NULL;
        }
    }
    S getFront()
    {
        if(front != NULL)
        {  return front->d;}

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
        node<S>* current = front;
        while (current != NULL) {
            cout << current->d << " ";
            current = current->next;
        }
        cout << endl;
    }
    bool search(S value) {
        node<S>* current = front;
        while (current != NULL) {
            if (current->d == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};
#endif