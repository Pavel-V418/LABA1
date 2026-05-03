#include "dynamic_array_io.h"
#include <stdio.h>

void print_array(const DynamicArray *dynamic_array){

    for (size_t i = 0; i < dynamic_array->size; i++){

        void *elem = get_element(dynamic_array, i);

        dynamic_array->type->print(elem);

        printf(" ");
    }

    printf("\n");
}