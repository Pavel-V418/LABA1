#include <stdio.h>
#include <stdlib.h>
#include "dyn_array_type.h"
#include "dynamic_array.h"

int compare_dyn_array(const void *arr1, const void *arr2) {

    const DynamicArray *a1 = *(const DynamicArray**) arr1;
    const DynamicArray *a2 = *(const DynamicArray**) arr2;

    if (a1->size > a2->size)
        return 1;

    if (a1->size < a2->size)
        return -1;

    return 0;
}

void print_dyn_array(const void *elem)
{
    const DynamicArray *arr = *(DynamicArray**)elem;

    printf("[ ");

    for (size_t i = 0; i < arr->size; i++)
    {
        void *item =
            (char*)arr->data +
            i * arr->type->element_size;

        arr->type->print(item);
        printf(" ");
    }

    printf("]");
}

int set_dyn_array_value(void *dynamic_array) {
    DynamicArray *arr = dynamic_array;

    int count;

    if (scanf("%d", &count) != 1)
        return 0;

    void *buffer = malloc(arr->type->element_size);

    if (!buffer)
        return 0;

    for (int i = 0; i < count; i++) {

        if (!arr->type->set_value(buffer)) {
            free(buffer);
            return 0;
        }

        push_back(arr, buffer);
    }
    free(buffer);
    return 1;
}

void destroy_inner_array_elements( void* arr ) { // удаление дин.массива, как элемента
    DynamicArray** ptr = ( DynamicArray** )arr;
    if ( *ptr != NULL ) {
        free_dynamic_array( *ptr );
        *ptr = NULL;
    }
}

TypeInfo *dyn_array_type = NULL;

const TypeInfo* get_dyn_array_type(void) {

    if (!dyn_array_type) {

        dyn_array_type = malloc(sizeof(TypeInfo));

        dyn_array_type->element_size = sizeof(DynamicArray*);
        dyn_array_type->compare = compare_dyn_array;
        dyn_array_type->print = print_dyn_array;
        dyn_array_type->set_value = set_dyn_array_value;
        dyn_array_type->destroy = destroy_inner_array_elements;
    }

    return dyn_array_type;
}