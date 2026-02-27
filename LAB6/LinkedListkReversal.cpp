#include <iostream>
using namespace std;
struct node {
    int val;
    node *next;
    node() : val(0), next(nullptr) {}
    node(int x) : val(x), next(nullptr) {}
    node(int x, node *next) : val(x), next(next) {}
};
class linkedList
{
	node* head;

public:
	linkedList() : head(NULL)	{}
	linkedList(const linkedList &obj)
	{   head=NULL;
        node* temp = obj.head;
		while(temp!=NULL)
		{
		  insertAtEnd(temp->val);
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
			cout << temp->val << " ";
			temp = temp->next;
		}
		cout << endl;
	}	
	void insertAtStart(int d)
	{
		node* n = new node;
		(*n).val = d;
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
		n->val = d;
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
		n->val = d;		
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
			if (temp->val == d)
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
class reversalByK {
public:
    node* reverseKGroup(node* head, int k) {
        // 1. Check if there are at least k nodes left in the list
        node* curr = head;
        for (int i = 0; i < k; i++) {
            if (!curr) return head; // If less than k nodes, leave them as is
            curr = curr->next;
        }

        // 2. Reverse the first k nodes
        node* prevNode = nullptr;
        node* currNode = head;
        node* nextNode = nullptr;

        for (int i = 0; i < k; i++) {
            nextNode = currNode->next; // Save next node
            currNode->next = prevNode; // Reverse pointer
            prevNode = currNode;       // Move prev forward
            currNode = nextNode;       // Move curr forward
        }

        // 3. After reversal, 'head' is now the tail of this group.
        // Connect it to the result of the next recursive call.
        if (nextNode != nullptr) {
            head->next = reverseKGroup(nextNode, k);
        }

        // 4. 'prevNode' is the new head of this reversed group
        return prevNode;
    }
};