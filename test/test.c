#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../dynamic_array.h"
#include "../operations.h"
#include "../int_type.h"
#include "../double_type.h"
#include "../dyn_array_type.h"

/* ====== Вспомогательные функции ====== */

void multiply_int_by_2(const void *src, void *dst){
    *(int*)dst = (*(int*)src) * 2;
}

int is_even(const void *elem){
    return (*(int*)elem) % 2 == 0;
}

void multiply_double_by_2(const void *src, void *dst){
    *(double*)dst = (*(double*)src) * 2.0;
}

int is_positive_double(const void *elem){
    return *(double*)elem > 0.0;
}

// map для массива массивов
void map_inner_int_x2(const void *src, void *dst)
{
    DynamicArray *s = *(DynamicArray**)src;

    DynamicArray *new_arr = malloc(sizeof(DynamicArray));
    init_dynamic_array(new_arr, get_int_type(), s->size);

    for (size_t i = 0; i < s->size; i++)
    {
        int *val = get_element(s, i);
        int x = (*val) * 2;
        push_back(new_arr, &x);
    }

    *(DynamicArray**)dst = new_arr;
}

// where для массива массивов
int no_negative_elements(const void *elem)
{
    DynamicArray *arr = *(DynamicArray**)elem;

    for (size_t i = 0; i < arr->size; i++)
    {
        int *value = get_element(arr, i);
        if (*value < 0)
            return 0;
    }

    return 1;
}

/* ================= INT TESTS ================= */

void test_init_and_push_int(){

    DynamicArray arr;
    assert(init_dynamic_array(&arr, get_int_type(), 2));

    int a = 5, b = 1, c = 3;

    push_back(&arr, &a);
    push_back(&arr, &b);
    push_back(&arr, &c);

    assert(arr.size == 3);
    assert(*(int*)get_element(&arr, 0) == 5);
    assert(*(int*)get_element(&arr, 1) == 1);
    assert(*(int*)get_element(&arr, 2) == 3);

    free_dynamic_array(&arr);
}

void test_pop_int(){

    DynamicArray arr;
    assert(init_dynamic_array(&arr, get_int_type(), 2));

    int a = 10, b = 20, c = 30;

    push_back(&arr, &a);
    push_back(&arr, &b);
    push_back(&arr, &c);

    int removed;

    assert(pop_back(&arr, &removed));
    assert(removed == 30);

    assert(pop_back(&arr, &removed));
    assert(removed == 20);

    assert(pop_back(&arr, &removed));
    assert(removed == 10);

    assert(pop_back(&arr, &removed) == 0);

    free_dynamic_array(&arr);
}

void test_sort_int(){

    DynamicArray arr;
    assert(init_dynamic_array(&arr, get_int_type(), 2));

    int a = 5, b = 1, c = 3;

    push_back(&arr, &a);
    push_back(&arr, &b);
    push_back(&arr, &c);

    bubble_sort(&arr);

    assert(*(int*)get_element(&arr, 0) == 1);
    assert(*(int*)get_element(&arr, 1) == 3);
    assert(*(int*)get_element(&arr, 2) == 5);

    free_dynamic_array(&arr);
}

void test_map_int(){

    DynamicArray arr;
    assert(init_dynamic_array(&arr, get_int_type(), 2));

    int a = 1, b = 3, c = 5;

    push_back(&arr, &a);
    push_back(&arr, &b);
    push_back(&arr, &c);

    DynamicArray mapped;
    map(&mapped, &arr, multiply_int_by_2);

    assert(mapped.size == 3);
    assert(*(int*)get_element(&mapped, 0) == 2);
    assert(*(int*)get_element(&mapped, 1) == 6);
    assert(*(int*)get_element(&mapped, 2) == 10);

    free_dynamic_array(&arr);
    free_dynamic_array(&mapped);
}

void test_where_int(){

    DynamicArray arr;
    assert(init_dynamic_array(&arr, get_int_type(), 2));

    int a = 1, b = 2, c = 3, d = 4;

    push_back(&arr, &a);
    push_back(&arr, &b);
    push_back(&arr, &c);
    push_back(&arr, &d);

    DynamicArray filtered;
    where(&filtered, &arr, is_even);

    assert(filtered.size == 2);
    assert(*(int*)get_element(&filtered, 0) == 2);
    assert(*(int*)get_element(&filtered, 1) == 4);

    free_dynamic_array(&arr);
    free_dynamic_array(&filtered);
}

