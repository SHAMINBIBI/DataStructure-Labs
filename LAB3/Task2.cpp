//double Linked List
#include <iostream>
using namespace std;
struct pageNode
{
    string d;
    pageNode *next;
    pageNode *prev;
    pageNode():d("NULL"), next(NULL), prev(NULL){}
    pageNode(string data):d(data), next(NULL), prev(NULL) {}
};
class browserHistory
{
    pageNode *head,*tail;
    pageNode *current;  //pointer for current page
    public:
    browserHistory(): head(NULL),tail(NULL),current(NULL){}
    browserHistory(string url) : head(NULL), tail(NULL), current(NULL) 
    {
           visitPage(url);
    }
    bool isEmpty()  {return head == NULL;}
    browserHistory ( const browserHistory &obj)
    {
        head = tail = NULL;
        pageNode *n = obj.head;
        while(n!=NULL)
        {
            visitPage(n->d);
            n = n->next;
        }
    }
    void visitPage(string d)
    {   if(current != NULL)
        {   pageNode *temp = current->next;
            while (temp != NULL)
            {
                pageNode *nextNode=temp->next;
                delete temp;
                temp = nextNode;
            }
            current->next = NULL;
            tail= current;
        }
        // Create new page
    pageNode *n = new pageNode(d);
    if(isEmpty())
    {  
        head = tail = current = n;
    }
    else
    {
        tail->next = n;
        n->prev = tail;
        tail = n;
        current = n;  // New page becomes current
    }
    }
    string getCurrentPage() {
    if(current == NULL) {
        cout << "No current page!" << endl;
        return "NULL";
    }
    return current->d;
}
    int getLength()
    {   pageNode* temp = head;
        int count = 0;
        while(temp != NULL)
        {   count++ ;
            temp = temp-> next;
        }
        return count;
    }
    void deleteAtEnd()
{    if(isEmpty()) return;    
     if(head == tail)  // Only one node
    {
        delete head;
        head = tail = current = NULL;
    }
    else
    {
        pageNode *temp = tail;
        tail = tail->prev;
        tail->next = NULL;
        if(current == temp) current = tail;  // Update current if deleting current
        delete temp;
    }
}
    string back()  //browsser previos tab/page func
    {
        if(current==NULL || current->prev==NULL)
        {
            cout<<"CANNOT BACK NO PAGE AVAILABLE PREVIOUSLY!\n";
            return "NULL";
        }
        current = current->prev;
        return current->d;
    }
    string forward()  //for switching to next page 
    {
        if(current==NULL || current->next==NULL)
        {
            cout<<"CANNOT GO NEXT NO PAGE AVAILABLE NEXT!\n";
            return "NULL";
        }
        current = current->next;
        return current->d;
    }
    bool search(string d)
    {
       pageNode *temp = head;
       while (temp!= NULL)
       {
        if (temp->d == d)
         { cout << "FOUND! "<< temp->d <<endl;
           return true; 
         }
         temp= temp->next;
       }
       cout << d <<"NOT FOUND IN LIST\n";
       return false;
    }
    void displayHistory()  // display
    {   cout << "FORWARD: " ;
       pageNode*temp= head;
        while(temp!= NULL)
        {
            cout << temp->d << " , ";
            temp= temp->next;
        }
        cout <<endl;
        cout<< "REVERSE: ";
        temp = tail;   //reusing temp instead of decalring anotehr variable
        if(temp == NULL)
        {
            cout << "EMPTY! "<< endl;
        }
        while (temp != NULL)
        {
            cout << temp->d << " , ";
            temp= temp->prev;
        }
        cout <<endl;
    }
    ~browserHistory()   //destructor
    {
    pageNode * temp = head;
    while(temp != NULL) {
        pageNode* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = tail = current = NULL;} // Reset all pointers
};
int main()
{    browserHistory bh;
    bh.visitPage("google.com");
    bh.getCurrentPage();   
    bh.visitPage("github.com");
    bh.getCurrentPage() ;    
    bh.visitPage("stackoverflow.com");
    bh.getCurrentPage();   
    // Navigate back
    cout << "Going back to: " << bh.back() << endl;
    cout << "Current page: " << bh.getCurrentPage() << endl;   
    cout << "Going back again: " << bh.back() << endl;
    cout << "Current page: " << bh.getCurrentPage() << endl;    
    // Navigate forward
    cout << "Going forward to: " << bh.forward() << endl;
    cout << "Current page: " << bh.getCurrentPage() << endl;    
    // Try to go beyond limits
    cout << "Trying to go back from first page: " << bh.back() << endl;
    cout << "Trying to go forward from last page: " << bh.forward() << endl;
    cout << "Trying to go forward again: " << bh.forward() << endl;  
    // Display full history
    cout << "\nFull Browser History\n";
    bh.displayHistory();  
    // Copy constructor
    cout << "\nTesting Copy Constructor\n";
    browserHistory bh2(bh);
    cout << "Original history:\n";
    bh.displayHistory();
    cout << "Copied history:\n";
    bh2.displayHistory();
    
    return 0;
}