#include <random>
#include <iostream>
#include <memory>

using namespace std;

namespace Utility_al{

template< typename T >
struct array_deleter
{
  void operator ()( T const * p)
  {
    delete[] p;
  }
};

shared_ptr<int> randomArray2(int iSize, int max, int min=0){
    // using shared_ptr
    auto intArrayDeleter = [](int* i){
        delete[] i;
    };

    // shared_ptr<int> arrp(new int[iSize], intArrayDeleter);
    shared_ptr<int> arrp(new int[iSize], array_deleter<int>);
    random_device rd;
    mt19937_64 gen(rd());

    uniform_int_distribution< int > dis(min, max);

    for (int i=0; i<iSize; ++i)
        arrp.get()[i] = dis(gen);
    return arrp;
  }

  int *randomArray(int iSize, int max, int min=0){
    int *arrp = new int[iSize];
    for(int i=min; i<max; i++){

    }
    random_device rd;
    mt19937_64 gen(rd());

    /*Instead of unsigned long long, you could use std::uintmax_t from cstdint to
      get the largest possible integer range (without using an actual big-integer
      library).*/

    /* This is where you define the number generator for unsigned long long: */
    uniform_int_distribution< int > dis(min, max);
    // uniform_int_distribution<double > dis(min, max);

    /* A few random numbers: */
    for (int i=0; i<iSize; ++i)
      arrp[i] = dis(gen);
    return arrp;
  }

    void printArray(int a[], int len){
        for (int i = 0; i<len; i++) {
            cout<< a[i]<< " ";
        }
        cout<<endl;
    }

    void merge(int a[], int l, int len1, int h, int len2){
        unique_ptr<int[]> arr1 {new int[len1]};
        unique_ptr<int[]> arr2 {new int[len2]};
        // int* arr1 = new int[len1];
        // int* arr2 = new int[len2];
        for (int i=0; i<len1; i++) {
            arr1[i] = a[l+i];
        }
        for (int i=0; i<len2; i++) {
            arr2[i] = a[h+i];
        }

        int i=0, j=0;
        int k=l;// k is not start with 0, but start from l(ow)
        while(i < len1 && j < len2){
            if(arr1[i] < arr2[j]){
                a[k++] = arr1[i++];
            }else{
                a[k++] = arr2[j++];
            }
        }
        while(i < len1){
            a[k++] = arr1[i++];
        }
        while(j < len2){
            a[k++] = arr2[j++];
        }
        // delete arr1;
        // delete arr2;
    }

    void mergeSort(int a[], int l, int h){
        if(l >= h){
            return;
        }
        int mid = l + (h-l)/2;
        mergeSort(a, l, mid);
        mergeSort(a, mid+1, h);
        merge(a, l, (mid-l+1), mid+1, (h-mid));
    }

  void quickSort(int a[], int l, int h){
     
  }

}
