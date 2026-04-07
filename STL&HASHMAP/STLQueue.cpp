#include <iostream>
#include <deque>
#include <algorithm>
#include <string>
using namespace std;
class ticket
{   private:
        int ID;
        string Name;
        string IssueType;
        int priorityLevel;       
    public:
        ticket() : ID(0), Name("None"), IssueType("NIL"), priorityLevel(0) {}         
        ticket(int id, string n, string type, int pr) : ID(id), Name(n), IssueType(type), priorityLevel(pr) {}     
        int getID() const { return ID; }
        string getName() const { return Name; }
        string getIssueType() const { return IssueType; }
        int getPriorityLevel() const { return priorityLevel; }           
        void display() const {
            cout << "Ticket ID: " << ID << ", Name: " << Name 
                 << ", Issue: " << IssueType << ", Priority: " 
                 << (priorityLevel == 2 ? "Urgent" : "Normal") << endl;
        }       
};
class myQueue
{   private:
        deque<ticket> tickets;                 
    public:
        myQueue() {}             
        void enqueue(ticket t) {  
            if (t.getPriorityLevel() == 2) {
                tickets.push_front(t);  // Urgent tickets at start
                cout << "Urgent ticket added!" << endl;
            } else {
                tickets.push_back(t);   // Normal tickets at end
                cout << "Normal ticket added!" << endl; 
            }      }           
        ticket dequeue() {   
            if (tickets.empty()) {
                cout << "No tickets to remove" << endl;
                return ticket(); 
            }
            ticket nextTicket = tickets.front();
            tickets.pop_front();
            return nextTicket;
        }               
        void display() const {   //displaying all pending tickets
            if (tickets.empty()) {
                cout << "No pending tickets!" << endl;
                return;            
            }            
            cout << "\n   Pending Tickets  " << endl;
            deque<ticket>::const_iterator temp;
            int index = 1;
            for (temp = tickets.begin(); temp != tickets.end(); ++temp) {
                cout << index++ << ". ";
                temp->display();
            }        }             
        void showCurrentTicket() const { // current ticket being processed 
            if (tickets.empty()) {
                cout << "No ticket currently being processed." << endl;
                return;
            }            
            cout << "Currently processing: ";
            tickets.front().display();       }           
        int countIssueType(const string& issueType) const { //tickets based on issuing type
            int count = 0;
            deque<ticket>::const_iterator temp;
            for (temp = tickets.begin(); temp != tickets.end(); ++temp) {
                if (temp->getIssueType() == issueType) {
                    count++;
                }
            }
            return count;       }              
        bool searchByID(int ticketID)  {     // Search for ticket by ID
            deque<ticket>::const_iterator temp;
            for (temp = tickets.begin(); temp != tickets.end(); ++temp) {
                if (temp->getID() == ticketID) {
                    cout << "Ticket found: ";
                    temp->display();
                    return true;
                }            }
            cout << "Ticket with ID " << ticketID << " not found." << endl;
            return false;
        }        
        bool isEmpty()  {
            return tickets.empty();
        }       
        int size() {
            return tickets.size();
        }
};
int main() {
    myQueue Q;
    int choice;       
    do {
        cout << "\n   Customer Support Center " << endl;
        cout << "1. Add New Ticket" << endl;
        cout << "2. Process Next Ticket" << endl;
        cout << "3. Display All Pending Tickets" << endl;
        cout << "4. Show Current Ticket Being Processed" << endl;
        cout << "5. Count Tickets by Issue Type" << endl;
        cout << "6. Search Ticket by ID" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;          
        switch(choice) {
            case 1: {
                int id, priority;
                string name, issueType;                
                cout << "Enter Ticket ID: ";
                cin >> id;
                cout << "Enter Customer Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Issue Type: ";
                getline(cin, issueType);
                cout << "Enter Priority Level (1=Normal, 2=Urgent): ";
                cin >> priority;               
                ticket newTicket(id, name, issueType, priority);
                Q.enqueue(newTicket);
                break;                      }                   
            case 2: 
             {   ticket processed = Q.dequeue();
                if (processed.getID() != 0) {
                    cout << "Processing ticket: ";
                    processed.display();
                }
                break;                      }                
            case 3: 
            {   Q.display();
                break;         }                        
            case 4: 
            {   Q.showCurrentTicket();
                break; 
            }                     
            case 5: 
            {    string issueType;
                cout << "Enter Issue Type to count: ";
                cin.ignore();
                getline(cin, issueType);
                int count = Q.countIssueType(issueType);
                cout << "Number of tickets with issue type '" << issueType 
                     << "': " << count << endl;
                break;                      }                      
            case 6: 
            {   int id;
                cout << "Enter Ticket ID to search: ";
                cin >> id;
                Q.searchByID(id);
                break;                       }                     
            case 7:
            {   cout << "Exiting system." << endl;
                break;  }                            
            default:
                cout << "Invalid choice Please try again." << endl;        }       
    } while(choice != 7);     
    return 0;
}