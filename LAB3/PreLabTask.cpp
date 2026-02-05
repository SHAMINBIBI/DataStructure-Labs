//Double Linked List
#include <iostream>
using namespace std;
struct dnode
{
    int d;
    dnode *next;
    dnode *prev;
    dnode(): d(0),next(NULL), prev(NULL){}
    dnode(int data):d(data), next(NULL), prev(NULL) {}
};
class doubleList
{
    dnode*head,*tail;
    public:
    doubleList(): head(NULL),tail(NULL){}
    bool isEmpty()  {return head == NULL;}
    doubleList ( const doubleList &obj)
    {
        head = tail = NULL;
        dnode *n = obj.head;
        while(n!=NULL)
        {
            insertAtEnd(n->d);
            n = n->next;
        }
    }
    void insertAtStart(int d)
    {
        dnode *n = new dnode(d);
        if(isEmpty())
        {  head = tail = n;}
        else
        {   n->next = head;
            head->prev = n;
            head = n;
        }
    }
    void insertAtEnd(int d)
    {
        if(isEmpty())
        {  insertAtStart(d);}
        else
        {
            dnode *n = new dnode(d);
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }
    int getLength()
    {
        dnode* temp = tail;
        int count = 0;
        while(temp != NULL)
        {
            count++ ;
            temp = temp-> prev;
        }
        return count;
    }
    void insertAtAnyPosition(int d, int pos)
    {
        if(pos == 1)
        {
            insertAtStart(d);
        }
        else if( pos > getLength())
        {
            if (pos == getLength() + 1)
            {    insertAtEnd(d);}
            else
            {   return;}
        }
        else
        {
            dnode *temp= head;
            int count =1;
            while(count < pos -1)
            {
                temp = temp-> next;
                count ++;
            }
        dnode *n = new dnode(d);
        n->next= temp->next;
        temp->next=n;
        n->prev = temp;
        n->next->prev =  n;
        }
    }
    void deleteAtEnd()
    {
        if(!isEmpty())
        {   if (head == tail){
            deleteAtStart();}
            else{
                dnode *temp = tail;
                tail = tail->prev;
                tail->next = NULL;
                delete temp;
            }
        }

    }
    void deleteAtStart()
    {
         if(!isEmpty())
        {   if (head == tail)
            {
            delete head;
            head =tail = NULL;
            }
            else{
                dnode *temp = head;
                head = head->next;
                delete temp;
                if (head!=NULL){
                head->prev = NULL;
                }
            }
        }
    }
    void deleteAtAnyPosition(int pos)  //delete at any position
    {
        if(pos < 1 || pos > getLength())
        {   cout << "INVALID POSITION ENTERED!\n ";
            return;
        }
        if ( pos==1 )
        {   deleteAtStart();}
        else if (pos == getLength())
        {   deleteAtEnd();}
        else
        {  dnode*   temp = tail;
           for(int i= getLength();i>pos+1;i--)
           {  temp= temp->prev;}
           dnode *toBeDeleted = temp->prev;
           temp->prev = toBeDeleted->prev;
           toBeDeleted->prev->next = temp;
           delete toBeDeleted;
        }
    }
    bool search(int d)
    {
       dnode *temp = tail;
       while (temp!= NULL)
       {
        if (temp->d == d)
         { cout << " FOUND! "<< temp->d <<endl;
           return true; 
         }
         temp= temp->prev;
       }
       cout << d <<" NOT FOUND IN LIST\n";
       return false;
    }
    void displayFwd()  //fprward display
    {
        dnode *temp= head;
        while(temp!= NULL)
        {
            cout << temp->d << " , ";
            temp= temp->next;
        }
        cout << endl;
    }
    void displayRev()
    {
        dnode *temp = tail;
        while (temp != NULL)
        {
            cout << temp->d << " , ";
            temp= temp->prev;
        }
        cout <<endl;
    }
    ~doubleList()   //destructor
    {
        while(!isEmpty())
        {
            deleteAtStart();
        }
    }
};
int main()
{
	doubleList l;
	l.insertAtStart(20);
	l.insertAtStart(30);
	l.insertAtStart(40);
	l.insertAtStart(50);
	l.insertAtStart(60);
	l.insertAtStart(70);
	l.insertAtEnd(100);
	l.insertAtEnd(10);
	l.deleteAtEnd();
	l.deleteAtStart();
    // l.displayFwd();
	l.displayRev();
    // l.deleteAtAnyPosition(3);
    // l.displayFwd();
	// l.search(505);
    // doubleList l2(l);
    // l.displayFwd();
    // l2.displayFwd();
    // l.deleteAtStart();
    // l.displayFwd();
    // l2.displayFwd();

   return 0;
}