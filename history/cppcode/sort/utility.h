#ifndef __UTILITY_H_
#define __UTILITY_H_

#include <memory>

namespace Utility_al{
  int *randomArray(int iSize, int max, int min=0);
  void printArray(int a[], int len);
  void mergeSort(int a[], int l, int h);
  void quickSort(int a[], int l, int h);

  std::shared_ptr<int> randomArray2(int iSize, int max, int min=0);
}

#endif // __UTILITY_H_
