#include "dynamic_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int init_dynamic_array(DynamicArray *dynamic_array, const TypeInfo *type, size_t initial_capacity) {

    if (!dynamic_array || !type)
        return 0;

    dynamic_array->capacity = initial_capacity;
    dynamic_array->type = type;
    dynamic_array->size = 0;

    dynamic_array -> data = malloc(initial_capacity * type->element_size);

    if (!dynamic_array -> data) {
        dynamic_array->capacity = 0;

        return 0;
    }

    return 1;
}

void free_dynamic_array(DynamicArray *dynamic_array) {

    if (!dynamic_array)
        return;

    free(dynamic_array -> data);

    dynamic_array->data = NULL;
    dynamic_array->capacity = 0;
    dynamic_array->size = 0;
}

int push_back(DynamicArray *dynamic_array, const void *element) {

    if (!dynamic_array || !element)
        return 0;

    if (dynamic_array->size == dynamic_array->capacity) {
        size_t new_capacity;

        if (dynamic_array->capacity == 0)
            new_capacity = 1;

        else
            new_capacity = dynamic_array->capacity * 2;

        void *new_data = malloc(new_capacity * dynamic_array->type->element_size);

        if (!new_data)
            return 0;

        if (dynamic_array->data) // если старые данные есть, то копируем их
            memcpy(new_data, dynamic_array->data, dynamic_array->size * dynamic_array->type->element_size);

        free(dynamic_array->data);

        dynamic_array->data = new_data;
        dynamic_array->capacity = new_capacity;
    }

    void *dest = (char *)dynamic_array->data + dynamic_array->size * dynamic_array->type->element_size;

    memcpy(dest, element, dynamic_array->type->element_size);
    dynamic_array->size++;

    return 1;
}

int pop_back(DynamicArray *dynamic_array, void *save_data) {

    if (!dynamic_array || !save_data || dynamic_array->size == 0)
        return 0;

    void *dest = (char*)dynamic_array->data + (dynamic_array->size - 1) * dynamic_array->type->element_size;

    memcpy(save_data, dest, dynamic_array->type->element_size);
    dynamic_array->size--;

    return 1;
}

void* get_element(const DynamicArray *dynamic_array, size_t index) {

    if (index >= dynamic_array->size)
        return NULL;

    return (char*)dynamic_array->data + index * dynamic_array->type->element_size;
}