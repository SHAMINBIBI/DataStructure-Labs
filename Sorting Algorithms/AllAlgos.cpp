#include <iostream>
#include <vector>
using namespace std;

class SortingAlgorithms
{   private:
     void quickSortRecursive(vector<int> &a, int low, int high) {
        if (low < high) {
            // Partition using last element as pivot
            int pivot = a[high];
            int i = low - 1;
            
            for (int j = low; j < high; j++) {
                if (a[j] <= pivot) {
                    i++;
                    swap(a[i], a[j]);
                }
            }
            swap(a[i + 1], a[high]);
            int pi = i + 1;
            
            // Recursive calls
            quickSortRecursive(a, low, pi - 1);
            quickSortRecursive(a, pi + 1, high);
        }
    }
    
    public:
    SortingAlgorithms(vector <int> arr)
    { BubbleSort(arr);
      cout << "\n";
      SelectionSort(arr);
      cout << "\n";
      InsertionSort(arr);
      cout << "\n";
      MergeSort(arr);
      cout << "Merge Sort: ";
      for(int i = 0; i < arr.size(); i++) {
      cout << arr[i] << " ";}
      cout << "\n";
      QuickSort(arr);
      
    }
    void BubbleSort(vector<int> &arr)  //sorting by comparing adjacent elements and swapping them if they are in the wrong order
    { for(int i=0;i<arr.size();i++)  //outer loop to traverse the array
        { for (int j=0;j<arr.size()-1;j++) //loop to compare adjacent elements
          { if(arr[i]<arr[j])
             { swap(arr[i],arr[j]);}   ///the swap
          }
        }
        cout<< "Bubble Sort: "; //sorted array
        for(int i=0;i<arr.size();i++)
        { cout<<arr[i] << " " ;}
    }
    void SelectionSort(vector<int> &arr)  //sorting by repeatedly selecting the smallest element from the unsorted portion and swapping it with the first unsorted element
    {   int temp = arr.size();
        for(int i=0;i<temp;i++)  //outer loop to traverse the array
        { int max = i;
          for (int j=i+1;j<temp;j++)  //loop to find the maximum element in the unsorted portion
          { if(arr[j]<arr[max])
             { max = j;}
          }
          swap(arr[i],arr[max]); //the swap
        }
        cout<< "Selection Sort: ";  //sorted array
        for(int i=0;i<arr.size();i++)
        { cout<<arr[i] << " " ;}
     } 
    void InsertionSort(vector<int> &arr)  //sorting by building a sorted portion of the array one element at a time, by repeatedly taking the next unsorted element and inserting it into the correct position in the sorted portion
    {  vector<int> sorted;   
       for (int i = 0; i < arr.size(); i++) //loop to traverse the array
       {int current = arr[i];
        int position = 0;
        while (position < sorted.size() && sorted[position] < current) //loop to find the correct position for the current element in the sorted portion
        {  position++;
        }
        if (position == sorted.size())
        { sorted.push_back(current); //if the current element is greater than all elements in the sorted portion, add it to the end
        }
        else
        { sorted.insert(sorted.begin() + position, current);
        }
    }
        arr = sorted;
        cout<< "Insertion Sort: ";  //sorted array
        for(int i=0;i<arr.size();i++)     
         { cout<<arr[i] << " ";}
    }
    void MergeSort(vector<int> &arr) //sorting by dividing the array into two halves, sorting each half recursively, and then merging the sorted halves back together
    {  int temp = arr.size();
        if (temp <= 1) return;
        int mid = temp / 2; //divide the array into two halves
        vector<int> left(arr.begin(), arr.begin() + mid); //create a vector for the left half
        vector<int> right(arr.begin() + mid, arr.end());  //create a vector for the right half
        MergeSort(left); //sort the left half recursively
        MergeSort(right); //sort the right half recursively
        mergeHelper(left, right, arr); //merge the sorted halves back together

    }
    void mergeHelper(vector<int> &left, vector<int> &right, vector<int> &arr) //helper function to merge two sorted halves of the array
    {  int i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size())
        { if (left[i] < right[j])
          { arr[k++] = left[i++];
          }
          else
          { arr[k++] = right[j++];
          }
        }
        while (i < left.size())
        { arr[k++] = left[i++];
        }
        while (j < right.size())
        { arr[k++] = right[j++];
        }
    }
    void QuickSort(vector<int> &arr) //sorting by selecting a 'pivot' element from the array
    {  
         vector<int> temp = arr;
        quickSortRecursive(temp, 0, temp.size() - 1);
        
        cout << "Quick Sort: ";
        for(int i = 0; i < temp.size(); i++) {
            cout << temp[i] << " ";
        }
        cout << endl;
    }
};
int main()
{   SortingAlgorithms obj({5 ,2 ,4, 1, 3,6});
    return 0;
}