void test_concat_int(){

    DynamicArray a, b, result;

    assert(init_dynamic_array(&a, get_int_type(), 2));
    assert(init_dynamic_array(&b, get_int_type(), 2));

    int x = 1, y = 2, z = 3;

    push_back(&a, &x);
    push_back(&b, &y);
    push_back(&b, &z);

    concat(&result, &a, &b);

    assert(result.size == a.size + b.size);

    assert(*(int*)get_element(&result, 0) == 1);
    assert(*(int*)get_element(&result, 1) == 2);
    assert(*(int*)get_element(&result, 2) == 3);

    free_dynamic_array(&a);
    free_dynamic_array(&b);
    free_dynamic_array(&result);
}

/* ================= DOUBLE TESTS ================= */

void test_init_and_push_double(){

    DynamicArray arr;
    assert(init_dynamic_array(&arr, get_double_type(), 2));

    double a = 5.5, b = 1.1, c = 3.3;

    push_back(&arr, &a);
    push_back(&arr, &b);
    push_back(&arr, &c);

    assert(arr.size == 3);
    assert(*(double*)get_element(&arr,0) == 5.5);
    assert(*(double*)get_element(&arr,1) == 1.1);
    assert(*(double*)get_element(&arr,2) == 3.3);

    free_dynamic_array(&arr);
}

void test_pop_double(){

    DynamicArray arr;
    assert(init_dynamic_array(&arr, get_double_type(), 2));

    double a = 1.5, b = 2.5;

    push_back(&arr, &a);
    push_back(&arr, &b);

    double removed;

    assert(pop_back(&arr, &removed));
    assert(removed == 2.5);

    assert(pop_back(&arr, &removed));
    assert(removed == 1.5);

    assert(pop_back(&arr, &removed) == 0);

    free_dynamic_array(&arr);
}

void test_sort_double(){

    DynamicArray arr;
    assert(init_dynamic_array(&arr, get_double_type(), 2));

    double a = 5.5, b = 1.1, c = 3.3;

    push_back(&arr, &a);
    push_back(&arr, &b);
    push_back(&arr, &c);

    bubble_sort(&arr);

    assert(*(double*)get_element(&arr, 0) == 1.1);
    assert(*(double*)get_element(&arr, 1) == 3.3);
    assert(*(double*)get_element(&arr, 2) == 5.5);

    free_dynamic_array(&arr);
}

void test_map_double(){

    DynamicArray arr;
    assert(init_dynamic_array(&arr, get_double_type(), 2));

    double a = 1.5, b = 3.5;

    push_back(&arr, &a);
    push_back(&arr, &b);

    DynamicArray mapped;
    map(&mapped, &arr, multiply_double_by_2);

    assert(mapped.size == 2);
    assert(*(double*)get_element(&mapped, 0) == 3.0);
    assert(*(double*)get_element(&mapped, 1) == 7.0);

    free_dynamic_array(&arr);
    free_dynamic_array(&mapped);
}

void test_where_double(){

    DynamicArray arr;
    assert(init_dynamic_array(&arr, get_double_type(), 2));

    double a = -1.0, b = 2.0, c = -3.0, d = 4.0;

    push_back(&arr, &a);
    push_back(&arr, &b);
    push_back(&arr, &c);
    push_back(&arr, &d);

    DynamicArray filtered;
    where(&filtered, &arr, is_positive_double);

    assert(filtered.size == 2);
    assert(*(double*)get_element(&filtered, 0) == 2.0);
    assert(*(double*)get_element(&filtered, 1) == 4.0);

    free_dynamic_array(&arr);
    free_dynamic_array(&filtered);
}

void test_concat_double(){

    DynamicArray a, b, result;

    assert(init_dynamic_array(&a, get_double_type(), 2));
    assert(init_dynamic_array(&b, get_double_type(), 2));

    double x = 1.1, y = 2.2, z = 3.3;

    push_back(&a, &x);
    push_back(&b, &y);
    push_back(&b, &z);

    concat(&result, &a, &b);

    assert(result.size == a.size + b.size);
    assert(*(double*)get_element(&result, 0) == 1.1);
    assert(*(double*)get_element(&result, 1) == 2.2);
    assert(*(double*)get_element(&result, 2) == 3.3);

    free_dynamic_array(&a);
    free_dynamic_array(&b);
    free_dynamic_array(&result);
}

