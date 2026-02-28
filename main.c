#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"
#include "operations.h"
#include "intType.h"
#include "doubleType.h"

void printIntArray(DYNAMIC_ARRAY *arr){
    for (size_t i = 0; i < arr->size; i++)
        printf("%d ", *(int*)getElement(arr, i));
    printf("\n");
}

void printDoubleArray(DYNAMIC_ARRAY *arr){
    for (size_t i = 0; i < arr->size; i++)
        printf("%.2f ", *(double*)getElement(arr, i));
    printf("\n");
}

void intMultiplyBy3(const void *src, void *dst){
    *(int*)dst = (*(int*)src) * 3;
}

void doubleMultiplyBy3(const void *src, void *dst){
    *(double*)dst = (*(double*)src) * 3;
}

void intSquare(const void *src, void *dst){
    int x = *(int*)src;
    *(int*)dst = x * x;
}

void doubleSquare(const void *src, void *dst){
    double x = *(double*)src;
    *(double*)dst = x * x;
}

int positiveInt(const void *e){
    return *(int*)e > 0;
}

int positiveDouble(const void *e){
    return *(double*)e > 0.0;
}

int main(){
    int typeChoice;

    printf("Выберите тип массива:\n");
    printf("1 - int\n");
    printf("2 - double\n");

    if (scanf("%d", &typeChoice) != 1 || (typeChoice != 1 && typeChoice != 2)){
        printf("Wrong type\n");
        return 1;
    }

    const TYPE_INFO *type;
    if (typeChoice == 1)
        type = getIntType();
    else
        type = getDoubleType();

    DYNAMIC_ARRAY array;

    if (!initDynamicArray(&array, type, 2)){
        printf("Memory allocation failed\n");
        return 1;
    }

    int running = 1;

    while (running){
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

        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        switch (choice){
            case 1:
            {
                if (typeChoice == 1){
                    int value;
                    printf("Enter int: ");
                    if (scanf("%d", &value) == 1)
                        pushBack(&array, &value);
                }
                else{
                    double value;
                    printf("Enter double: ");
                    if (scanf("%lf", &value) == 1)
                        pushBack(&array, &value);
                }
                break;
            }

            case 2:
            {
                if (typeChoice == 1){
                    int removed;
                    if (popBack(&array, &removed))
                        printf("Removed: %d\n", removed);
                    else
                        printf("Array empty\n");
                }
                else{
                    double removed;
                    if (popBack(&array, &removed))
                        printf("Removed: %.2f\n", removed);
                    else
                        printf("Array empty\n");
                }
                break;
            }

            case 3:
            {
                size_t index;
                printf("Index: ");
                if (scanf("%zu", &index) != 1)
                    break;

                void *elem = getElement(&array, index);

                if (!elem)
                    printf("Wrong index\n");
                else if (typeChoice == 1)
                    printf("%d\n", *(int*)elem);
                else
                    printf("%.2f\n", *(double*)elem);

                break;
            }

            case 4:
            {
                SORT_SIGNAL r = bubbleSort(&array);

                if (r == SORT_ERROR)
                    printf("Null error\n");
                else if (r == SORT_ALREADY_WAS)
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
                DYNAMIC_ARRAY result;

                if (typeChoice == 1){
                    map(&result, &array, intMultiplyBy3);
                    printIntArray(&result);
                }// int
                else{
                    map(&result, &array, doubleMultiplyBy3);
                    printDoubleArray(&result);
                }// double

                freeDynamicArray(&result);
                break;
            }

            case 8:
            {
                DYNAMIC_ARRAY result;

                if (typeChoice == 1){
                    map(&result, &array, intSquare);
                    printIntArray(&result);
                }
                else{
                    map(&result, &array, doubleSquare);
                    printDoubleArray(&result);
                }

                freeDynamicArray(&result);
                break;
            }

            case 9:
            {
                DYNAMIC_ARRAY result;

                if (typeChoice == 1){
                    where(&result, &array, positiveInt);
                    printIntArray(&result);
                }
                else{
                    where(&result, &array, positiveDouble);
                    printDoubleArray(&result);
                }

                freeDynamicArray(&result);
                break;
            }

            case 10:
            {
                DYNAMIC_ARRAY second;
                if (!initDynamicArray(&second, type, 2)){
                    printf("Memory error\n");
                    break;
                }

                int count;
                printf("How many elements? ");
                if (scanf("%d", &count) != 1){
                    freeDynamicArray(&second);
                    break;
                }

                for (int i = 0; i < count; i++){
                    if (typeChoice == 1){
                        int v;
                        printf("Enter int: ");
                        if (scanf("%d", &v) == 1)
                            pushBack(&second, &v);
                    }
                    else{
                        double v;
                        printf("Enter double: ");
                        if (scanf("%lf", &v) == 1)
                            pushBack(&second, &v);
                    }
                }

                DYNAMIC_ARRAY result;

                concat(&result, &array, &second);
                if (typeChoice == 1)
                    printIntArray(&result);
                else
                    printDoubleArray(&result);

                freeDynamicArray(&result);
                freeDynamicArray(&second);
                break;
            }

            case 0:
                running = 0;
                break;

            default:
                printf("Wrong choice\n");
        } // switch

        if (typeChoice == 1) {
            printf("\n");
            printIntArray(&array);
        }
        else {
            printf("\n");
            printDoubleArray(&array);
        }
    } // while

    freeDynamicArray(&array);
    return 0;
}