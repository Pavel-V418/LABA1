#include <assert.h>
#include <stdio.h>
#include "../dynamic_array.h"
#include "../operations.h"
#include "../int_type.h"
#include "../double_type.h"

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

    printf("All tests passed successfully!\n");
    return 0;
}