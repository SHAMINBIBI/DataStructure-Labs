#include <iostream>
#include <list>
#include <algorithm>
#include <string>
using namespace std;
class Product {
public:
    int ID;
    string name;
    double price;
    string category; 
    Product(int id, string n, double p, string c) 
        : ID(id), name(n), price(p), category(c) {}   
    void display() const {
        cout << "ID:" << ID << " , " << name 
             << " , Rs." << price << " , " << category << endl;
    }
};
class RetailSystem {
    list<Product> products;    
    static bool compareByPrice(const Product& a, const Product& b) {
        return a.price < b.price;
    } 
    static Product applyPriceIncrease(Product p, double percent) {
        p.price *= (1 + percent / 100);
        return p;
    }   
public:
    void addProduct(int id, string name, double price, string category) {
        products.push_back(Product(id, name, price, category));
    }   
    void sortByPrice() {
        products.sort(compareByPrice);
        cout << "All Prods Sorteed\n";
    }   
    bool searchByID(int id) {
        list<Product>::iterator temp;
        for (temp = products.begin(); temp != products.end(); temp++) {
            if (temp->ID == id) {
                cout << "Found: ";
                temp->display();
                return true;
            }
        }
        cout << "Product " << id << " not found\n";
        return false;
    }   
    int countByCategory(string cat) {
        int count = 0;
        list<Product>::iterator temp;
        for (temp = products.begin(); temp != products.end(); temp++) {
            if (temp->category == cat) {
                count++;
            }
        }
        return count;
    }   
    void priceIncrease(double percent) {
        transform(products.begin(), products.end(), products.begin(),
                  [percent](Product p) { return applyPriceIncrease(p, percent); });
        cout << "Prices increased by " << percent << "%\n";
    }   
    void displayAll() {
        if (products.empty()) {
            cout << "No products\n";
            return;
        }
        for_each(products.begin(), products.end(),
                 [](const Product& p) { p.display(); });
    }
};
int main() {
    RetailSystem r1;
    int choice; 
    do {
        cout << "\n1.Add 2.Sort 3.Search 4.Count 5.Increase 6.Display 7.Exit\n";
        cout << "Choice: ";
        cin >> choice;      
        if (choice == 1) 
           { int id; string name, cat; double price;
            cout << "ID: "; cin >> id;
            cout << "Name: "; cin.ignore(); 
            getline(cin, name);
            cout << "Price: "; cin >> price;
            cout << "Category: "; cin.ignore();
            getline(cin, cat);
            r1.addProduct(id, name, price, cat);        }
        else if (choice == 2) 
         {   r1.sortByPrice();}
        else if (choice == 3) 
         {   int id; cout << "ID: "; cin >> id;
            r1.searchByID(id);        }
        else if (choice == 4)
          {  string cat; cout << "Category: "; 
            cin.ignore(); 
            getline(cin, cat);
            cout << "Count: " << r1.countByCategory(cat) << endl;     }
        else if (choice == 5) 
          {  double percent; 
            cout << "Increase Price by Percent: "; 
            cin >> percent;
            r1.priceIncrease(percent);       }
        else if (choice == 6) 
          {  r1.displayAll();        }
    } while (choice != 7);  
    return 0;
}