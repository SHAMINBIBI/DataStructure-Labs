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
    // Insert 
    void insert(int key, string value) {
        int index = hashFunction(key);     
        // Check if key already exists
        list<HashNode>::iterator temp;
        for (temp = table[index].begin(); temp != table[index].end(); temp++) {
            if (temp->key == key) {
                temp->value = value;  
                cout << "Updated key " << key << "\n";
                return;
            }
        }
        // Insert new node
        table[index].push_back(HashNode(key, value));
        cout << "Insertion done(" << key << ", " << value << ") at index " << index << "\n";
    }   
    bool remove(int key) {   // Delete key
        int index = hashFunction(key);    
        list<HashNode>::iterator temp;
        for (temp = table[index].begin(); temp != table[index].end(); temp++) {
            if (temp->key == key) {
                table[index].erase(temp);
                cout << "Deleted " << key << "\n";
                return true;
            }
        }      
        cout << "Key " << key << " not found\n";
        return false;
    }  
    string search(int key) {   // Search for key
        int index = hashFunction(key);       
        list<HashNode>::iterator temp;
        for (temp = table[index].begin(); temp != table[index].end(); temp++) {
            if (temp->key == key) {
                cout<< "FOUND " <<endl;
                return temp->value;
            }
        }      
        return "NOT FOUND";
    }
    // Display entire hash table
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
    HashTable h(10);  //Hash Table of size 10
    int choice;   
    do {
        cout << "\n 1.Insert\n 2.Delete\n 3.Search\n 4.Display\n 5.Exit\n";
        cout << "Choice: ";
        cin >> choice;  
        if (choice == 1) {
            int key; string value;
            cout << "Enter key: "; cin >> key;
            cout << "Enter value: "; cin >> value;
            h.insert(key, value);       }
        else if (choice == 2) {
            int key;
            cout << "Enter key to delete: "; cin >> key;
            h.remove(key);       }
        else if (choice == 3) {
            int key;
            cout << "Enter key to search: "; cin >> key;
            string result = h.search(key);
            cout << "Value: " << result << "\n";       }
        else if (choice == 4) {
            h.display();     }
    } while (choice != 5); 
    return 0;
}