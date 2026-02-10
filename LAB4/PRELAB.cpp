#include <iostream>
using namespace std;
struct node {
	int d;
	node* next;
	node() : d(0), next(NULL) {}
    node(int data) : d(data), next(NULL) {}
};
class DQ 
{
    node *front , *rear;

    public:
    DQ() : front(NULL), rear(NULL) {}
    void enqueue(int d)
    {
        node *n = new node(d);
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
            node*temp = front;
            front = front->next;
            delete temp;
            temp = NULL;
        }
    }
    int getFront()
    {
        if(front != NULL)
        {  return front->d;}

        return 0;
    }
      bool isEmpty() {
        return front == NULL;
    }
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }        
        cout << "Queue elements : ";
        node* current = front;
        while (current != NULL) {
            cout << current->d << " ";
            current = current->next;
        }
        cout << endl;
    }
    bool search(int value) {
        node* current = front;
        while (current != NULL) {
            if (current->d == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};
int main() {
    DQ q;   
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();   
    q.dequeue();
    q.display();   
    q.enqueue(40);
    q.display();   
    cout << "Front: " << q.getFront() << endl;    
    cout << q.search(30);
    
    return 0;
}