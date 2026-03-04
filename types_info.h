#ifndef LABA1_TYPES_INFO_H
#define LABA1_TYPES_INFO_H

#include <stddef.h>

typedef int (*ComparePtr)(const void*, const void*);
typedef void (*PrintPtr)(const void*);
typedef int (*SetValuePtr)(void *);

typedef struct type_info{
    ComparePtr compare;
    size_t elementSize;
    PrintPtr print;
    SetValuePtr set_value;
}TYPE_INFO;


#endif //LABA1_TYPES_INFO_H