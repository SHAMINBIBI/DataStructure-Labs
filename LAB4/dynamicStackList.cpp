#include <iostream>
using namespace std;
struct node {
    int d;
    node* next;
};
class linkedList {
    node* head;
public:
    linkedList() : head(NULL) {}   
    void insertAtStart(int d)
    {
        node* n = new node;
        n->d = d;
        n->next = head;
        head = n;
    }   
    void deleteFromStart()
    {
        if (head != NULL)
        {
            node* temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            cout << "LIST IS EMPTY!" << endl;
        }
    }   
    bool isEmpty()
    {
        return head == NULL;
    }   
    int getHeadData()
    {
        if (head != NULL)
        {
            return head->d;
        }
        return -1;
    }    
    void display()
    {
        node* temp = head;
        while (temp != NULL)
        {
            cout << temp->d << " ";
            temp = temp->next;
        }
        cout << endl;
    }    
    ~linkedList()
    {
        while(!isEmpty())
        {
            deleteFromStart();
        }
    }
};
// Dynamic Stack using  linkedList
class StackUsingList {
    linkedList list;   
public:
    bool isEmpty()
    {
        return list.isEmpty();
    }    
    void push(int d)
    {
        list.insertAtStart(d);
        cout << "Inserted: " << d << endl;
    }   
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty " << endl;
            return;
        }
        cout << "Deleted: " << list.getHeadData() << endl;
        list.deleteFromStart();
    }   
    int getTop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return list.getHeadData();
    }   
    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack : ";
        list.display();
    }
};
int main()
{
    StackUsingList s;
    
    s.push(10);
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