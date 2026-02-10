#include <iostream>
using namespace std;
struct node {
    int d;
    node* next;
    node() : d(0), next(NULL) {}
    node(int data) : d(data), next(NULL) {}
};
class linkedList
{
	node* head;

public:
	linkedList() : head(NULL)
	{}
	linkedList(const linkedList &obj)
	{   head=NULL;
        node* temp = obj.head;
		while(temp!=NULL)
		{
		  insertAtEnd(temp->d);
		  temp = temp->next;
		}

	}
	void deleteFromStart()
	{
		if (head != NULL)
		{
			node* temp = head;
			head = head->next;
			delete  temp;
		}
		else
		{
			cout << "LIST IS EMPTY!" << endl;
		}

	}
    void deleteFromAnyPos(int pos)
	{
		if(pos<1 || pos> getLength())
		{  cout<< "INVALID POSITION ENTERED-ONLY POSITIONS BETWEEN 1 AND " << getLength()<< " ARE ALLOWED\n";
		return;
	    }
		if(pos==1)
		{
			deleteFromStart();
		}
		else if (pos==getLength())
		{ deleteFromEnd();}
		else
		{
			node* temp= head;
			for(int i=1;i<pos-1;i++)
			{
				temp =temp->next;
			}
			node* toBeDeleted = temp->next;
			temp->next= toBeDeleted->next;
			delete toBeDeleted;
		}

	}
	void deleteFromEnd()
	{
		if (head == NULL)
		{
			cout << "LIST IS EMPTY!" << endl;
			return;
		}		
		if (head->next == NULL)
		{
			delete head;
			head = NULL;
			return;
		}		
		node* temp = head;
		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}		
		delete temp->next;
		temp->next = NULL;
	}
	void display()
	{
		node* temp = head;
		while (temp!=NULL)
		{
			cout << temp->d << " ";
			temp = temp->next;
		}
		cout << endl;
	}	
	void insertAtStart(int d)
	{
		node* n = new node;
		(*n).d = d;
		n->next = head;
		head = n;
		
	}
    void insertAtAnyPos(int d,int pos)
	{   if(pos ==1)
		{
			insertAtStart(d);
		}
		if (pos < 1 || pos > getLength() + 1)
    {
        cout << " INVALID POSITION!!! Position should be between 1 and " 
             << getLength() + 1 << endl;
        return;
    }
		else if(pos <= getLength() + 1  && pos > 0)
		{
		node* n =new node;
		n->d = d;
		node* temp= head;
		int count=1;
		while(count < pos-1)
		{
			temp= temp-> next;
			count ++;
		}
		n-> next = temp-> next;
		temp->next = n;
	    }   	
	}
	void insertAtEnd(int d)
	{
		node* n = new node;
		n->d = d;		
		if (head == NULL)
		{
			head = n;
			return;
		}		
		node* temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = n;
	}
	int getLength()
	{
		int count = 0;
		node* temp = head;
		
		while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}
		
		return count;
	}
	bool isEmpty()
	{
		return (head == NULL);
	}
	bool searchData(int d)
	{
		node* temp = head;
		
		while (temp != NULL)
		{
			if (temp->d == d)
			{
				return true;
			}
			temp = temp->next;
		}		
		return false;
	}
    int getFrontData() {
        if (head != NULL) {
            return head->d;
        }
        return -1;
    }
	~linkedList()
	{
		while(head!=NULL)
		{
			deleteFromStart();
		}
	}
};
// Queue using linkedList
class QueueUsingList {
private:
    linkedList list;      
public:
    void enqueue(int d) {   // enqueue = insert at end
        list.insertAtEnd(d);
    }
    void dequeue() {    // dequeue = delete from start
        list.deleteFromStart();
    }
    int getFront() {   // Get front = get first element
        return list.getFrontData();
    }
    bool isEmpty() {
        return list.isEmpty();
    }
    void display() {
        cout << "Queue: ";
        list.display();
    }
};
int main() {
    QueueUsingList q;  
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();   
    q.dequeue();
    q.display();  
    cout << "Front: " << q.getFront() << endl;  
    q.enqueue(40);
    q.display();   
    return 0;
}