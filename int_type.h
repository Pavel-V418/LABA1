#ifndef LABA1_INTTYPE_H
#define LABA1_INTTYPE_H

#include "types_info.h"

int compare_int(const void *arg1, const void *arg2);
int set_int_value(void *elem);

void destroy_int(void *elem);

const TypeInfo *get_int_type(void);

void print_int(const void *elem);


#endif //LABA1_INTTYPE_H