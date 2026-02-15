#include "dynamicStackT.h"
#include <iostream>
using namespace std;
class canvasEditor
{
    private:
    dynamicStack <canvasEditor> shapes;
    dynamicStack <canvasEditor> shapes2;
    int id;
    string type;
    public:
    canvasEditor() : id(0), type("") {}
    canvasEditor(int i, string t) : id(i), type(t) {}
        void addShape(int i, string tp)
    {   while (!shapes2.isEmpty())
        {
        shapes2.pop();
        }  
        shapes.push(canvasEditor(i, tp));
    }
    void deleteLastShape()
    {
        if (shapes.isEmpty())
       {
        cout << "No shapes to delete" << endl;
        return;
        }
    while (!shapes2.isEmpty())  //clear redo history
    {
        shapes2.pop();
    }
    
    canvasEditor lastShape = shapes.getTop();
    shapes2.push(lastShape);
    shapes.pop();
    }
    void Undo()
    {
        if (shapes.isEmpty())
        {
            cout << "No actions to undo" << endl;
            return;
        }
        canvasEditor lastShape = shapes.getTop();
        shapes2.push(lastShape);
        shapes.pop();
    }
    void Redo()
    {   if (shapes2.isEmpty())
        {
            cout<< "Cannot Redo, Nothing to Redo\n";
            return;
        }
        canvasEditor UndoShape = shapes2.getTop();
        shapes.push(UndoShape);
        shapes2.pop();
        
    }
    void displayCanvas()
{    if (shapes.isEmpty())
    {
        cout << "Canvas is empty" << endl;
        return;
    }    
    cout << " Current Canvas " << endl;
    dynamicStack<canvasEditor> tempStack;  //temp stack to get shapes in orrder then pop in rev order   
    while (!shapes.isEmpty())
    {
        canvasEditor shape = shapes.getTop();
        tempStack.push(shape);
        shapes.pop();
    }
    int count = 1;
    while (!tempStack.isEmpty())
    {   canvasEditor shape = tempStack.getTop();
        cout << count << ". ID: " << shape.id << ", Type: " << shape.type << endl;
        count++;
        shapes.push(shape);    // Transfer back to original stack
        tempStack.pop();
    }
    }
    int getId() const { return id; }
    string getType() const { return type; }

};
int main()
{
    canvasEditor canvas;    
    cout << "Testing Canvas Editor\n";   
    canvas.addShape(1, "Circle");   // Add shapes
    canvas.addShape(2, "Rectangle");
    canvas.addShape(3, "TextBox");
    canvas.displayCanvas();    
    cout << "Deleting last shape:\n";  // Delete last shape
    canvas.deleteLastShape();
    canvas.displayCanvas();
    canvas.Undo();  // Undo
    canvas.displayCanvas();
    canvas.Redo();       // Redo
    canvas.displayCanvas();
    canvas.addShape(4, "Circle");  // Add new shape to clear redo history
    canvas.displayCanvas();
    canvas.Redo();    // now redo be fail cuz redo hist cleared    
    return 0;
}