#ifndef LABA1_TYPES_INFO_H
#define LABA1_TYPES_INFO_H

#include <stddef.h>

typedef int (*ComparePtr)(const void*, const void*);

typedef struct type_info{
    ComparePtr compare;
    size_t elementSize;
}TYPE_INFO;


#endif //LABA1_TYPES_INFO_H