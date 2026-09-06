#include <stdlib.h>
#include "array.h"

typedef struct Array {
    size_t size;
    Data *data;
    FFree *free_function;
} Array;

Array *array_create(size_t size, FFree f)
{
    Array *arr = malloc(sizeof(Array));

    if (arr == NULL)
        return NULL;

    arr->size = size;
    arr->free_function = f;
    arr->data = calloc(size, sizeof(Data));

    if (arr->data == NULL)
    {
        free(arr);
        return NULL;
    }

    return arr;
}

void array_delete(Array *arr)
{
    if (arr == NULL)
        return;

    if (arr->free_function != NULL)
    {
        for (size_t i = 0; i < arr->size; ++i)
        {
            if (arr->data[i] != 0)
                arr->free_function((void*)arr->data[i]);
        }
    }

    free(arr->data);
    free(arr);
}

Data array_get(const Array *arr, size_t index)
{
    return arr->data[index];
}

void array_set(Array *arr, size_t index, Data value)
{
    if (arr->free_function != NULL && arr->data[index] != 0)
        arr->free_function((void*)arr->data[index]);

    arr->data[index] = value;
}

size_t array_size(const Array *arr)
{
    return arr->size;
}
