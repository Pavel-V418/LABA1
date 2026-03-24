#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"
#include "operations.h"
#include "int_type.h"
#include "double_type.h"

void int_multiply_by_3(const void *src, void *dst){
    *(int*)dst = (*(int*)src) * 3;
}

void double_multiply_by_3(const void *src, void *dst){
    *(double*)dst = (*(double*)src) * 3;
}

void int_square(const void *src, void *dst){
    int x = *(int*)src;
    *(int*)dst = x * x;
}

void double_square(const void *src, void *dst){
    double x = *(double*)src;
    *(double*)dst = x * x;
}

int positive_int(const void *e){
    return *(int*)e > 0;
}

int positive_double(const void *e){
    return *(double*)e > 0.0;
}

int main(){

    int type_choice;

    printf("Choose array type:\n");
    printf("1 - int\n");
    printf("2 - double\n");

    if (scanf("%d", &type_choice) != 1 || (type_choice != 1 && type_choice != 2)){
        printf("Wrong type\n");

        return 1;
    }

    const TypeInfo *type =
        (type_choice == 1) ? get_int_type() : get_double_type();

    DynamicArray array;

    if (!init_dynamic_array(&array, type, 2)){
        printf("Memory error\n");

        return 1;
    }

    int running = 1;

    while (running){

        printf("\n========== MENU ==========\n");
        printf("1. push_back\n");
        printf("2. pop_back\n");
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

        int choice;

        if (scanf("%d", &choice) != 1){
            while (getchar() != '\n');

            continue;
        }

        switch (choice){
            case 1:
            {
                char buffer[type->element_size]; // временное место в памяти для записи значения

                printf("Enter value: ");

                if (type->set_value(buffer) == 1)
                    push_back(&array, buffer);

                break;
            }

            case 2:
            {
                char buffer[type->element_size];

                if (pop_back(&array, buffer)){
                    printf("Removed: ");

                    type->print(buffer);

                    printf("\n");
                }

                else
                    printf("Array empty\n");
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
                    printf("Wrong index\n");

                else{
                    type->print(elem);
                    printf("\n");
                }

                break;
            }

            case 4:
            {
                SortSignal r = bubble_sort(&array);

                if (r == SORT_ERROR)
                    printf("Error\n");

                else if (r == SORT_ALREADY_SORTED)
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

                if (type_choice == 1)
                    map(&result, &array, int_multiply_by_3);

                else
                    map(&result, &array, double_multiply_by_3);

                print_array(&result);

                free_dynamic_array(&result);

                break;
            }

            case 8:
            {
                DynamicArray result;

                if (type_choice == 1)
                    map(&result, &array, int_square);

                else
                    map(&result, &array, double_square);

                print_array(&result);

                free_dynamic_array(&result);
                break;
            }

            case 9:
            {
                DynamicArray result;

                if (type_choice == 1)
                    where(&result, &array, positive_int);

                else
                    where(&result, &array, positive_double);

                print_array(&result);

                free_dynamic_array(&result);

                break;
            }

            case 10:
            {
                DynamicArray second;

                if (!init_dynamic_array(&second, type, 2)){
                    printf("Memory error\n");

                    break;
                }

                int count;

                printf("How many elements? ");

                if (scanf("%d", &count) != 1){
                    free_dynamic_array(&second);

                    break;
                }
                for (int i = 0; i < count; i++){
                    char buffer[type->element_size];

                    printf("Enter value: ");

                    if (type->set_value(buffer) == 1)
                        push_back(&second, buffer);
                }
                DynamicArray result;

                concat(&result, &array, &second);

                print_array(&result);

                free_dynamic_array(&result);
                free_dynamic_array(&second);

                break;
            }

            case 0:
                running = 0;

                break;

            default:
                printf("Wrong choice\n");
        } // switch

        printf("\n");

        print_array(&array);
    } // while

    free_dynamic_array(&array);

    return 0;
}