#include <iostream>
using namespace std;
struct node {
    int d;
    node *next;
    node() : d(0), next(nullptr) {}
    node(int x) :d(x), next(nullptr) {}
    node(int x, node *next) :d(x), next(next) {}
};
class linkedList   //linked list class that was made in LAB 2
{	node* head;
public:
	linkedList() : head(NULL)	{}
	linkedList(const linkedList &obj)
	{   head=NULL;
        node* temp = obj.head;
		while(temp!=NULL)
		{
		  insertAtEnd(temp->d);
		  temp = temp->next;
		}
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
	void insertAtEnd(int d)
	{	node* n = new node;
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
	{	int count = 0;
		node* temp = head;	
		while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}	
		return count;
	}
	node* getHead() { return head; }
    void setHead(node* newHead) { head = newHead; }
	bool isEmpty()
	{
		return (head == NULL);
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
	~linkedList()
	{
		while(head!=NULL)
		{
			deleteFromStart();
		}
	}
};
class LinkedListRev{
    public:
    node* reverseKGroup(node* head,int k)
	{
		node* temp =head;
		//checking if k nodes exist in linked list
		int count = 1;
		while(count<=k)
		{	if(temp==NULL)
			{ return head;}
			temp=temp->next;
			count++;
		}
		//recursive call for the rest of list i.e after k group
		node* prevNode = reverseKGroup(temp,k);
		//reverse current group
		temp = head;
		count = 1;
		while (count<=k)
		{   node* next = temp->next;
			temp->next = prevNode;
			prevNode = temp;
			temp = next;
			count++;
		}
		return prevNode;
	}
};
int main()
{   linkedList list1;  
    for (int i = 1; i <= 5; i++) list1.insertAtEnd(i); 
    cout << "Original List: ";
    list1.display();
    LinkedListRev revTool;
    int k = 2;   //for k=2
    node* newHead1 = revTool.reverseKGroup(list1.getHead(), k);  // Get the head, reverse it, and set the new head back
    list1.setHead(newHead1);
    cout << "After " << k << "-group reversal: ";
    list1.display();
    linkedList list2;
    for (int i = 1; i <= 5; i++) list2.insertAtEnd(i);
    cout << "Original List: ";
    list2.display();
    int k1 = 3;
    node* newHead2 = revTool.reverseKGroup(list2.getHead(), k1);  //for k=3
    list2.setHead(newHead2);
    cout << "After " << k1 << "-group reversal: ";
    list2.display();
    return 0;	
}