/* ================= ARRAY OF ARRAY TESTS ================= */

void test_array_of_arrays_push()
{
    DynamicArray outer;
    assert(init_dynamic_array(&outer, get_dyn_array_type(), 2));

    DynamicArray *inner = malloc(sizeof(DynamicArray));
    init_dynamic_array(inner, get_int_type(), 2);

    int a = 1, b = 2;
    push_back(inner, &a);
    push_back(inner, &b);

    push_back(&outer, &inner);

    assert(outer.size == 1);

    DynamicArray *res = *(DynamicArray**)get_element(&outer, 0);
    assert(res->size == 2);
    assert(*(int*)get_element(res, 0) == 1);
    assert(*(int*)get_element(res, 1) == 2);

    free_dynamic_array(inner);
    free(inner);
    free_dynamic_array(&outer);
}

void test_array_of_arrays_pop()
{
    DynamicArray outer;
    assert(init_dynamic_array(&outer, get_dyn_array_type(), 2));

    DynamicArray *inner1 = malloc(sizeof(DynamicArray));
    init_dynamic_array(inner1, get_int_type(), 2);

    int a = 1;
    push_back(inner1, &a);

    DynamicArray *inner2 = malloc(sizeof(DynamicArray));
    init_dynamic_array(inner2, get_int_type(), 2);

    int b = 2;
    push_back(inner2, &b);

    push_back(&outer, &inner1);
    push_back(&outer, &inner2);

    assert(outer.size == 2);

    DynamicArray *removed;

    assert(pop_back(&outer, &removed));
    assert(outer.size == 1);

    // проверяем, что вытащился именно inner2
    assert(*(int*)get_element(removed, 0) == 2);

    // чистим
    free_dynamic_array(removed);
    free(removed);

    // ещё один pop
    assert(pop_back(&outer, &removed));
    assert(outer.size == 0);

    assert(*(int*)get_element(removed, 0) == 1);

    free_dynamic_array(removed);
    free(removed);

    assert(pop_back(&outer, &removed) == 0);

    free_dynamic_array(&outer);
}

void test_array_of_arrays_sort()
{
    DynamicArray outer;
    assert(init_dynamic_array(&outer, get_dyn_array_type(), 2));

    // size = 3
    DynamicArray *a = malloc(sizeof(DynamicArray));
    init_dynamic_array(a, get_int_type(), 3);
    int a1 = 1, a2 = 2, a3 = 3;
    push_back(a, &a1);
    push_back(a, &a2);
    push_back(a, &a3);

    // size = 1
    DynamicArray *b = malloc(sizeof(DynamicArray));
    init_dynamic_array(b, get_int_type(), 1);
    int b1 = 10;
    push_back(b, &b1);

    // size = 2
    DynamicArray *c = malloc(sizeof(DynamicArray));
    init_dynamic_array(c, get_int_type(), 2);
    int c1 = 5, c2 = 6;
    push_back(c, &c1);
    push_back(c, &c2);

    push_back(&outer, &a);
    push_back(&outer, &b);
    push_back(&outer, &c);

    bubble_sort(&outer);

    DynamicArray *r0 = *(DynamicArray**)get_element(&outer, 0);
    DynamicArray *r1 = *(DynamicArray**)get_element(&outer, 1);
    DynamicArray *r2 = *(DynamicArray**)get_element(&outer, 2);

    assert(r0->size == 1);
    assert(r1->size == 2);
    assert(r2->size == 3);

    // очистка
    free_dynamic_array(a); free(a);
    free_dynamic_array(b); free(b);
    free_dynamic_array(c); free(c);

    free_dynamic_array(&outer);
}

