#pragma once

#include <utility>
#include <cstddef>

template <typename T>
void Insertion_Sort(T *data, size_t front, size_t back)
{
    for (size_t i = front + 1; i <= back; i++)
    {
        size_t j = i;
        T old_data = data[j];
        while (j != front && old_data < data[j - 1])
        {
            data[j] = data[j - 1];
            j--;
        }
        data[j] = old_data;
    }
}