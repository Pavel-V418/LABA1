#include "intType.h"
#include <stdlib.h>

typedef struct int_type{
    int value;
}INTEGER;

int compareInt(const void *arg1, const void *arg2) {
    const INTEGER *a1 = (const INTEGER*) arg1;
    const INTEGER *a2 = (const INTEGER*) arg2;
    if (a1->value > a2->value)
        return 1;
    if (a1->value < a2->value)
        return -1;
    return 0;
}

TYPE_INFO *intType = NULL;
const TYPE_INFO* getIntType(void) {
    if (!intType) {
        intType = malloc(sizeof(TYPE_INFO));
        intType->elementSize = sizeof(INTEGER);
        intType->compare = compareInt;
    }
    return intType;
}
