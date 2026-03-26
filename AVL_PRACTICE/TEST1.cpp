#include <iostream>
using namespace std;
#include <algorithm>
double kg_to_g(double in)
{
    return (in*1000);
}
int main()
{
    double kg[]={1,2,3,4,5};
    double g[5];
    transform(kg,kg+5,g,kg_to_g);
    for(int i=0;i<5;i++)
    {
        cout << g[i] << endl;
    }

   return 0;
}





// #include <iostream>
// using namespace std;
// #include <list>
// template <class T>  
// class myList:public list<T>  //inheritance 
// { public:
//   void display()   //display function 
//   {
//      typename list<T>:: iterator temp; //iterator declaration
//      temp = (*this).begin();
//      while (temp!= (*this).end())
//      {
//         cout<< (*temp)<<endl;
//         temp++;
//      }
//   }
//   bool operator == (myList<T> &l)  //operator overloadinng for ==
//   {     typename list<T>:: iterator temp1; 
//         typename list<T>:: iterator temp2;
//         temp1 = (*this).begin();
//         temp2 = l.begin();
//         while (temp1!= (*this).end() && temp2!= l.end())
//         {
//             if((*temp1) != (*temp2))
//             {
//                 return false;
//             }
//             temp1++;
//             temp2++;
//         }
//         if(temp1 == (*this).end() && temp2 == l.end())
//         {
//             return true;
//         }
//         else
//         {
//             return false;
//         }
//   }
// };
// int main()
// {   myList <int> l;
//     l.push_back(1);
//     l.push_back(2);
//     l.display();
//     myList <int> l2;
//     l2.push_back(1);
//     l2.push_back(2);
//     l2.display();
//     if(l==l2)
//     {
//         cout << "EQUAL"<<endl;    
//     }
//     return 0;
// }
