#include <iostream>
#include <stack>
#include <string>
using namespace std;
class ExpValidator {
private:
    stack<char> brackets;
    string expression;  
public:
    ExpValidator(string exp) : expression(exp) {} 
    bool validate() {
        int mismatchPosition = -1;
        int validPairs = 0;     
        for (int i = 0; i < expression.length(); i++) {
            char ch = expression[i];           
            if (ch == '(' || ch == '[' || ch == '{') {   // Opening brackets
                brackets.push(ch);
            }
            else if (ch == ')' || ch == ']' || ch == '}') {
                if (brackets.empty()) {
                    cout << "Extra closing bracket '" << ch << "' at position " << i << endl;
                    return false;
                }               
                char top = brackets.top();               
                if ((ch == ')' && top == '(') ||   // Check exp
                    (ch == ']' && top == '[') || 
                    (ch == '}' && top == '{')) {
                    brackets.pop();
                    validPairs++;
                } else {
                    cout << "Mismatch at position " << i << endl;
                    return false;
                }
            }
        }        
        if (!brackets.empty()) {
            cout <<  brackets.size() << " opening bracket(s) not closed" << endl;
            return false;
        }        
        cout << "Expression is balanced!" << endl;
        cout << "Total valid pairs: " << validPairs << endl;
        return true;
    }
};
int main() {
    string exp;
    cout << "Enter expression: ";
    getline(cin, exp);
    ExpValidator validator(exp);
    validator.validate(); 
    return 0;
}