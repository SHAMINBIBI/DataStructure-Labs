#include <iostream>
using namespace std;
struct node {
    int data;
    node* next;
    node(int d) : data(d), next(NULL) {}
};
class dynamicStack
{   node* top;    
    public:
    dynamicStack() : top(NULL) {}    
    bool isEmpty()
    {
        return (top == NULL);
    }    
    void push(int d)
    {
        node* newNode = new node(d);
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
        node* temp = top;
        top = top->next;
        cout << "Deleted: " << temp->data << endl;
        delete temp;
    }    
    int getTop()
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
int main()
{
    dynamicStack s;
    
    s.push(100);
    s.push(20);
    s.push(30);
    s.display();    
    cout << "Top: " << s.getTop() << endl;   
    s.pop();
    s.display();   
    s.push(40);
    s.push(50);
    s.display();
    
    return 0;
}