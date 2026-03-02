#include <iostream>
#include <algorithm> // swap needa this
using namespace std;
const int s = 100;
class Heap {
    int arr[s];
    int avail;
public:
    Heap() : avail(0) {}
    bool isEmpty() {     //Returns true if the heap is empty
        return avail == 0; 
    }
    int getTop() {      //Returns the maximum , root
        if (isEmpty()) {
            cout << "Heap empty" << endl;
            return -1; 
        }
        return arr[0];
    }
    void insert(int d){
        if (isEmpty())
        {    arr[avail] = d; avail++;
        }
        else
        {   arr[avail] = d;
            int temp = avail++;
            int par;
        while (true)
        {   par = (temp - 1) / 2;
        if (temp>0&&arr[temp] > arr[par]){
            swap(arr[temp], arr[par]);
            temp = par;
        }   
        else
        {   break;
        }
        }  
        }
    }
    void deleteRoot() {     //Removes the top element and keepss Max Heap property
        if (isEmpty()) {
            cout << "Heap Underflow!" << endl;
            return;
        }
        arr[0] = arr[avail - 1]; // Move the last element to the root
        avail--;
        int i = 0;        // Heapify Down 
        while (true) {
            int leftChild = (2 * i) + 1;
            int rightChild = (2 * i) + 2;
            int largest = i;
            if (leftChild < avail && arr[leftChild] > arr[largest]) { // Check if left child is larger than current node
                largest = leftChild;
            }
            if (rightChild < avail && arr[rightChild] > arr[largest]) { // Check if right child is larger than current largest
                largest = rightChild;
            }
            if (largest != i) {    // If the largest is not the current node, swap and continue down
                swap(arr[i], arr[largest]);
                i = largest;
            } else {
                break; 
            }
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Heap is empty.";
        }
        for (int i = 0; i < avail; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Heap h;
    h.insert(15);
    h.insert(10);
    h.insert(25);
    h.insert(5);
    h.insert(30);
    cout << "Heap after insertion: ";
    h.display(); 
    cout << "Current Max: " << h.getTop() << endl;
    h.deleteRoot();
    cout << "Heap after deletion: ";
    h.display();
    cout << "New Max: " << h.getTop() << endl;
    return 0;
}