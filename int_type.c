#include "int_type.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct int_type{
    int value;
}Integer;

int compare_int(const void *arg1, const void *arg2) {

    const Integer *a1 = (const Integer*) arg1;
    const Integer *a2 = (const Integer*) arg2;

    if (a1->value > a2->value)
        return 1;

    if (a1->value < a2->value)
        return -1;

    return 0;
}

void print_int(const void *elem) {
    printf("%d", *(const int*)elem);
}

int set_int_value(void *elem) {
    return scanf("%d", (int*)elem);
}

void destroy_int(void *elem) {}

TypeInfo *int_type = NULL;

const TypeInfo* get_int_type(void) {

    if (!int_type) {

        int_type = malloc(sizeof(TypeInfo));

        int_type->element_size = sizeof(Integer);
        int_type->compare = compare_int;
        int_type->print = print_int;
        int_type->set_value = set_int_value;
        int_type->destroy = destroy_int;
    }

    return int_type;
}
