#include "dynamicQueueT.h"
#include<iostream>
using namespace std;
class Computingsystem
{
    private:
    DQ <Computingsystem> task;
    DQ <Computingsystem> AllTasks;
    string id;
    float workUnit;
    public:
    Computingsystem() : id(""), workUnit(0) {}
    Computingsystem(string i, float w) : id(i), workUnit(w) {}    
    void addWork(string i , float units)
    {
       task.enqueue(Computingsystem(i,units));   
    }
    void processing()
    {
        if(task.isEmpty())
        {
            cout << "No procesisng Task available" << endl;
            return;
        }
        while(!task.isEmpty()){
        Computingsystem CW = task.getFront();  //CW = current work
        float remainingUnits = CW.workUnit;    // Use the task's work units       
        while(remainingUnits > 0) {
            cout << "Processing work: " << CW.id << " Remaining Units: "<< remainingUnits << endl;
            remainingUnits--;            
            if(remainingUnits == 0) {
                task.dequeue();  // Only dequeue when completely processed
                cout << "Done Task: " << CW.id << endl;
            }
        }
        displayWaiting();
        }
        cout << "All tasks processed"<<endl;
    }
    void displayWaiting()
    {
            cout << "Waiting Tasks:\n";
            task.display();
    }
    void displayAllTasks()
    {
        cout << "All Tasks:\n" << endl;
        task.display();
    }   
    friend ostream& operator<<(ostream& os, const Computingsystem& cs) {
        os <<"\n"<< cs.id << " - " << cs.workUnit << " units";
        return os;
    }
};
int main()
{
    Computingsystem CS;
    CS.addWork("Task1", 3);
    CS.addWork("Task2", 2);
    CS.addWork("Task3", 4);
    CS.processing();

    return 0;
}