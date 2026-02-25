#include <assert.h>
#include <stdio.h>
#include "../dynamicArray.h"
#include "../operations.h"
#include "../intType.h"
#include "../doubleType.h"

void multiplyBy2(const void *src, void *dst)
{
    *(int*)dst = (*(int*)src) * 2;
}

int isEven(const void *elem)
{
    return (*(int*)elem) % 2 == 0;
}

void multiplyDoubleBy2(const void *src, void *dst)
{
    *(double*)dst = (*(double*)src) * 2.0;
}

int isPositiveDouble(const void *elem)
{
    return *(double*)elem > 0.0;
}
//test 1
void testCreateAndPushInt()
{
    DYNAMIC_ARRAY *arr =
        createDynamicArray(getIntType(), 2);

    assert(arr != NULL);
    assert(arr->size == 0);

    int a = 5, b = 1, c = 3;

    pushBack(arr, &a);
    pushBack(arr, &b);
    pushBack(arr, &c);

    assert(arr->size == 3);

    assert(*(int*)getElement(arr, 0) == 5);
    assert(*(int*)getElement(arr, 1) == 1);
    assert(*(int*)getElement(arr, 2) == 3);

    deleteDynamicArray(arr);
}
//test 2
void testPopInt()
{
    DYNAMIC_ARRAY *arr =
        createDynamicArray(getIntType(), 2);

    int a = 10, b = 20, c = 30;

    pushBack(arr, &a);
    pushBack(arr, &b);
    pushBack(arr, &c);

    assert(arr->size == 3);

    int removed;

    assert(popBack(arr, &removed) == 1);
    assert(removed == 30);
    assert(arr->size == 2);

    assert(popBack(arr, &removed) == 1);
    assert(removed == 20);
    assert(arr->size == 1);

    assert(popBack(arr, &removed) == 1);
    assert(removed == 10);
    assert(arr->size == 0);

    assert(popBack(arr, &removed) == 0);

    deleteDynamicArray(arr);
}
//test 3
void testSortInt()
{
    DYNAMIC_ARRAY *arr =
        createDynamicArray(getIntType(), 2);

    int a = 5, b = 1, c = 3;

    pushBack(arr, &a);
    pushBack(arr, &b);
    pushBack(arr, &c);

    bubbleSort(arr);

    assert(*(int*)getElement(arr, 0) == 1);
    assert(*(int*)getElement(arr, 1) == 3);
    assert(*(int*)getElement(arr, 2) == 5);

    deleteDynamicArray(arr);
}
//test 4
void testMapInt()
{
    DYNAMIC_ARRAY *arr =
        createDynamicArray(getIntType(), 2);

    int a = 1, b = 3, c = 5;

    pushBack(arr, &a);
    pushBack(arr, &b);
    pushBack(arr, &c);

    DYNAMIC_ARRAY *mapped =
        map(arr, multiplyBy2);

    assert(mapped->size == 3);

    assert(*(int*)getElement(mapped, 0) == 2);
    assert(*(int*)getElement(mapped, 1) == 6);
    assert(*(int*)getElement(mapped, 2) == 10);

    deleteDynamicArray(arr);
    deleteDynamicArray(mapped);
}
//test 5
void testWhereInt()
{
    DYNAMIC_ARRAY *arr =
        createDynamicArray(getIntType(), 2);

    int a = 1, b = 2, c = 3, d = 4;

    pushBack(arr, &a);
    pushBack(arr, &b);
    pushBack(arr, &c);
    pushBack(arr, &d);

    DYNAMIC_ARRAY *filtered =
        where(arr, isEven);

    assert(filtered->size == 2);
    assert(*(int*)getElement(filtered, 0) == 2);
    assert(*(int*)getElement(filtered, 1) == 4);

    deleteDynamicArray(arr);
    deleteDynamicArray(filtered);
}
// test 6
void testConcatInt()
{
    DYNAMIC_ARRAY *a =
        createDynamicArray(getIntType(), 2);

    DYNAMIC_ARRAY *b =
        createDynamicArray(getIntType(), 2);

    int x = 1, y = 2, z = 3;

    pushBack(a, &x);
    pushBack(b, &y);
    pushBack(b, &z);

    DYNAMIC_ARRAY *c = concat(a, b);

    assert(c->size == 3);
    assert(*(int*)getElement(c, 0) == 1);
    assert(*(int*)getElement(c, 1) == 2);
    assert(*(int*)getElement(c, 2) == 3);

    deleteDynamicArray(a);
    deleteDynamicArray(b);
    deleteDynamicArray(c);
}
//test 7
void testCreateAndPushDouble()
{
    DYNAMIC_ARRAY *arr =
        createDynamicArray(getDoubleType(), 2);

    assert(arr != NULL);
    assert(arr->size == 0);

    double a = 5.5, b = 1.1, c = 3.3;

    pushBack(arr, &a);
    pushBack(arr, &b);
    pushBack(arr, &c);

    assert(arr->size == 3);

    assert(*(double*)getElement(arr, 0) == 5.5);
    assert(*(double*)getElement(arr, 1) == 1.1);
    assert(*(double*)getElement(arr, 2) == 3.3);

    deleteDynamicArray(arr);
}
//test 8
void testPopDouble()
{
    DYNAMIC_ARRAY *arr =
        createDynamicArray(getDoubleType(), 2);

    double a = 1.5, b = 2.5;

    pushBack(arr, &a);
    pushBack(arr, &b);

    assert(arr->size == 2);

    double removed;

    assert(popBack(arr, &removed) == 1);
    assert(removed == 2.5);
    assert(arr->size == 1);

    assert(popBack(arr, &removed) == 1);
    assert(removed == 1.5);
    assert(arr->size == 0);

    assert(popBack(arr, &removed) == 0);

    deleteDynamicArray(arr);
}
//test 9
void testSortDouble()
{
    DYNAMIC_ARRAY *arr =
        createDynamicArray(getDoubleType(), 2);

    double a = 5.5, b = 1.1, c = 3.3;

    pushBack(arr, &a);
    pushBack(arr, &b);
    pushBack(arr, &c);

    bubbleSort(arr);

    assert(*(double*)getElement(arr, 0) == 1.1);
    assert(*(double*)getElement(arr, 1) == 3.3);
    assert(*(double*)getElement(arr, 2) == 5.5);

    deleteDynamicArray(arr);
}
//test 10
void testMapDouble()
{
    DYNAMIC_ARRAY *arr =
        createDynamicArray(getDoubleType(), 2);

    double a = 1.5, b = 3.5;

    pushBack(arr, &a);
    pushBack(arr, &b);

    DYNAMIC_ARRAY *mapped =
        map(arr, multiplyDoubleBy2);

    assert(mapped->size == 2);

    assert(*(double*)getElement(mapped, 0) == 3.0);
    assert(*(double*)getElement(mapped, 1) == 7.0);

    deleteDynamicArray(arr);
    deleteDynamicArray(mapped);
}
//test 11
void testWhereDouble()
{
    DYNAMIC_ARRAY *arr =
        createDynamicArray(getDoubleType(), 2);

    double a = -1.0, b = 2.0, c = -3.0, d = 4.0;

    pushBack(arr, &a);
    pushBack(arr, &b);
    pushBack(arr, &c);
    pushBack(arr, &d);

    DYNAMIC_ARRAY *filtered =
        where(arr, isPositiveDouble);

    assert(filtered->size == 2);
    assert(*(double*)getElement(filtered, 0) == 2.0);
    assert(*(double*)getElement(filtered, 1) == 4.0);

    deleteDynamicArray(arr);
    deleteDynamicArray(filtered);
}
//test 12
void testConcatDouble()
{
    DYNAMIC_ARRAY *a =
        createDynamicArray(getDoubleType(), 2);

    DYNAMIC_ARRAY *b =
        createDynamicArray(getDoubleType(), 2);

    double x = 1.1, y = 2.2, z = 3.3;

    pushBack(a, &x);
    pushBack(b, &y);
    pushBack(b, &z);

    DYNAMIC_ARRAY *c = concat(a, b);

    assert(c->size == 3);
    assert(*(double*)getElement(c, 0) == 1.1);
    assert(*(double*)getElement(c, 1) == 2.2);
    assert(*(double*)getElement(c, 2) == 3.3);

    deleteDynamicArray(a);
    deleteDynamicArray(b);
    deleteDynamicArray(c);
}

int main()
{
    testCreateAndPushInt();
    testPopInt();
    testSortInt();
    testMapInt();
    testWhereInt();
    testConcatInt();

    testCreateAndPushDouble();
    testPopDouble();
    testSortDouble();
    testMapDouble();
    testWhereDouble();
    testConcatDouble();

    printf("All tests passed successfully!\n");

    return 0;
}