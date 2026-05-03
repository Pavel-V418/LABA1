#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"
#include "operations.h"
#include "int_type.h"
#include "double_type.h"
#include "dyn_array_type.h"
#include "dynamic_array_io.h"

void int_multiply_by_3(const void *src, void *dst)
{
    *(int *)dst = (*(const int *)src) * 3;
}

void double_multiply_by_3(const void *src, void *dst)
{
    *(double *)dst = (*(const double *)src) * 3.0;
}

void array_of_array_multiply_by_3(const void *src, void *dst)
{
    DynamicArray *s = *(DynamicArray**)src;

    DynamicArray *new_arr = malloc(sizeof(DynamicArray));
    init_dynamic_array(new_arr, s->type, s->size);

    for (size_t i = 0; i < s->size; i++)
    {
        int *val = get_element(s, i);
        int x = (*val) * 3;
        push_back(new_arr, &x);
    }

    *(DynamicArray**)dst = new_arr;
}

void array_of_array_square(const void *src, void *dst)
{
    DynamicArray *s = *(DynamicArray**)src;

    DynamicArray *new_arr = malloc(sizeof(DynamicArray));
    if (!new_arr)
        return;

    init_dynamic_array(new_arr, get_int_type(), s->size);

    for (size_t i = 0; i < s->size; i++)
    {
        int *val = get_element(s, i);

        int x = (*val) * (*val);

        push_back(new_arr, &x);
    }

    *(DynamicArray**)dst = new_arr;
}

void int_square(const void *src, void *dst)
{
    int x = *(const int *)src;
    *(int *)dst = x * x;
}

void double_square(const void *src, void *dst)
{
    double x = *(const double *)src;
    *(double *)dst = x * x;
}

int positive_int(const void *e)
{
    return *(const int *)e > 0;
}

int positive_double(const void *e)
{
    return *(const double *)e > 0.0;
}

int size_positive(const void *elem) // без пустых массивов
{
    return (*(DynamicArray**)elem)->size > 0;
}

void print_array_menu(void)
{
    printf("\n========== MENU ==========\n");
    printf("1. pushBack\n");
    printf("2. popBack\n");
    printf("3. Get element\n");
    printf("4. Sort\n");
    printf("5. Show size\n");
    printf("6. Show capacity\n");
    printf("7. Map: multiply by 3\n");
    printf("8. Map: square\n");
    printf("9. Where: positive\n");
    printf("10. Concat\n");
    printf("0. Exit\n");
    printf("==========================\n");
    printf("Choice: ");
}

void print_type_choice_menu(void)
{
    printf("Choose type:\n");
    printf("1 - int\n");
    printf("2 - double\n");
    printf("3 - array of arrays\n");
    printf("Choice: ");
}

