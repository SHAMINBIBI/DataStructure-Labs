#include <iostream>
using namespace std;

class Task{
    private:
    string task;
    string taskID;
    string deadline;
    public:
    //default connstructor
    Task(){ 
        task = "NIL";
        taskID ="NIL";
        deadline = "NIL";
    }
    //parameterized constructor
    Task(string t, string id, string dd)
    {
        task = t;
        taskID = id;
        deadline = dd;
    }
    //setters
    void setTask(string t)
    { task = t;}
    void setTaskID(string tid)
    { taskID = tid;}
    void setDeadline(string d)
    { deadline = d;}
    //copy const. 
    void copyFrom(const Task& other) {
        task = other.task;
        taskID = other.taskID;
        deadline = other.deadline;
    }
    //getters
    string getTask(){ return task;}
    string getTaskID(){ return taskID;}
    string getDeadline(){return deadline;}
};
class To_doList
{   private:
    Task *ptr;  //dynamic array
    int size;   // current number of tasks
    int capacity;  // current capacity of array
    
    public:
    //def const
    To_doList(): ptr(NULL), size(0), capacity(0){}
    //para const
    To_doList(Task task)
    {   size =1;
        capacity =1;
        ptr = new Task [capacity];
        ptr[0].copyFrom(task); 
    }
    //copy const
    To_doList(const To_doList &obj):size(obj.size), capacity(obj.capacity)
    {   ptr = new Task[capacity];
        for (int i=0; i < size; i++)
        { ptr[i].copyFrom(obj.ptr[i]);
}
    }
    void addTask(Task newtsk)
    {  for (int i=0; i <size;i++)
        { if (newtsk.getTaskID() == ptr[i].getTaskID())
            {  cout<< " TASK ID : " << newtsk.getTaskID() << "already exists!!!"<< endl;
             return; 
            }
           
        }
        //if array is full
        if (size == capacity)
        {
            int newcapacity = (capacity ==0) ? 1: capacity * 2; //new capacity
            Task *newPtr = new Task [newcapacity]; //new array
            //copy tasks to new array
            for (int i =0;i<size ;i++)
            {
                newPtr[i].copyFrom(ptr[i]);
            }
            delete [] ptr; // delete old array
            ptr= newPtr;
            capacity = newcapacity;
        }
        //add new task
        ptr[size].copyFrom(newtsk);
        size++;
        cout<< "NEW TASK ADDED SUCCESFULLY!!" << endl;
    }
    void removeTask(string rtsk)
    {   int index =-1;
        for (int i=0; i<size ;i++)
        { if (rtsk == ptr[i].getTaskID())
            { index = i;
            break;
            }
        } 
        //if task not  found
        if(index ==-1)
        {
            cout<< "TASK NOT FOUND!" << endl;
            return;
        }
        for (int i = index; i < size - 1; i++)  // Shift tasks left to fill the gap
        {
            ptr[i].copyFrom(ptr[i + 1]);
        }
        size--;
         cout << "Task with ID " << rtsk << " removed successfully!" << endl;
    }
         // Display all tasks
    void displayTasks()
    {
        if (size == 0)
        {
            cout << "No tasks in the list!" << endl;
            return;
        }
        
        cout << "\nTO DO LIST    " << endl;
        for (int i = 0; i < size; i++)
        {
            cout << i+1 << ". ID: " << ptr[i].getTaskID()
                 << "\nTask: " << ptr[i].getTask()
                 << "\nDeadline: " << ptr[i].getDeadline() << endl;
        }
        cout << "Total tasks: " << size << endl;
        cout << "Array capacity: " << capacity << endl;
    }
       
    // Get current size
    int getSize() { return size; }
    
    // Get current capacity
    int getCapacity() { return capacity; }

    ~To_doList(){
       delete[] ptr; 
    }
    
} ;
int main()
{
    // Create some tasks
    Task t1("PERFORM LAB", "TK1", "23-1-2026");
    Task t2("STUDY FOR QUIZ", "TK2", "2-2-2026");
    Task t3("READ BOOK", "TK3", "30-1-2026");
    
    // Create list with first task
    To_doList myList(t1);
    myList.displayTasks();
    
    // Add more tasks
    myList.addTask(t2);
    myList.addTask(t3);
    myList.displayTasks();
    
    // Try to add duplicate
    myList.addTask(t2);
    
    // Remove a task
    myList.removeTask("TK2");
    myList.displayTasks();
    
    // Test copy constructor
    To_doList copiedList = myList;
    cout << "\nCopied list:" << endl;
    copiedList.displayTasks();
    
    return 0;
}