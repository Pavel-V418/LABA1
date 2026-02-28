#include "operations.h"
#include <stdlib.h>
#include "dynamicArray.h"
#include "string.h"


void concat(DYNAMIC_ARRAY *result,const DYNAMIC_ARRAY *arr1, const DYNAMIC_ARRAY *arr2) {
    if (!arr1 || !arr2 || !result)
        return;
    if (arr1->type != arr2->type)
        return;
    if (!initDynamicArray(result, arr1->type, arr1->size + arr2->size))
        return;
    size_t element_size = arr1->type->elementSize;
    memcpy(result->data, arr1->data, arr1->size * element_size);
    memcpy((char*)result->data + arr1->size * element_size, arr2->data,arr2->size * element_size);
    result->size = arr1->size + arr2->size;
}

SORT_SIGNAL bubbleSort(DYNAMIC_ARRAY* dynamic_array) {
    if (!dynamic_array || dynamic_array->size < 2)
        return SORT_ERROR;
    size_t elementSize = dynamic_array->type->elementSize;
    void *swap = malloc(dynamic_array->type->elementSize);
    if (!swap)
        return SORT_ERROR;
    int was_swap = 0;
    for (size_t i =0; i < dynamic_array->size - 1; i++) {
        int cycle_swap = 0;
        for (size_t j = 0; j < dynamic_array->size - i - 1; j++) {
            void *element1 = (char*)dynamic_array->data + j * elementSize;
            void *element2 = (char*)dynamic_array->data + (j + 1) * elementSize;
            if (dynamic_array->type->compare(element1, element2) > 0) {
                memcpy(swap, element1, elementSize);
                memcpy(element1, element2, elementSize);
                memcpy(element2, swap, elementSize);
                cycle_swap = 1;
                was_swap = 1;
            }
        }
        if (!cycle_swap)
            break;
    }
    free(swap);
    if (!was_swap)
        return SORT_ALREADY_WAS;
    return SORT_COMPLETE;
}

void map(DYNAMIC_ARRAY *result_array ,const DYNAMIC_ARRAY *dynamic_array, FuncForMap function) {
    if (!dynamic_array || !function || !result_array)
        return;
    if (!initDynamicArray(result_array, dynamic_array->type, dynamic_array->size))
        return;
    for (size_t i = 0; i < dynamic_array->size; i++) {
        void *element_i = (char*)dynamic_array->data + i * dynamic_array->type->elementSize; // i-ый элемент из исходного массива
        void *dest = (char*)result_array->data + i * dynamic_array->type->elementSize; // адрес в новом массиве
        function(element_i, dest);
    }
    result_array->size = dynamic_array->size;
}

void where(DYNAMIC_ARRAY *result,const DYNAMIC_ARRAY *dynamic_array, Predicate p) {
    if (!dynamic_array || !p || !result)
        return;
    if (!initDynamicArray(result, dynamic_array->type, dynamic_array->size))
        return;
    for (size_t i = 0; i < dynamic_array->size; i++) {
        void *element = (char*)dynamic_array->data + i * dynamic_array->type->elementSize;
        if (p(element)) {
            pushBack(result, element);
        }
    }
}

