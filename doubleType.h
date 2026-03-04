#ifndef LABA1_DOUBLETYPE_H
#define LABA1_DOUBLETYPE_H

#include "types_info.h"

const TYPE_INFO *getDoubleType(void);
int compareDoubles(const void *arg1, const void *arg2);
void printDouble(const void *elem);
int setDoubleValue(void *elem);

#endif //LABA1_DOUBLETYPE_H