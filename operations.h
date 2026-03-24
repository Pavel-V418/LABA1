#ifndef LABA1_OPERATIONS_H
#define LABA1_OPERATIONS_H

#include "dynamic_array.h"

typedef enum {
    SORT_ERROR = -1,
    SORT_ALREADY_SORTED = 0,
    SORT_COMPLETE = 1
}SortSignal;

SortSignal bubble_sort(DynamicArray* dynamic_array);

void concat(DynamicArray *result,const DynamicArray *arr1, const DynamicArray *arr2);
void map(DynamicArray *result_array ,const DynamicArray *dynamic_array, FuncForMap function);
void where(DynamicArray *result,const DynamicArray *dynamic_array, Predicate p);
// удостовериться, что было n вызовов функиции
#endif //LABA1_OPERATIONS_H