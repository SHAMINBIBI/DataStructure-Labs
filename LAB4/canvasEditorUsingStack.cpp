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
    {
        shapes.push(canvasEditor(i,tp));
    }
    void deleteLastShape()
    {
        if (shapes.isEmpty())
        {
            cout << "No shapes to delete" << endl;
            return;
        }
        canvasEditor lastShape = shapes.getTop();
        shapes2.push(lastShape);
        shapes.pop();
    }
    void Undo()
    {
        if (shapes2.isEmpty())
        {
            cout << "No actions to undo" << endl;
            return;
        }
        canvasEditor lastShapeDel = shapes.getTop();
        shapes2.push(lastShapeDel);
        shapes.pop();
    }
    void Redo()
    {   if (shapes2.isEmpty())
        {
            cout<< "Cannot Redo, Nothing to Redo\n";
            return;
        }

        
    }
};