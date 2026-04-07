#include <iostream>
#include <list>
#include <string>
using namespace std;
class HashNode {
public:
    int key;
    string value;   
    HashNode(int k, string v) : key(k), value(v) {}
};
class HashTable {
private:
    int tableSize;
    list<HashNode>* table;    
    int hashFunction(int key) {
        return key % tableSize;
    }    
public:
    HashTable(int size) {
        tableSize = size;
        table = new list<HashNode>[tableSize];
    }    
    ~HashTable() {
        delete[] table;
    }       
    void insert(int key, string value) {
        int index = hashFunction(key);     
        
        list<HashNode>::iterator temp;
        for (temp = table[index].begin(); temp != table[index].end(); temp++) {
            if (temp->key == key) {
                temp->value = value;  
                return;
            }
        }      
        table[index].push_back(HashNode(key, value));
    }      
    string search(int key) {
        int index = hashFunction(key);       
        list<HashNode>::iterator temp;
        for (temp = table[index].begin(); temp != table[index].end(); temp++) {
            if (temp->key == key) {
                return temp->value;
            }
        }      
        return "";
    }  
    void display() {
        cout << "\n   Hash Table   \n";
        for (int i = 0; i < tableSize; i++) {
            cout << "Index " << i << ": ";
            if (table[i].empty()) {
                cout << "Empty\n";
            } else {
                list<HashNode>::iterator temp;
                for (temp = table[i].begin(); temp != table[i].end(); temp++) {
                    cout << "(" << temp->key << ", " << temp->value << ") ";
                }
                cout << endl;
            }
        }
    }
};
int main() {
    HashTable h(10);
    int choice;
    cout<< "\nWelcome to SHAM'S Website Login System\n";
    do {
        cout << "\n1. Register\n2. Login\n3. Display\n4. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        if (choice == 1) {
            int id;
            string pass;
            cout << "Enter User ID: ";
            cin >> id;
            cout << "Enter Password: ";
            cin >> pass;
            h.insert(id, pass);
            cout << "User registered successfully!\n";
        }
        else if (choice == 2) {
            int id;
            string pass;
            cout << "Enter User ID: ";
            cin >> id;
            cout << "Enter Password: ";
            cin >> pass;         
            string stored = h.search(id);           
            if (stored == "") {
                cout << "Authentication failure\n";           }
            else if (stored == pass) {
                cout << "Authentication successful\n";       }
            else {
                cout << "Authentication failure\n";        }
        }
        else if (choice == 3) {
            h.display();
        }       
    } while (choice != 4);   
    return 0;
}