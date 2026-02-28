#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"
#include "operations.h"
#include "intType.h"
#include "doubleType.h"

void printIntArray(DYNAMIC_ARRAY *arr)
{
    for (size_t i = 0; i < arr->size; i++)
        printf("%d ", *(int*)getElement(arr, i));
    printf("\n");
}

void printDoubleArray(DYNAMIC_ARRAY *arr)
{
    for (size_t i = 0; i < arr->size; i++)
        printf("%.2f ", *(double*)getElement(arr, i));
    printf("\n");
}

void intMultiplyBy3(const void *src, void *dst)
{
    *(int*)dst = (*(int*)src) * 3;
}
void doubleMultiplyBy3(const void *src, void *dst)
{
    *(double*)dst = (*(double*)src) * 3;
}

void intSquare(const void *src, void *dst)
{
    int x = *(int*)src;
    *(int*)dst = x * x;
}
void doubleSquare(const void *src, void *dst)
{
    double x = *(double*)src;
    *(double*)dst = x * x;
}

int positiveInt(const void *e)
{
    return *(int*)e > 0;
}

int positiveDouble(const void *e)
{
    return *(double*)e > 0.0;
}
int main()
{
    int typeChoice;

    printf("Выберите тип массива:\n");
    printf("1 - int\n");
    printf("2 - double\n");
    scanf("%d", &typeChoice);
    if (typeChoice != 1 && typeChoice != 2)
    {
        printf("Wrong type\n");
        return 1;
    }

    const TYPE_INFO *type;
    if (typeChoice == 1)
        type = getIntType();
    else
        type = getDoubleType();

    DYNAMIC_ARRAY *array =
        createDynamicArray(type, 2);// без * и заменить create на init
    if (!array) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int running = 1;

    while (running)
    {
        printf("\n========== MENU ==========\n");
        printf("1. Use pushBack\n");
        printf("2. Use popBack\n");
        printf("3. Find element\n"); // по индексу
        printf("4. Sort\n");
        printf("5. Show size\n");
        printf("6. Show capacity\n");
        printf("7. Map: multiply by 3\n");
        printf("8. Map: square\n");
        printf("9. Where: positive numbers\n");
        printf("10. Concatination\n");
        printf("0. Exit\n");
        printf("==========================\n");
        printf("\nChose button: ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (typeChoice == 1)
                {
                    int value;
                    printf("Введите int: ");
                    scanf("%d", &value);
                    pushBack(array, &value);
                }
                else
                {
                    double value;
                    printf("Введите double: ");
                    scanf("%lf", &value);
                    pushBack(array, &value);
                }
                break;

            case 2:
                if (typeChoice == 1)
                {
                    int save_data;
                    if (popBack(array, &save_data))
                        printf("Removed: %d\n", save_data);
                    else
                        printf("Array is empty\n");
                }
                else
                {
                    double save_data;
                    if (popBack(array, &save_data))
                        printf("Removed: %.2f\n", save_data);
                    else
                        printf("Array is empty\n");
                }
                break;

            case 3:
            {
                size_t index;
                printf("Enter index: ");
                scanf("%zu", &index);

                void *elem = getElement(array, index);

                if (!elem)
                    printf("Wrong index\n");
                else if (typeChoice == 1)
                    printf("%d\n", *(int*)elem);
                else
                    printf("%.2f\n", *(double*)elem);

                break;
            }

            case 4: {
                int changed = bubbleSort(array);
                if (!changed)
                    printf("Array was already sorted\n");
                else
                    printf("Sorted complete\n");
                break;
            }
            case 5:
                printf("Size = %zu\n", array->size);
                break;

            case 6:
                printf("Capacity = %zu\n", array->capacity);
                break;

            case 7:
                if (typeChoice == 1){
                    DYNAMIC_ARRAY *map_array = map(array, intMultiplyBy3);
                    printIntArray(map_array);
                    deleteDynamicArray(map_array);
                }
                else {
                    DYNAMIC_ARRAY *map_array = map(array, doubleMultiplyBy3);
                    printDoubleArray(map_array);
                    deleteDynamicArray(map_array);
                }
                break;

            case 8:
                if (typeChoice == 1){
                    DYNAMIC_ARRAY *map_array = map(array, intSquare);
                    printIntArray(map_array);
                    deleteDynamicArray(map_array);
                }
                else {
                    DYNAMIC_ARRAY *map_array = map(array, doubleSquare);
                    printDoubleArray(map_array);
                    deleteDynamicArray(map_array);
                }
                break;

            case 9:
                if (typeChoice == 1)
                {
                    DYNAMIC_ARRAY *where_array = where(array, positiveInt);
                    printIntArray(where_array);
                    deleteDynamicArray(where_array);
                }
                else {
                    DYNAMIC_ARRAY *where_array = where(array, positiveDouble);
                    printDoubleArray(where_array);
                    deleteDynamicArray(where_array);
                }
                break;

            case 10:
            {
                printf("Creating second array...\n");

                DYNAMIC_ARRAY *second_array =
                    createDynamicArray(type, 2);

                if (!second_array)
                {
                    printf("Memory allocation failed\n");
                    break;
                }

                int count;
                printf("How many elements in second array? ");
                scanf("%d", &count);

                for (int i = 0; i < count; i++)
                {
                    if (typeChoice == 1)
                    {
                        int v;
                        printf("Enter int: ");
                        scanf("%d", &v);
                        pushBack(second_array, &v);
                    }
                    else
                    {
                        double v;
                        printf("Enter double: ");
                        scanf("%lf", &v);
                        pushBack(second_array, &v);
                    }
                }

                DYNAMIC_ARRAY *result = concat(array, second_array);

                if (!result)
                {
                    printf("Concat failed (type mismatch?)\n");
                }
                else
                {
                    printf("Result of concatenation:\n");

                    if (typeChoice == 1)
                        printIntArray(result);
                    else
                        printDoubleArray(result);

                    deleteDynamicArray(result);
                }

                deleteDynamicArray(second_array);
                break;
            }
            case 0:
                running = 0;
                break;

            default:
                printf("Wrong chose\n");
        } // close cases
        if (typeChoice == 1) {
            printf("\n");
            printIntArray(array);
        }
        else {
            printf("\n");
            printDoubleArray(array);
        }
    } // while
    deleteDynamicArray(array);
    return 0;
}// main
// долбавить проверку на ввод(смог раобрать строку на вход и из нее получил корректный вывод)