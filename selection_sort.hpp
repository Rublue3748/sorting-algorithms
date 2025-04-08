#pragma once
#include <utility>
#include <cstddef>

template <typename T>
void Selection_Sort(T *data, size_t front, size_t back)
{
    for (size_t start = front; start < back; start++)
    {
        size_t min_index = start;
        for (size_t i = start + 1; i <= back; i++)
        {
            if (data[i] < data[min_index])
            {
                min_index = i;
            }
        }
        std::swap(data[start], data[min_index]);
    }
}