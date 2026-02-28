#ifndef LABA1_OPERATIONS_H
#define LABA1_OPERATIONS_H

#include "dynamicArray.h"

DYNAMIC_ARRAY* concat(const DYNAMIC_ARRAY *arr1, const DYNAMIC_ARRAY *arr2);
int bubbleSort(DYNAMIC_ARRAY* dynamic_array);
DYNAMIC_ARRAY* where(const DYNAMIC_ARRAY *dynamic_array, Predicate p);
DYNAMIC_ARRAY* map(const DYNAMIC_ARRAY *dynamic_array, FuncForMap function);
// удостовериться, что было n вызовов функиции
#endif //LABA1_OPERATIONS_H