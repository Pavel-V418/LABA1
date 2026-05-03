#ifndef LABA1_DYN_ARRAY_TYPE_H
#define LABA1_DYN_ARRAY_TYPE_H

// массив массивов
#include "types_info.h"

int compare_dyn_array(const void *arg1, const void *arg2);
int set_dyn_array_value(void *elem);
void free_inner_array_elements( void* arr );

const TypeInfo *get_dyn_array_type(void);

void print_dyn_array(const void *elem);

#endif //LABA1_DYN_ARRAY_TYPE_H
