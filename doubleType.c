#include "doubleType.h"
#include <stdlib.h>

typedef struct double_type{
    double value;
}DOUBLE;

int compareDoubles(const void *arg1, const void *arg2) {
    const DOUBLE *a1 = (const DOUBLE*) arg1;
    const DOUBLE *a2 = (const DOUBLE*) arg2;
    if (a1->value > a2->value)
        return 1;
    if (a1->value < a2->value)
        return -1;
    return 0;
}

TYPE_INFO *doubleType = NULL;
const TYPE_INFO *getDoubleType(void) {
    if (!doubleType) {
        doubleType = malloc(sizeof(TYPE_INFO));
        doubleType -> compare = compareDoubles;
        doubleType -> elementSize = sizeof(DOUBLE);
    }
    return doubleType;
}
