#include "operations.h"
#include <stdlib.h>
#include "dynamicArray.h"
#include "string.h"


DYNAMIC_ARRAY* concat(const DYNAMIC_ARRAY *arr1, const DYNAMIC_ARRAY *arr2) {
    if (!arr1 || !arr2)
        return NULL;
    if (arr1->type != arr2->type)
        return NULL;
    DYNAMIC_ARRAY* result = createDynamicArray(arr1->type, arr1->size + arr2->size);
    if (!result)
        return NULL;
    memcpy(result->data, arr1->data, arr1->size * arr1->type->elementSize);
    memcpy((char*)result->data + arr1->size * arr1->type->elementSize, arr2->data, arr2->size * arr2->type->elementSize);
    result->size = arr1->size + arr2->size;
    return result;
}

int bubbleSort(DYNAMIC_ARRAY* dynamic_array) {
    if (!dynamic_array || dynamic_array->size < 2)
        return 0;
    size_t elementSize = dynamic_array->type->elementSize;
    void *swap = malloc(dynamic_array->type->elementSize);
    if (!swap)
        return 0;
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
    return was_swap;
}

DYNAMIC_ARRAY* map(const DYNAMIC_ARRAY *dynamic_array, FuncForMap function) {
    if (!dynamic_array || !function)
        return NULL;
    DYNAMIC_ARRAY *result_array = createDynamicArray(dynamic_array->type, dynamic_array->size);
    if (!result_array)
        return NULL;
    for (size_t i = 0; i < dynamic_array->size; i++) {
        void *element_i = (char*)dynamic_array->data + i * dynamic_array->type->elementSize; // i-ый элемент из исходного массива
        void *dest = (char*)result_array->data + i * dynamic_array->type->elementSize; // адрес в новом массиве
        function(element_i, dest);
    }
    result_array->size = dynamic_array->size;
    return result_array;
}

DYNAMIC_ARRAY* where(const DYNAMIC_ARRAY *dynamic_array, Predicate p) {
    if (!dynamic_array || !p)
        return NULL;
    DYNAMIC_ARRAY *result = createDynamicArray(dynamic_array->type, dynamic_array->size);
    if (!result)
        return NULL;
    for (size_t i = 0; i < dynamic_array->size; i++) {
        void *element = (char*)dynamic_array->data + i * dynamic_array->type->elementSize;
        if (p(element)) {
            pushBack(result, element);
            result->size++;
        }
    }
    return result;
}

