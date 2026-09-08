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

    int count[1001] = {0};

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int x = (int)array_get(arr, i);
        ++count[x];
    }

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int x = (int)array_get(arr, i);

        if (count[x] == 1)
            printf("%d ", x);
    }

    printf("\n");

    array_delete(arr);
    fclose(input);

    return 0;
}