#include "dynamicArray.h"
#include <stdlib.h>
#include <string.h>

DYNAMIC_ARRAY* createDynamicArray(const TYPE_INFO *type, size_t initialCapacity) {
    DYNAMIC_ARRAY* dynamic_array = malloc(sizeof(DYNAMIC_ARRAY));
    if (!dynamic_array)
        return NULL;
    dynamic_array -> size = 0;
    dynamic_array -> capacity = initialCapacity;
    dynamic_array -> type = type;
    dynamic_array -> data = malloc(initialCapacity * (type->elementSize));
    if (!dynamic_array -> data) {
        free(dynamic_array);
        return NULL;
    }
    return dynamic_array;
}

void deleteDynamicArray(DYNAMIC_ARRAY *dynamic_array) {
    if (!dynamic_array)
        return;
    free(dynamic_array -> data);
    free(dynamic_array);
}

int pushBack(DYNAMIC_ARRAY *dynamic_array, const void *element) {
    if (!dynamic_array || !element)
        return 0;
    if (dynamic_array->size == dynamic_array->capacity) {
        size_t newCapacity;
        if (dynamic_array->capacity == 0)
            newCapacity = 1;
        else
            newCapacity = dynamic_array->capacity * 2;
        void *newData = malloc(newCapacity * dynamic_array->type->elementSize);
        if (!newData)
            return 0;
        if (dynamic_array->data) // если старые данные есть, то копируем их
            memcpy(newData, dynamic_array->data, dynamic_array->size * dynamic_array->type->elementSize);
        free(dynamic_array->data);
        dynamic_array->data = newData;
        dynamic_array->capacity = newCapacity;
    }
    void *dest = (char *)dynamic_array->data + dynamic_array->size * dynamic_array->type->elementSize;
    memcpy(dest, element, dynamic_array->type->elementSize);
    dynamic_array->size++;
    return 1;
}

int popBack(DYNAMIC_ARRAY *dynamic_array, void *save_data) {
    if (!dynamic_array || dynamic_array->size == 0)
        return 0;
    void *dest = (char*)dynamic_array->data + (dynamic_array->size - 1) * dynamic_array->type->elementSize;
    memcpy(save_data, dest, dynamic_array->type->elementSize);
    dynamic_array->size--;
    return 1;
}

void* getElement(DYNAMIC_ARRAY *dynamic_array, size_t index) {
    if (index >= dynamic_array->size)
        return NULL;
    return (char*)dynamic_array->data + index * dynamic_array->type->elementSize;
}
