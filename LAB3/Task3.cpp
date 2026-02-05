#include <iostream>
using namespace std;
struct stationNode
{   string stationName;
    stationNode *next;
    stationNode *prev;
    stationNode(): stationName("NULL"), next(NULL), prev(NULL){}
    stationNode(string name): stationName(name), next(NULL), prev(NULL) {}
};
class MetroRoute
{   stationNode *head, *tail;
    stationNode *current;    
public:
    MetroRoute(): head(NULL), tail(NULL), current(NULL){}    
    MetroRoute(string firstStation) : head(NULL), tail(NULL), current(NULL) 
    {        addStation(firstStation, 1);
    }   
    // Copy constructor
    MetroRoute (const MetroRoute &obj)
    {   head = tail = current = NULL;
        stationNode *n = obj.head;
        while(n != NULL)
        {   addStation(n->stationName, getLength() + 1);
            n = n->next;
        }
        // Set current to same position as original 
        setCurrentToPosition(obj.getCurrentPosition());
    }    
    bool isEmpty()  { return head == NULL; }  
    void addStation(string stationName, int position)
    {   if(position < 1) 
        {   cout << "Position must be >= 1!" << endl;
            return;
        }        
        if(position == 1)
        {
            stationNode *n = new stationNode(stationName);
            if(isEmpty())
            {
                head = tail = current = n;
            }
            else
            {
                n->next = head;
                head->prev = n;
                head = n;
            }
            return;
        }        
        int length = getLength();
        if(position > length + 1)
        {
            cout << "Invalid position! Max position is " << length + 1 << endl;
            return;
        }        
        if(position == length + 1)
        {
            stationNode *n = new stationNode(stationName);
            if(isEmpty())
            {
                head = tail = current = n;
            }
            else
            {
                tail->next = n;
                n->prev = tail;
                tail = n;
            }
            return;
        }        
        stationNode *temp = head;
        for(int i = 1; i < position - 1; i++)
        {
            temp = temp->next;
        }        
        stationNode *n = new stationNode(stationName);
        n->next = temp->next;
        n->prev = temp;
        temp->next->prev = n;
        temp->next = n;
    }    
    bool removeStation(string stationName)
    {   if(isEmpty())
        {
            cout << "Route is empty!" << endl;
            return false;
        }        
        stationNode *temp = head;
        while(temp != NULL)
        {   if(temp->stationName == stationName)
            {   if(current == temp)
                {
                    if(temp->next != NULL)
                        current = temp->next;
                    else if(temp->prev != NULL)
                        current = temp->prev;
                    else
                        current = NULL;
                }                
                if(temp->prev != NULL)
                    temp->prev->next = temp->next;
                else
                    head = temp->next;
                
                if(temp->next != NULL)
                    temp->next->prev = temp->prev;
                else
                    tail = temp->prev;                
                delete temp;
                cout << "Station '" << stationName << "' removed successfully." << endl;
                return true;
            }
            temp = temp->next;
        }       
        cout << "Station '" << stationName << "' not found!" << endl;
        return false;
    }    
    string moveForward()
    {
        if(current == NULL || current->next == NULL)
        {
            cout << "Cannot move forward - end of route!" << endl;
            return "NULL";
        }
        current = current->next;
        return current->stationName;
    }    
    string moveBackward()
    {
        if(current == NULL || current->prev == NULL)
        {
            cout << "Cannot move backward - start of route!" << endl;
            return "NULL";
        }
        current = current->prev;
        return current->stationName;
    }    
    void displayRoute()
    {
        cout << "Complete Metro Route:\n";
        cout << "FORWARD: ";
        stationNode *temp = head;
        if(temp == NULL) {
            cout << "Route is empty";
        }
        while(temp != NULL)
        {
            cout << temp->stationName;
            if(temp->next != NULL) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;        
        cout << "REVERSE: ";
        temp = tail;
        if(temp == NULL) {
            cout << "Route is empty";
        }
        while(temp != NULL)
        {
            cout << temp->stationName;
            if(temp->prev != NULL) cout << " -> ";
            temp = temp->prev;
        }
        cout << endl;
    }    
    string currentStation() const
    {
        if(current == NULL) {
            cout << "No current station!" << endl;
            return "NULL";
        }
        return current->stationName;
    }    
    int getLength() const
    {
        stationNode *temp = head;
        int count = 0;
        while(temp != NULL)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }   
    int getCurrentPosition() const  // ADDED 'const' HERE
    {
        if(current == NULL) return 0;        
        stationNode *temp = head;
        int pos = 1;
        while(temp != NULL && temp != current)
        {
            pos++;
            temp = temp->next;
        }
        return pos;
    }    
    void setCurrentToPosition(int pos)
    {
        if(pos < 1 || pos > getLength())
        {
            cout << "Invalid position!" << endl;
            return;
        }        
        stationNode *temp = head;
        for(int i = 1; i < pos; i++)
        {
            temp = temp->next;
        }
        current = temp;
    }    
    ~MetroRoute()
    {
        stationNode *temp = head;
        while(temp != NULL) {
            stationNode *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = current = NULL;
    }
};
int main()
{   MetroRoute route;    
    route.addStation("Secrtrait", 1);
    route.addStation("Faiz Ahmed Faiz", 2);
    route.addStation("Chandni Chowk", 3);
    route.addStation("Kameti Chowk", 4);    
    cout << "Current station: " << route.currentStation() << endl;
    route.displayRoute();    
    cout << "Moving forward: " << route.moveForward() << endl;
    cout << "Current station: " << route.currentStation() << endl;     
    cout << "Moving backward: " << route.moveBackward() << endl;
    cout << "Current station: " << route.currentStation() << endl;
    cout << "\nAdding Station in Middle\n";
    route.addStation("RehmanAbad", 3);
    route.displayRoute();
    cout << "Current station: " << route.currentStation() << endl;   
    cout << "\nRemoving Station\n";
    route.removeStation("Chandni Chowk");
    route.displayRoute();   
    cout << "\nTesting Copy Constructor\n";
    MetroRoute route2(route);
    cout << "Original route:\n";
    route.displayRoute();
    cout << "Copied route:\n";
    route2.displayRoute();    
    return 0;
}