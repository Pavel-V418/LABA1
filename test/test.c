#include <assert.h>
#include <stdio.h>
#include "../dynamicArray.h"
#include "../operations.h"
#include "../intType.h"
#include "../doubleType.h"

/* ====== Вспомогательные функции ====== */

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

/* ================= INT TESTS ================= */

void testCreateAndPushInt()
{
    DYNAMIC_ARRAY arr;
    assert(initDynamicArray(&arr, getIntType(), 2));

    int a = 5, b = 1, c = 3;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);

    assert(arr.size == 3);
    assert(*(int*)getElement(&arr, 0) == 5);
    assert(*(int*)getElement(&arr, 1) == 1);
    assert(*(int*)getElement(&arr, 2) == 3);

    freeDynamicArray(&arr);
}

void testPopInt()
{
    DYNAMIC_ARRAY arr;
    assert(initDynamicArray(&arr, getIntType(), 2));

    int a = 10, b = 20, c = 30;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);

    int removed;

    assert(popBack(&arr, &removed));
    assert(removed == 30);

    assert(popBack(&arr, &removed));
    assert(removed == 20);

    assert(popBack(&arr, &removed));
    assert(removed == 10);

    assert(popBack(&arr, &removed) == 0);

    freeDynamicArray(&arr);
}

void testSortInt()
{
    DYNAMIC_ARRAY arr;
    assert(initDynamicArray(&arr, getIntType(), 2));

    int a = 5, b = 1, c = 3;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);

    bubbleSort(&arr);

    assert(*(int*)getElement(&arr, 0) == 1);
    assert(*(int*)getElement(&arr, 1) == 3);
    assert(*(int*)getElement(&arr, 2) == 5);

    freeDynamicArray(&arr);
}

void testMapInt()
{
    DYNAMIC_ARRAY arr;
    assert(initDynamicArray(&arr, getIntType(), 2));

    int a = 1, b = 3, c = 5;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);

    DYNAMIC_ARRAY mapped;
    assert(map(&mapped, &arr, multiplyBy2));

    assert(mapped.size == 3);
    assert(*(int*)getElement(&mapped, 0) == 2);
    assert(*(int*)getElement(&mapped, 1) == 6);
    assert(*(int*)getElement(&mapped, 2) == 10);

    freeDynamicArray(&arr);
    freeDynamicArray(&mapped);
}

void testWhereInt()
{
    DYNAMIC_ARRAY arr;
    assert(initDynamicArray(&arr, getIntType(), 2));

    int a = 1, b = 2, c = 3, d = 4;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);
    pushBack(&arr, &d);

    DYNAMIC_ARRAY filtered;
    assert(where(&filtered, &arr, isEven));

    assert(filtered.size == 2);
    assert(*(int*)getElement(&filtered, 0) == 2);
    assert(*(int*)getElement(&filtered, 1) == 4);

    freeDynamicArray(&arr);
    freeDynamicArray(&filtered);
}

void testConcatInt()
{
    DYNAMIC_ARRAY a, b, result;

    assert(initDynamicArray(&a, getIntType(), 2));
    assert(initDynamicArray(&b, getIntType(), 2));

    int x = 1, y = 2, z = 3;

    pushBack(&a, &x);
    pushBack(&b, &y);
    pushBack(&b, &z);

    assert(concat(&result, &a, &b));

    assert(result.size == 3);
    assert(*(int*)getElement(&result, 0) == 1);
    assert(*(int*)getElement(&result, 1) == 2);
    assert(*(int*)getElement(&result, 2) == 3);

    freeDynamicArray(&a);
    freeDynamicArray(&b);
    freeDynamicArray(&result);
}

/* ================= DOUBLE TESTS ================= */

void testCreateAndPushDouble()
{
    DYNAMIC_ARRAY arr;
    assert(initDynamicArray(&arr, getDoubleType(), 2));

    double a = 5.5, b = 1.1, c = 3.3;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);

    assert(arr.size == 3);

    freeDynamicArray(&arr);
}

void testPopDouble()
{
    DYNAMIC_ARRAY arr;
    assert(initDynamicArray(&arr, getDoubleType(), 2));

    double a = 1.5, b = 2.5;

    pushBack(&arr, &a);
    pushBack(&arr, &b);

    double removed;

    assert(popBack(&arr, &removed));
    assert(removed == 2.5);

    assert(popBack(&arr, &removed));
    assert(removed == 1.5);

    assert(popBack(&arr, &removed) == 0);

    freeDynamicArray(&arr);
}

void testSortDouble()
{
    DYNAMIC_ARRAY arr;
    assert(initDynamicArray(&arr, getDoubleType(), 2));

    double a = 5.5, b = 1.1, c = 3.3;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);

    bubbleSort(&arr);

    assert(*(double*)getElement(&arr, 0) == 1.1);
    assert(*(double*)getElement(&arr, 1) == 3.3);
    assert(*(double*)getElement(&arr, 2) == 5.5);

    freeDynamicArray(&arr);
}

void testMapDouble()
{
    DYNAMIC_ARRAY arr;
    assert(initDynamicArray(&arr, getDoubleType(), 2));

    double a = 1.5, b = 3.5;

    pushBack(&arr, &a);
    pushBack(&arr, &b);

    DYNAMIC_ARRAY mapped;
    assert(map(&mapped, &arr, multiplyDoubleBy2));

    assert(mapped.size == 2);
    assert(*(double*)getElement(&mapped, 0) == 3.0);
    assert(*(double*)getElement(&mapped, 1) == 7.0);

    freeDynamicArray(&arr);
    freeDynamicArray(&mapped);
}

void testWhereDouble()
{
    DYNAMIC_ARRAY arr;
    assert(initDynamicArray(&arr, getDoubleType(), 2));

    double a = -1.0, b = 2.0, c = -3.0, d = 4.0;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);
    pushBack(&arr, &d);

    DYNAMIC_ARRAY filtered;
    assert(where(&filtered, &arr, isPositiveDouble));

    assert(filtered.size == 2);
    assert(*(double*)getElement(&filtered, 0) == 2.0);
    assert(*(double*)getElement(&filtered, 1) == 4.0);

    freeDynamicArray(&arr);
    freeDynamicArray(&filtered);
}

void testConcatDouble()
{
    DYNAMIC_ARRAY a, b, result;

    assert(initDynamicArray(&a, getDoubleType(), 2));
    assert(initDynamicArray(&b, getDoubleType(), 2));

    double x = 1.1, y = 2.2, z = 3.3;

    pushBack(&a, &x);
    pushBack(&b, &y);
    pushBack(&b, &z);

    assert(concat(&result, &a, &b));

    assert(result.size == 3);
    assert(*(double*)getElement(&result, 0) == 1.1);
    assert(*(double*)getElement(&result, 1) == 2.2);
    assert(*(double*)getElement(&result, 2) == 3.3);

    freeDynamicArray(&a);
    freeDynamicArray(&b);
    freeDynamicArray(&result);
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