int main(void)
{
    int typeChoice;

    print_type_choice_menu();

    if (!set_int_value(&typeChoice) || typeChoice < 1 || typeChoice > 3)
    {
        printf("Wrong type\n");
        return 1;
    }

    const TypeInfo *type = NULL;

    if (typeChoice == 1)
        type = get_int_type();
    else if (typeChoice == 2)
        type = get_double_type();
    else
        type = get_dyn_array_type();

    if (!type)
    {
        printf("Type init failed\n");
        return 1;
    }

    DynamicArray array;

    if (!init_dynamic_array(&array, type, 2))
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    int running = 1;

    while (running)
    {
        print_array_menu();

        int choice;
        if (scanf("%d", &choice) != 1){
            while (getchar() != '\n');

            continue;
        }

        switch (choice)
        {
            case 1:
            {
                if (typeChoice == 1)
                {
                    int value;
                    printf("Enter int: ");
                    if (scanf("%d", &value) == 1)
                        push_back(&array, &value);
                }
                else if (typeChoice == 2)
                {
                    double value;
                    printf("Enter double: ");
                    if (scanf("%lf", &value) == 1)
                        push_back(&array, &value);
                }
                else
                {
                    DynamicArray *inner = malloc(sizeof(DynamicArray));
                    if (!inner)
                    {
                        printf("Memory error\n");
                        break;
                    }

                    if (!init_dynamic_array(inner, get_int_type(), 2))
                    {
                        free(inner);
                        printf("Memory error\n");
                        break;
                    }

                    int count;
                    printf("How many int elements in inner array? ");
                    if (!set_int_value(&count) || count < 0)
                    {
                        free_dynamic_array(inner);
                        free(inner);
                        printf("Wrong count\n");
                        break;
                    }

                    for (int i = 0; i < count; i++)
                    {
                        int value;
                        printf("Enter value: ");
                        if (scanf("%d", &value) == 1)
                            push_back(inner, &value);
                    }

                    push_back(&array, &inner);
                }

                break;
            }

            case 2:
            {
                if (typeChoice == 1)
                {
                    int removed;
                    if (pop_back(&array, &removed))
                        printf("Removed: %d\n", removed);
                    else
                        printf("Array empty\n");
                }
                else if (typeChoice == 2)
                {
                    double removed;
                    if (pop_back(&array, &removed))
                        printf("Removed: %.2f\n", removed);
                    else
                        printf("Array empty\n");
                }
                else
                {
                    DynamicArray *removed = NULL;
                    if (pop_back(&array, &removed))
                    {
                        printf("Removed inner array:\n");
                        print_array(removed);
                        free_dynamic_array(removed);
                        free(removed);
                    }
                    else
                    {
                        printf("Array empty\n");
                    }
                }

                break;
            }

            case 3:
            {
                size_t index;
                printf("Index: ");
                if (scanf("%zu", &index) != 1)
                    break;

                void *elem = get_element(&array, index);

                if (!elem)
                {
                    printf("Wrong index\n");
                }
                else if (typeChoice == 1)
                {
                    printf("%d\n", *(int *)elem);
                }
                else if (typeChoice == 2)
                {
                    printf("%.2f\n", *(double *)elem);
                }
                else
                {
                    DynamicArray *inner = *(DynamicArray **)elem;
                    print_array(inner);
                }

                break;
            }

            case 4:
            {
                SortSignal signal = bubble_sort(&array);

                if (signal == SORT_ERROR)
                    printf("Sort error\n");

                else if (signal == SORT_ALREADY_SORTED)
                    printf("Already sorted\n");

                else
                    printf("Sorted\n");

                break;
            }

            case 5:
                printf("Size = %zu\n", array.size);
                break;

            case 6:
                printf("Capacity = %zu\n", array.capacity);
                break;

            case 7:
            {
                DynamicArray result;

                if (typeChoice == 1)
                {
                    map(&result, &array, int_multiply_by_3);
                    print_array(&result);
                }
                else if (typeChoice == 2)
                {
                    map(&result, &array, double_multiply_by_3);
                    print_array(&result);
                }
                else
                {
                    map(&result, &array, array_of_array_multiply_by_3);
                    print_array(&result);
                }

                free_dynamic_array(&result);
                break;
            }

            case 8:
            {
                DynamicArray result;

                if (typeChoice == 1)
                {
                    map(&result, &array, int_square);
                    print_array(&result);
                }
                else if (typeChoice == 2)
                {
                    map(&result, &array, double_square);
                    print_array(&result);
                }
                else
                {
                    map(&result, &array, array_of_array_square);
                    print_array(&result);
                }

                free_dynamic_array(&result);
                break;
            }

            case 9:
            {
                DynamicArray result;

                if (typeChoice == 1)
                {
                    where(&result, &array, positive_int);
                    print_array(&result);
                }
                else if (typeChoice == 2)
                {
                    where(&result, &array, positive_double);
                    print_array(&result);
                }
                else
                {
                    where(&result, &array, size_positive);
                    print_array(&result);
                }

                free_dynamic_array(&result);
                break;
            }

            case 10:
            {
                DynamicArray second;

                if (!init_dynamic_array(&second, type, 2))
                {
                    printf("Memory error\n");
                    break;
                }

                int count;
                printf("How many elements? ");
                if (!set_int_value(&count) || count < 0)
                {
                    free_dynamic_array(&second);
                    printf("Wrong count\n");
                    break;
                }

                for (int i = 0; i < count; i++)
                {
                    if (typeChoice == 1)
                    {
                        int value;
                        printf("Enter int: ");
                        if (scanf("%d", &value) == 1)
                            push_back(&second, &value);
                    }
                    else if (typeChoice == 2)
                    {
                        double value;
                        printf("Enter double: ");
                        if (scanf("%lf", &value) == 1)
                            push_back(&second, &value);
                    }
                    else
                    {
                        DynamicArray *inner = malloc(sizeof(DynamicArray));
                        if (!inner)
                        {
                            printf("Memory error\n");
                            break;
                        }

                        if (!init_dynamic_array(inner, get_int_type(), 2))
                        {
                            free(inner);
                            printf("Memory error\n");
                            break;
                        }

                        int innerCount;
                        printf("How many int elements in inner array? ");
                        if (!set_int_value(&innerCount) || innerCount < 0)
                        {
                            free_dynamic_array(inner);
                            free(inner);
                            printf("Wrong count\n");
                            break;
                        }

                        for (int j = 0; j < innerCount; j++)
                        {
                            int value;
                            printf("Enter int: ");
                            if (scanf("%d", &value) == 1)
                                push_back(inner, &value);
                        }

                        push_back(&second, &inner);
                    }
                }

                DynamicArray result;

                concat(&result, &array, &second);
                print_array(&result);

                free_dynamic_array(&result);
                free_dynamic_array(&second);

                if (typeChoice == 3)
                    free_inner_array_elements(&second);

                break;
            }

            case 0:
                running = 0;
                break;

            default:
                printf("Wrong choice\n");
        }

        printf("\n");
        print_array(&array);
    }

    if (typeChoice == 3)
        free_inner_array_elements(&array);

    free_dynamic_array(&array);
    return 0;
}