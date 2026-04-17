#include <iostream>
#include <vector>
using namespace std;

class SortingAlgorithms
{   
    
    public:
    SortingAlgorithms(vector <int> arr)
    { BubbleSort(arr);
      SelectionSort(arr);
      InsertionSort(arr);
    }
    void BubbleSort(vector<int> &arr)
    { for(int i=0;i<arr.size();i++)
        { for (int j=0;j<arr.size()-1;j++)
          { if(arr[i]<arr[j])
             { swap(arr[i],arr[j]);}
          }
        }
        cout<< "Bubble Sort: ";
        for(int i=0;i<arr.size();i++)
        { cout<<arr[i] << " " ;}
    }
    void SelectionSort(vector<int> &arr)
    {   int temp = arr.size();
        for(int i=0;i<temp;i++)
        { int max = i;
          for (int j=i+1;j<temp;j++)
          { if(arr[j]<arr[max])
             { max = j;}
          }
          swap(arr[i],arr[max]);
        }
        cout<< "Selection Sort: ";
        for(int i=0;i<arr.size();i++)
        { cout<<arr[i] << " " ;}
     } 
    void InsertionSort(vector<int> &arr) 
    {  vector<int> sorted;   
       for (int i = 0; i < arr.size(); i++)
       {int current = arr[i];
        int position = 0;
        while (position < sorted.size() && sorted[position] < current)
        {  position++;
        }
        if (position == sorted.size())
        { sorted.push_back(current);
        }
        else
        { sorted.insert(sorted.begin() + position, current);
        }
    }
        arr = sorted;
        cout<< "Insertion Sort: ";
        for(int i=0;i<arr.size();i++)     
         { cout<<arr[i] << " ";}
    }
    void MergeSort(vector<int> &arr)
    {  int temp = arr.size();
        if (temp <= 1) return;
        int mid = temp / 2;
        vector<int> left(arr.begin(), arr.begin() + mid);
        vector<int> right(arr.begin() + mid, arr.end());
        MergeSort(left);
        MergeSort(right);
        mergeHelper(left, right, arr);
      
    }
    void mergeHelper(vector<int> &left, vector<int> &right, vector<int> &arr)
    {  
      
    }
};
int main()
{   SortingAlgorithms obj({5 ,2 ,4, 1, 3,6});
    return 0;
}