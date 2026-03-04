#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<iostream>
using namespace std;
template <class T>
struct node {
	T d;
	node<T>* next;
	node() : next(NULL) {}
};
template <class S>
class linkedList
{
	node<S>* head;
public:
	linkedList() : head(NULL)
	{}
	linkedList(const linkedList<S> &obj)
	{   head = NULL;
        node<S>* temp = obj.head;
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
			node<S>* temp = head;
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
			node<S>* temp= head;
			for(int i=1;i<pos-1;i++)
			{
				temp =temp->next;
			}
			node<S>* toBeDeleted = temp->next;
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
		node<S>* temp = head;
		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}		
		delete temp->next;
		temp->next = NULL;
	}
	void display()
	{
		node<S>* temp = head;
		while (temp!=NULL)
		{
			cout << temp->d << " ";
			temp = temp->next;
		}
		cout << endl;
	}	
	void insertAtStart(S d)
	{
		node<S>* n = new node<S>();
		(*n).d = d;
		n->next = head;
		head = n;		
	}
    void insertAtAnyPos(S d,int pos)
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
		node<S>* n =new node<S>();
		n->d = d;
		node<S>* temp= head;
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
	void insertAtEnd(S d)
	{
		node<S>*  n = new node<S>();
		n->d = d;	
		if (head == NULL)
		{
			head = n;
			return;
		}		
		node<S>* temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = n;
	}
	int getLength()
	{
		int count = 0;
		node<S>* temp = head;		
		while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}	
		return count;
	}
	bool isEmpty()
	{
		if(head == NULL){ return true;}
		else
		{ return false;}
	}
	bool searchData(S d)
	{
		node<S>* temp = head;		
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
	~linkedList()
	{
		while(head!=NULL)
		{
			deleteFromStart();
		}
	}
};
#endif
