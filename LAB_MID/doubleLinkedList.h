#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include <iostream>
using namespace std;
template <class T>
struct dnode
{
    T d;
    dnode<T> *next;
    dnode<T> *prev;
    dnode(): next(NULL), prev(NULL){}
    dnode(T data):d(data), next(NULL), prev(NULL) {}
};
template <class S>
class doubleList
{
    dnode <S>*head,*tail;
    public:
    doubleList(): head(NULL),tail(NULL){}
    
    dnode<S>* getHead() const {
        return head;
    }
    bool isEmpty()  {return head == NULL;}
    doubleList ( const doubleList &obj)
    {
        head = tail = NULL;
        dnode<S> *n = obj.head;
        while(n!=NULL)
        {
            insertAtEnd(n->d);
            n = n->next;
        }
    }
    void insertAtStart(S d)
    {
        dnode<S> *n = new dnode<S>(d);
        if(isEmpty())
        {  head = tail = n;}
        else
        {   n->next = head;
            head->prev = n;
            head = n;
        }
    }
    void insertAtEnd(S d)
    {
        if(isEmpty())
        {  insertAtStart(d);}
        else
        {
            dnode<S> *n = new dnode<S>(d);
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }
    int getLength()
    {
        dnode<S>* temp = head;
        int count = 0;
        while(temp != NULL)
        {
            count++ ;
            temp = temp-> next;
        }
        return count;
    }
    void insertAtAnyPosition(S d, int pos)
    {   if(pos < 1) 
        {
            cout << "POSITION MUST BE >= 1" << endl;
            return;
        }
        if(pos == 1)
        {
            insertAtStart(d);
        }
        else if( pos > getLength())
        {
            if (pos == getLength() + 1)
            {    insertAtEnd(d);}
            else
            {   cout << "INVALID POSITION ENTERED!"<< endl;
                return;}
        }
        else
        {
            dnode<S> *temp= head;
            int count =1;
            while(count < pos -1)
            {
                temp = temp-> next;
                count ++;
            }
        dnode<S> *n = new dnode<S>(d);
        n->next= temp->next;
        temp->next=n;
        n->prev = temp;
        n->next->prev =  n;
        }
    }
    void deleteAtEnd()
    {
        if(!isEmpty())
        {   if (head == tail)
            {
            deleteAtStart();}
        
            else{
                dnode<S> *temp = tail;
                tail = tail->prev;
                tail->next = NULL;
                delete temp;
            }
        }
        else
        {  cout << "CANNOT DELETE FROM EMPTY LIST!\n";
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
            else
           {
            dnode<S> *temp = head;
            head = head->next;
            delete temp;
            if (head!=NULL){
            head->prev = NULL;
            }
           }
        }
        else
        {  cout << "CANNOT DELETE FROM EMPTY LIST!\n";
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
        {  dnode<S> *temp = tail;
           for(int i= getLength();i>pos+1;i--)
           {  temp= temp->prev;}
           dnode<S> *toBeDeleted = temp->prev;
           temp->prev = toBeDeleted->prev;
           toBeDeleted->prev->next = temp;
           delete toBeDeleted;
        }
    }
    bool search(S d)
    {
       dnode<S> *temp = head;
       while (temp!= NULL)
       {
        if (temp->d == d)
         { cout << " FOUND! "<< temp->d <<endl;
           return true; 
         }
         temp= temp->next;
       }
       cout << d <<" NOT FOUND IN LIST\n";
       return false;
    }
    void Traverse()  // display
    {   cout << "FORWARD: " ;
        dnode<S> *temp= head;
        while(temp!= NULL)
        {
            cout << temp->d << " , ";
            temp= temp->next;
        }
        cout <<endl;
        cout<< "REVERSE: ";
        temp = tail;   //reeeusing temp instead of decalring anotehr variable
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
    ~doubleList()   //destructor
    {
        while(!isEmpty())
        {
            deleteAtStart();
        }
    }
};
#endif
