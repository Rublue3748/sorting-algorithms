#pragma once
#include <utility>
#include <cstddef>

namespace Gnome_Sort
{
    template <typename T>
    void Gnome_Sort(T *data, size_t front, size_t back)
    {
        size_t i = front;
        while (i < back)
        {
            if (data[i + 1] < data[i])
            {
                std::swap(data[i], data[i + 1]);
                if (i > front)
                {
                    i--;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                i++;
            }
        }
    }
}