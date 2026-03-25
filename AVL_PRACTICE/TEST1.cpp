#include <iostream>
using namespace std;
#include <list>
template <class T>  //template
class myList:public list<T>  //inheritance used 
{ public:
  void display()   //display function , was not built in i STL so we made it
  {
     typename list<T>:: iterator temp; //iterator declaration
     temp = (*this).begin();
     while (temp!= (*this).end())
     {
        cout<< (*temp)<<endl;
        temp++;
     }
  }
  bool operator == (myList<T> &l)  //operator overloadinng for ==
  {     if (this->size() != l.size())   //if size not equal list definitely not equal
        {
            return false;
     }
        typename list<T> :: iterator temp ;
        temp = (*this).begin();
        typename list<T> :: iterator temp2;
        temp2 =  l.begin();

        while(temp!=(*this).end() )  //while loop till past-the-end
        {
            if((*temp)!= *temp2)  //comparison
            {
                return false;
            }
            temp++;   //incrementing iterators
            temp2++;
        }
        return true;
  }
};
int main()
{   myList <int> l;
    l.push_back(5);
    l.push_back(4);
    l.display();
    myList <int> l2;
    l2.push_back(5);
    l2.push_back(4);
    l2.display();
    if(l==l2)
    {
        cout << "Lists are equal"<<endl;    
    }
    return 0;
}
