#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;
class Record {
public:
    int ID;
    string name;
    double value;
    Record(int id, string n, double v) : ID(id), name(n), value(v) {}  
    void display() const {
        cout << "ID:" << ID << " , " << name << " , " << value << endl;
    }   
    bool operator<(const Record& other) const {
        return value < other.value;
    }  
    bool operator==(const Record& other) const {
        return ID == other.ID;
    }
};
class RecordManager {
    list<Record> department1;
    list<Record> department2;
    list<Record> mergedList;   
    static bool compareByValue(const Record& a, const Record& b) {
        return a.value < b.value;
    }   
public:
    void addTodepartment1(int id, string name, double value) {
        department1.push_back(Record(id, name, value));
        department1.sort(compareByValue);
    }  
    void addTodepartment2(int id, string name, double value) {
        department2.push_back(Record(id, name, value));
        department2.sort(compareByValue);
    }   
    void mergeCollections() {
        mergedList = department1;
        mergedList.merge(department2);
        cout << "MergedList!\n";
    }  
    void displaymergedList() {
        if (mergedList.empty()) {
            cout << "No mergedList data\n";
            return;
        }
        cout << "\n   MergedList    \n";
        list<Record>::iterator temp;
        for (temp = mergedList.begin(); temp != mergedList.end(); temp++) {
            temp->display();
        }
    }  
    void verifySorted() {
        bool sorted = true;
        list<Record>::iterator temp = mergedList.begin();
        list<Record>::iterator next = mergedList.begin();
        next++;

        while (next != mergedList.end()) {
            if (temp->value > next->value) {
                 sorted = false;
                 break;
            }
        temp++;
        next++;}}
    void findDuplicates() {
        list<Record>::iterator temp;
        list<Record>::iterator check;
        bool found = false;   
        temp = mergedList.begin();
        while (temp != mergedList.end()) {
          check = temp;
          check++;
            while (check != mergedList.end()) {
              if (temp->ID == check->ID) {
                 cout << "Duplicate ID found: " << temp->ID << endl;
                 found = true;
            }
               check++;
        }
        temp++;
    }  
    if (!found) {
        cout << "No duplicate record IDs found\n";
    }}
};
int main() {
    RecordManager rec1;
    int choice;
    do {
        cout << "\n1.Add to Dep1 2.Add to Dep2 3.Merge 4.Display 5.Verify 6.Find Duplicates 7.Exit\n";
        cout << "Choice: ";
        cin >> choice;    
        if (choice == 1) {
            int id; string name; double val;
            cout << "ID: "; cin >> id;
            cout << "Name: "; cin.ignore(); getline(cin, name);
            cout << "Value: "; cin >> val;
            rec1.addTodepartment1(id, name, val);       }
        else if (choice == 2) {
            int id; string name; double val;
            cout << "ID: "; cin >> id;
            cout << "Name: "; cin.ignore(); getline(cin, name);
            cout << "Value: "; cin >> val;
            rec1.addTodepartment2(id, name, val);        }
        else if (choice == 3) {
            rec1.mergeCollections();       }
        else if (choice == 4) {
            rec1.displaymergedList();       }
        else if (choice == 5) {
            rec1.verifySorted();       }
        else if (choice == 6) {
            rec1.findDuplicates();        }
    } while (choice != 7);   
    return 0;
}