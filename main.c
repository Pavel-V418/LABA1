#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"
#include "operations.h"
#include "intType.h"
#include "doubleType.h"

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

    printf("Choose array type:\n");
    printf("1 - int\n");
    printf("2 - double\n");

    if (scanf("%d", &typeChoice) != 1 || (typeChoice != 1 && typeChoice != 2)){
        printf("Wrong type\n");
        return 1;
    }

    const TYPE_INFO *type =
        (typeChoice == 1) ? getIntType() : getDoubleType();

    DYNAMIC_ARRAY array;

    if (!initDynamicArray(&array, type, 2)){
        printf("Memory error\n");
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

        if (scanf("%d", &choice) != 1){
            while (getchar() != '\n');
            continue;
        }

        switch (choice){
            case 1:
            {
                char buffer[type->elementSize]; // временное место в памяти для записи значения

                printf("Enter value: ");

                if (type->set_value(buffer) == 1)
                    pushBack(&array, buffer);
                break;
            }

            case 2:
            {
                char buffer[type->elementSize];

                if (popBack(&array, buffer)){
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

                void *elem = getElement(&array, index);

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
                SORT_SIGNAL r = bubbleSort(&array);

                if (r == SORT_ERROR)
                    printf("Error\n");
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

                if (typeChoice == 1)
                    map(&result, &array, intMultiplyBy3);
                else
                    map(&result, &array, doubleMultiplyBy3);

                printArray(&result);
                freeDynamicArray(&result);
                break;
            }

            case 8:
            {
                DYNAMIC_ARRAY result;

                if (typeChoice == 1)
                    map(&result, &array, intSquare);
                else
                    map(&result, &array, doubleSquare);

                printArray(&result);
                freeDynamicArray(&result);
                break;
            }

            case 9:
            {
                DYNAMIC_ARRAY result;

                if (typeChoice == 1)
                    where(&result, &array, positiveInt);
                else
                    where(&result, &array, positiveDouble);

                printArray(&result);
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
                    char buffer[type->elementSize];
                    printf("Enter value: ");
                    if (type->set_value(buffer) == 1)
                        pushBack(&second, buffer);
                }
                DYNAMIC_ARRAY result;

                concat(&result, &array, &second);

                printArray(&result);

                freeDynamicArray(&result);
                freeDynamicArray(&second);
                break;
            }

            case 0:
                running = 0;
                break;

            default:
                printf("Wrong choice\n");
        }// switch

        printf("\n");
        printArray(&array);
    }// while
    freeDynamicArray(&array);
    return 0;
}