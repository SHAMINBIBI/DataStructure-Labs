#include <iostream>
using namespace std;
class intStaticPointer
{private:
	int* ptr;
	//int ext;
public:
	//1- default constructor
	intStaticPointer() {
		ptr = NULL;
	}
	//2-AllocMem func
	void AllocMem(int a) {
		int ext;
		ptr= &ext;
		ext=a;

	}
	void setVal(int val)
	{
		ptr = &val;
	}
	float getVal() {
		return *ptr ;
	}
	~intStaticPointer()
	{
		cout << "PTR ADDRESS :" << ptr << endl;
		cout << "PTR VALUE :" << *ptr << endl;
		
	}
};

void mystery(intStaticPointer& b)
{
	int a = 100;
	b.AllocMem(a);
	cout << b.getVal()<<endl;
}
int main()
{
	intStaticPointer b;
	int z = 8;
	b.AllocMem(z);
	cout << b.getVal()<<endl;
	mystery(b);
	cout << b.getVal()<<endl;
}






