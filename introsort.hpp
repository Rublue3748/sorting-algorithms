#pragma once
#include <utility>
#include <random>
#include <cstddef>
#include <cmath>
#include "heap_sort.hpp"
#include "insertion_sort.hpp"

namespace Intro_Sort
{
    std::minstd_rand gen;
    template <typename T>
    size_t _intr_Randomized_Partion(T *data, size_t front, size_t back)
    {
        std::uniform_int_distribution dist(front, back);
        std::swap(data[back], data[dist(gen)]);
        T pivot = data[back];
        size_t q = front - 1;
        for (size_t i = front; i < back; i++)
        {
            if (data[i] <= pivot)
            {
                q++;
                std::swap(data[q], data[i]);
            }
        }
        q++;
        std::swap(data[q], data[back]);

        return q;
    }

    template <typename T>
    void _intr_Intro_Sort(T *data, size_t front, size_t back, size_t depth, size_t max_depth)
    {
        if (front - back > 1)
        {
            if (back - front < 16)
            {
                Insertion_Sort::Insertion_Sort(data, front, back);
                return;
            }
            if (depth > max_depth)
            {
                Heap_Sort::Heap_Sort(data, front, back);
                return;
            }
            size_t q = _intr_Randomized_Partion(data, front, back);
            _intr_Intro_Sort(data, front, q - 1, depth + 1, max_depth);
            _intr_Intro_Sort(data, q + 1, back, depth + 1, max_depth);
        }
    }
    template <typename T>
    void Intro_Sort(T *data, size_t front, size_t back)
    {
        // 3 * depth found to be the best
        size_t max = static_cast<size_t>(3.0 * std::log2(back - front));
        _intr_Intro_Sort(data, front, back, 0, max);
    }
}