void test_array_of_arrays_sort_already_sorted()
{
    DynamicArray outer;
    assert(init_dynamic_array(&outer, get_dyn_array_type(), 2));

    DynamicArray *a = malloc(sizeof(DynamicArray));
    init_dynamic_array(a, get_int_type(), 1);
    int x = 1;
    push_back(a, &x);

    DynamicArray *b = malloc(sizeof(DynamicArray));
    init_dynamic_array(b, get_int_type(), 2);
    int y1 = 1, y2 = 2;
    push_back(b, &y1);
    push_back(b, &y2);

    push_back(&outer, &a);
    push_back(&outer, &b);

    SortSignal res = bubble_sort(&outer);

    assert(res == SORT_ALREADY_SORTED);

    free_dynamic_array(a); free(a);
    free_dynamic_array(b); free(b);
    free_dynamic_array(&outer);
}

void test_array_of_arrays_map()
{
    DynamicArray outer;
    assert(init_dynamic_array(&outer, get_dyn_array_type(), 2));

    DynamicArray *inner = malloc(sizeof(DynamicArray));
    init_dynamic_array(inner, get_int_type(), 2);

    int a = 2, b = 3;
    push_back(inner, &a);
    push_back(inner, &b);

    push_back(&outer, &inner);

    DynamicArray mapped;
    map(&mapped, &outer, map_inner_int_x2);

    DynamicArray *res = *(DynamicArray**)get_element(&mapped, 0);

    assert(*(int*)get_element(res, 0) == 4);
    assert(*(int*)get_element(res, 1) == 6);

    free_dynamic_array(inner);
    free(inner);
    free_dynamic_array(res);
    free(res);

    free_dynamic_array(&outer);
    free_dynamic_array(&mapped);
}

void test_array_of_arrays_where()
{
    DynamicArray outer;
    assert(init_dynamic_array(&outer, get_dyn_array_type(), 2));

    // good array
    DynamicArray *a1 = malloc(sizeof(DynamicArray));
    init_dynamic_array(a1, get_int_type(), 2);

    int x1 = 1, x2 = 2;
    push_back(a1, &x1);
    push_back(a1, &x2);

    // bad array
    DynamicArray *a2 = malloc(sizeof(DynamicArray));
    init_dynamic_array(a2, get_int_type(), 2);

    int y1 = -1, y2 = 5;
    push_back(a2, &y1);
    push_back(a2, &y2);

    push_back(&outer, &a1);
    push_back(&outer, &a2);

    DynamicArray filtered;
    where(&filtered, &outer, no_negative_elements);

    assert(filtered.size == 1);

    DynamicArray *res = *(DynamicArray**)get_element(&filtered, 0);
    assert(res->size == 2);

    free_dynamic_array(a1);
    free(a1);
    free_dynamic_array(a2);
    free(a2);

    free_dynamic_array(&outer);
    free_dynamic_array(&filtered);
}

void test_array_of_arrays_concat()
{
    DynamicArray a, b, result;

    assert(init_dynamic_array(&a, get_dyn_array_type(), 2));
    assert(init_dynamic_array(&b, get_dyn_array_type(), 2));

    DynamicArray *inner1 = malloc(sizeof(DynamicArray));
    init_dynamic_array(inner1, get_int_type(), 2);

    int x = 1;
    push_back(inner1, &x);

    DynamicArray *inner2 = malloc(sizeof(DynamicArray));
    init_dynamic_array(inner2, get_int_type(), 2);

    int y = 2;
    push_back(inner2, &y);

    push_back(&a, &inner1);
    push_back(&b, &inner2);

    concat(&result, &a, &b);

    assert(result.size == 2);

    free_dynamic_array(inner1);
    free(inner1);
    free_dynamic_array(inner2);
    free(inner2);

    free_dynamic_array(&a);
    free_dynamic_array(&b);
    free_dynamic_array(&result);
}



int main(){

    test_init_and_push_int();
    test_pop_int();
    test_sort_int();
    test_map_int();
    test_where_int();
    test_concat_int();

    test_init_and_push_double();
    test_pop_double();
    test_sort_double();
    test_map_double();
    test_where_double();
    test_concat_double();

    test_array_of_arrays_push();
    test_array_of_arrays_pop();
    test_array_of_arrays_sort();
    test_array_of_arrays_sort_already_sorted();
    test_array_of_arrays_map();
    test_array_of_arrays_where();
    test_array_of_arrays_concat();

    printf("All tests passed successfully!\n");
    return 0;
}