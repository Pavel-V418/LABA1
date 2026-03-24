#ifndef LABA1_DOUBLETYPE_H
#define LABA1_DOUBLETYPE_H

#include "types_info.h"

int set_double_value(void *elem);
int compare_doubles(const void *arg1, const void *arg2);

const TypeInfo *get_double_type(void);

void print_double(const void *elem);


#endif //LABA1_DOUBLETYPE_H