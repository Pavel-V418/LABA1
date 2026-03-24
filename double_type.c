#include "double_type.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct double_type{
    double value;
}DoubleType;

int compare_doubles(const void *arg1, const void *arg2) {

    const DoubleType *a1 = (const DoubleType*) arg1;
    const DoubleType *a2 = (const DoubleType*) arg2;

    if (a1->value > a2->value)
        return 1;

    if (a1->value < a2->value)
        return -1;

    return 0;
}

void print_double(const void *elem) {
    printf("%.2lf", *(const double*)elem);
}

int set_double_value(void *elem) {
    return scanf("%lf", (double*)elem);
}

TypeInfo *double_type = NULL;

const TypeInfo *get_double_type(void) {

    if (!double_type) {

        double_type = malloc(sizeof(TypeInfo));

        double_type -> compare = compare_doubles;
        double_type -> element_size = sizeof(DoubleType);
        double_type -> print = print_double;
        double_type -> set_value = set_double_value;
    }

    return double_type;
}
