#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);

    Array *arr = array_create(n, NULL);

    for (int i = 0; i < n; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }

    return arr;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
        return 1;

    Array *arr = array_create_and_read(input);

    Array *positive = array_create(array_size(arr), NULL);
    Array *negative = array_create(array_size(arr), NULL);

    size_t positive_size = 0;
    size_t negative_size = 0;

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int x = (int)array_get(arr, i);

        if (x > 0)
        {
            array_set(positive, positive_size, x);
            ++positive_size;
        }
        else if (x < 0)
        {
            array_set(negative, negative_size, x);
            ++negative_size;
        }
    }

    for (size_t i = 0; i < positive_size; ++i)
        printf("%d ", (int)array_get(positive, i));

    printf("\n");

    for (size_t i = 0; i < negative_size; ++i)
        printf("%d ", (int)array_get(negative, i));

    printf("\n");

    array_delete(positive);
    array_delete(negative);
    array_delete(arr);

    fclose(input);

    return 0;
}