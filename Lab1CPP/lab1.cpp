#include <iostream>
#include <fstream>
#include "array.h"

Array* array_create_and_read(std::ifstream& input)
{
    int n;
    input >> n;

    Array* arr = array_create(n);

    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }

    return arr;
}

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;

    std::ifstream input(argv[1]);

    if (!input)
        return 1;

    Array* arr = array_create_and_read(input);

    Array* positive = array_create(array_size(arr));
    Array* negative = array_create(array_size(arr));

    size_t positive_size = 0;
    size_t negative_size = 0;

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int x = array_get(arr, i);

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
        std::cout << array_get(positive, i) << ' ';

    std::cout << '\n';

    for (size_t i = 0; i < negative_size; ++i)
        std::cout << array_get(negative, i) << ' ';

    std::cout << '\n';

    array_delete(positive);
    array_delete(negative);
    array_delete(arr);

    return 0;
}