#include <iostream>
#include "utility.h"
#include <memory>
using namespace std;

void insertSort(int A[], int len){
  for(int i=1; i<len; ++i){
    int j = i-1;
    if(A[i] < A[j]){
      int key = A[i];
      int k = j;
      for(;k>=0; k--){
        if(A[k] > key){
          A[k+1]=A[k];
        }else{
          break;
        }
      }
      A[k] = key;
    }
  }
  Utility_al::printArray(A, len);
}

void insertSort2(int a[], int len){
  for(int i=1; i<len; ++i){
    int j = i-1;
    int t=a[i];
    int k=j;
    while(k>=0){
      if(a[k] > t){
        a[k+1]=a[k];
      }else{
        break;
      }
      --k;
    }
    a[k+1] = t;
  }
}



int main(int argc, char *argv[]) {
  int arrSize = 10;
  int *rarr = Utility_al::randomArray(arrSize,10);
  Utility_al::printArray(rarr, arrSize);
  // insertSort2(rarr, arrSize);
  Utility_al::mergeSort(rarr, 0, arrSize-1);
  Utility_al::printArray(rarr, arrSize);
  delete rarr;


  shared_ptr<int> rarr2 = Utility_al::randomArray2(arrSize,10);
  Utility_al::printArray(rarr2.get(), arrSize);
  insertSort2(rarr2.get(), arrSize);
  // Utility_al::mergeSort(rarr, 0, arrSize-1);
  Utility_al::printArray(rarr2.get(), arrSize);

  cout << "\n" << rarr2.use_count() <<endl;
  return 0;
}
