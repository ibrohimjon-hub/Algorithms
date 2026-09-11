#include <cassert>
#include "array.h"

int main()
{
    Array* arr = array_create(10);

    assert(array_size(arr) == 10);

    for (int i = 0; i < 10; ++i)
        array_set(arr, i, i * 2);

    for (int i = 0; i < 10; ++i)
        assert(array_get(arr, i) == i * 2);

    array_delete(arr);

    return 0;
}