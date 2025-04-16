#pragma once
#include <utility>
#include <cstddef>

namespace Bubble_Sort
{
    template <typename T>
    void Bubble_Sort(T *data, size_t front, size_t back)
    {
        for (size_t start = front; start <= back; start++)
        {
            for (size_t i = back; i > front; i--)
            {
                if (!(data[i - 1] < data[i]))
                {
                    std::swap(data[i - 1], data[i]);
                }
            }
        }
    };
}