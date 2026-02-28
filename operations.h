#ifndef LABA1_OPERATIONS_H
#define LABA1_OPERATIONS_H

#include "dynamicArray.h"

typedef enum {
    SORT_ERROR = -1,
    SORT_ALREADY_WAS = 0,
    SORT_COMPLETE = 1
}SORT_SIGNAL;

int concat(DYNAMIC_ARRAY *result,const DYNAMIC_ARRAY *arr1, const DYNAMIC_ARRAY *arr2);
SORT_SIGNAL bubbleSort(DYNAMIC_ARRAY* dynamic_array);
int map(DYNAMIC_ARRAY *result_array ,const DYNAMIC_ARRAY *dynamic_array, FuncForMap function);
int where(DYNAMIC_ARRAY *result,const DYNAMIC_ARRAY *dynamic_array, Predicate p);
// удостовериться, что было n вызовов функиции
#endif //LABA1_OPERATIONS_H