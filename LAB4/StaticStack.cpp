#include <iostream>
using namespace std;
const int SIZE = 6;
class staticStack
{
    int top =0;
    int items[SIZE];
    public:
    staticStack():top(0){}
    bool isEmpty()
    {        return (top == 0);}
    bool isFull()
    { return (top == SIZE);}
    void push(int d)
    {
        if(isFull())
        {cout << "Stack is full!" << d << endl;
        return;}
        items[top] = d;
        top++;
    }
    void pop()
    {
        if(isEmpty())
        {cout << "Stack is empty" << endl;
        return;}
        top--;
        cout << "Deleted: " << items[top] << endl;
    }
    int getTop()
    {
        if(isEmpty())
        {cout << "Stack is empty" << endl;
        return -1;}
        return items[top-1];
    }
     void display()
    {
        if(isEmpty())
        {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack : ";
        for(int i = top-1; i >= 0; i--)
        {
            cout << items[i] << " ";
        }
        cout << endl;
    }
};
int main()
{
    staticStack s;    
    s.push(10);
    s.push(20);
    s.push(30);
    s.display();  
    cout << "Top: " << s.getTop() << endl;   
    s.pop();
    s.display(); 
    s.push(40);
    s.push(50);
    s.push(60);
    s.push(70);  
    s.display();   
    return 0;
}