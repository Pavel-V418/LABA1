#ifndef LABA1_DYNAMICARRAY_H
#define LABA1_DYNAMICARRAY_H

#include <stddef.h>
#include "types_info.h"

typedef struct {

    size_t size;
    size_t capacity; // вместимость
    void *data;
    const TypeInfo *type;

}DynamicArray;

int init_dynamic_array(DynamicArray *dynamic_array, const TypeInfo *type, size_t initial_capacity);
int push_back(DynamicArray *dynamic_array, const void *element);
int pop_back(DynamicArray *dynamic_array, void *save_data);

void free_dynamic_array(DynamicArray *dynamic_array);
void print_array(const DynamicArray *dynamic_array);

void* get_element(const DynamicArray *dynamic_array, size_t index);

typedef void(*FuncForMap)(const void*, void*);
typedef int (*Predicate)(const void*);


#endif //LABA1_DYNAMICARRAY_H