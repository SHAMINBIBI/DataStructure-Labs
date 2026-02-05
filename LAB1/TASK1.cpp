#include <iostream>
using namespace std;
int main(){
//a)Declaring nums and initializing num1
    float num1;
    float num2;
    num1=5.6;
//Declaring fPtr and making it null
    float *fPtr ;
    fPtr = NULL;
//b)derefer and display value
    // cout << "value :" << *fPtr;
//c)assign address of nu1 to fPTR
    fPtr = &num1;
//d) display val
    cout << "num1 ptr pointing value :" << *fPtr<< endl;
//e) assign fPtr to num2
    num2 = *fPtr;
    cout << "num2 value pointed by fPtr :" << num2 << endl;
//f)addres of num1
    cout <<"Address of num1 :" << &num1 <<endl;
//g) address in fPtr
    cout <<"Address of fPtr :" << fPtr<<endl;

return 0;
}
