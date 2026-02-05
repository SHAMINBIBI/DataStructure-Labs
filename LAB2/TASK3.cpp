//task 3 LAB 2
#include<iostream>
#include <string>
using namespace std;
struct record
{	int id;
	string name;
	string severity;
	record* next;
    record():id(0),name("XXX"),severity("None"),next(NULL){}
	record (int i, string n,string sev,record* nxt =NULL): id(i),name(n),severity(sev),next(nxt){}
};
class linkedList
{   record* reg_patient;
public:
	linkedList() : reg_patient(NULL){}
	linkedList(const linkedList &obj)
	{   reg_patient=NULL;
       record* temp = obj.reg_patient;
		while(temp!=NULL)
		{
		  insertAtEnd(temp->id ,temp->name,temp->severity);
		  temp = temp->next;
		}
	}
	void deleteFromStart()
	{	if (reg_patient != NULL)
		{   record* temp = reg_patient;
			reg_patient = reg_patient->next;
			delete  temp;
		}
		else
		{
			cout << "RECORD IS EMPTY!" << endl;
		}
	}
    void deleteFromAnyPos(int pos)
	{
		if(pos<1 || pos> getLength())
		{  cout<< "INVALID POSITION ENTERED.ONLY IDs BETWEEN 1 & " << getLength()<< " ARE ALLOWED\n";
		return;
	    }
		if(pos==1)
		{ deleteFromStart();
		}
		else if (pos==getLength())
		{ deleteFromEnd();}
		else
		{   record* temp= reg_patient;
			for(int i=1;i<pos-1;i++)
			{
				temp =temp->next;
			}
		   record* toBeDeleted = temp->next;
			temp->next= toBeDeleted->next;
			delete toBeDeleted;
		}
	}
	void deleteFromEnd()
	{
		if (reg_patient == NULL)
		{
			cout << "LIST IS EMPTY!" << endl;
			return;
		}		
		if (reg_patient->next == NULL)
		{
			delete reg_patient;
			reg_patient = NULL;
			return;
		}		
	   record* temp = reg_patient;
		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}		
		delete temp->next;
		temp->next = NULL;
	}
	void display()
	{
	   record* temp = reg_patient;
	   cout << "MEENU'S CARE PATIENT RECORD "<<endl;
	   if(temp==NULL)
	   {
		cout << "RECORD LIST EMPTY! "<<endl;
		return;
	   }
	   int count=1;
		while (temp!=NULL)
		{
			cout << count << "-ID " << temp->id << "- NAME " << temp->name <<"-SEVERITY "<<temp->severity << endl;
			temp = temp->next;
			count++;
		}
		cout << endl;
	}	
	void insertAtStart(int id,string name,string cond)
	{
	   record* n = new record(id,name,cond,reg_patient);
		reg_patient = n;
		cout << "PATIENT " << name << " (ID: " << id << ") ADDED AT START!" << endl; 		
	}
    void insertSeriousPatient(int id,string name)
	{   	
	   record* n =new record(id,name,"Serious");
		if (reg_patient == NULL || reg_patient->severity == "Stable")
		{   n->next= reg_patient;
			reg_patient = n;
			cout << "PATIENT " << name << " (ID: " << id << ") ADDED AS SERIOUS PATIENT!" << endl;
			return;		}
		record *temp=reg_patient;
		while(temp->next != NULL && temp->next->severity == "Critical")
		{   
			temp= temp-> next;			
		}
		n-> next = temp-> next;
		temp->next = n;
	    cout << "PATIENT " << name << " (ID: " << id << ") ADDED AS SERIOUS PATIENT!" << endl;		
	}
	void insertAtEnd(int id,string name,string cond)
	{
	   record* n = new record(id,name,cond);
		if (reg_patient == NULL)
		{
			reg_patient = n;
		}
		else
		{
	   record* temp = reg_patient;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = n;
	    }
		cout << "PATIENT " << name << " (ID: " << id << ") ADDED AT END!" << endl;  
	}
	int getLength()
	{
		int count = 0;
	   record* temp = reg_patient;		
	   while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}		
		return count;
	}
	bool isEmpty()
	{
		return (reg_patient == NULL);
	}
	bool searchAndDisplay(int id)
	{
	   record* temp = reg_patient;	
		while (temp != NULL)
		{
			if (temp->id == id)
			{
				cout << "PATIENT FOUND!\n";
				cout << "ID: " << temp->id << endl;
				cout << "NAME: " << temp->name << endl;
				cout << "CONDITION: " << temp->severity << endl;
				return true;
			}
			temp = temp->next;
		}
		cout << "PATIENT ID " << id << " NOT FOUND!" << endl; 
		return false;
	}
	void removeID(int ID)
	{   
		if(reg_patient== NULL)
		{
          cout << "EMPTY LIST.NO PATIENT TO BE REMOVED!\n";
		  return;
		}
		if(reg_patient->id == ID)
		{  record* temp = reg_patient;
		   reg_patient =reg_patient->next;
		   cout << "PATIENT ID " << ID << " REMOVED FROM REC\n";
			delete temp;
			return;
		}
		//serch
		record *temp= reg_patient;
		while(temp->next != NULL && temp->next->id != ID)
		{
                temp= temp->next;
		}
		if(temp->next==NULL)
		{
			cout << "INNPUT ID" << ID << " NOT FOUND\n";
			return;
		}
		// Remove patient
		record* toDelete = temp->next;
		temp->next = toDelete->next;
		cout << "PATIENT ID " << ID << " REMOVED!" << endl;
		delete toDelete;
	}
	void nextPatient()  //for treating next patent
	{
        if(reg_patient==NULL)
		{  cout<< " RECORD EMPTY-NO PATIENTS TO TREAT\n";
			return;
		}
		cout << " TREATING PATIENT: " << reg_patient-> name << endl;
		cout << " ID: " << reg_patient->id <<endl;
		cout << " CONDITION: " << reg_patient->severity<< endl;
		deleteFromStart();
	}
	void dischargePatient()   //disracarge patient when treated
	{
		if(reg_patient == NULL)
		{
			cout << "LIST EMPTY!NO PATIENTS TO DISCHARGE!" << endl;
			return;
		}
		if(reg_patient->next == NULL)
		{
			cout << "DISCHARGING PATIENT: " << reg_patient->name 
			     << "\nID: " << reg_patient->id << endl;
			delete reg_patient;
			reg_patient = NULL;
			return;
		}
		record *temp= reg_patient;
		while(temp->next->next!= NULL)
		{
			temp= temp->next;
		}
		cout << "DISCHARGING LAST PATIENT: " << temp->next->name 
		     << "\nID: " << temp->next->id << endl;
		delete temp->next;
		temp->next = NULL;
	}
	~linkedList()
	{
		while(reg_patient!=NULL)
		{
			deleteFromStart();
		}
	}
};
class EmergencyRecord
{   private:
	linkedList patientRecord;
	public:
	EmergencyRecord(int  id=0,string name =" ",string condition = " ")
	{	if(id != 0)  // If initial patient provided
		{
			addPatient(id, name, condition);
		}
	}
	EmergencyRecord(const EmergencyRecord &obj) : patientRecord(obj.patientRecord) {}
	void addPatient(int id,string name,string condition)
	{	if(condition == "Critical")
		{   patientRecord.insertAtStart(id, name,condition);}
		else if(condition == "Serious")
		{   patientRecord.insertSeriousPatient(id,name);}
		else{ patientRecord.insertAtEnd(id,name,condition);}
	} 
	void displayPatients()
	{
		patientRecord.display();
	}	
	void treatNext()
	{
		patientRecord.nextPatient();
	}	
	void removePatient(int id)
	{
		patientRecord.removeID(id);
	}	
	void searchPatient(int id)
	{
		patientRecord.searchAndDisplay(id);
	}	
	void dischargeLast()
	{
		patientRecord.dischargePatient();
	}
	linkedList createBackup()
	{	cout << "COPYING THE RECORD " << endl;
		return linkedList(patientRecord);  // Using copy constructor
	}
};
int main()
{  cout << "MEENU'S CARE HOSPITAL\n" << endl;	
	EmergencyRecord er1;
	er1.displayPatients();  // 1.Start system with no patients	
	EmergencyRecord er2(101, "Alia", "Critical"); // 2: Start system with one transferred patient
	er2.displayPatients(); 
	er2.addPatient(102, "Saba", "Critical");  // 3: Add critical patient
	er2.displayPatients(); 
	er2.addPatient(103, "Ahmed", "Stable");   // 4: Add stable patient
	er2.displayPatients(); 
	er2.addPatient(104, "Ayesha", "Serious");  // 5: Add serious patient
	er2.displayPatients(); 
	er2.addPatient(105, "Ali", "Critical");  // 6: Add another critical patient
	er2.displayPatients();  
	er2.addPatient(106, "Sara", "Stable");   // 7: Add another stable patient
	er2.displayPatients(); 	
	er2.treatNext();        // 8: Treat next patient
	er2.displayPatients();  
	er2.removePatient(104); // 9: Remove patient by ID 104
	er2.displayPatients();
	er2.removePatient(106);  // 10: Remove last patient
	er2.displayPatients();
	er2.removePatient(999); // 11: Attempt to remove non-existent patient
	er2.displayPatients();
	er2.searchPatient(102);  // 12: Search existing patient
	er2.searchPatient(888); // 13: Search non-existing patient	
	linkedList backup = er2.createBackup();  // 14: Create backup at shift end
	er2.removePatient(103);
	er2.displayPatients();
    backup.display();
	er2.addPatient(201,"Shamin","Stable");
	er2.displayPatients();
    backup.display();
	er2.dischargeLast(); // 15: Discharge last remaining patient
	er2.displayPatients();
	cout << "\nDisplaying empty list" << endl;
	er2.displayPatients();  // 16: Display empty list
	return 0;
}