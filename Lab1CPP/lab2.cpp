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

    int count[1001] = {};

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int x = array_get(arr, i);
        ++count[x];
    }

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int x = array_get(arr, i);

        if (count[x] == 1)
            std::cout << x << ' ';
    }

    std::cout << '\n';

    array_delete(arr);

    return 0;
}