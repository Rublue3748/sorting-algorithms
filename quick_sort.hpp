#pragma once

#include <utility>
#include <cstddef>
#include <iostream>
#include <random>

template <typename T>
size_t _Partition(T *data, size_t front, size_t back)
{
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
size_t _Randomized_Partition(T *data, size_t front, size_t back)
{
    std::minstd_rand gen;
    std::uniform_int_distribution dist(front, back);
    std::swap(data[back], data[dist(gen)]);
    return _Partition(data, front, back);
}

template <typename T>
void Quick_Sort(T *data, size_t front, size_t back)
{
    if (front - back > 1)
    {
        size_t q = _Partition(data, front, back);
        // std::cout << front << " " << q << " " << back << std::endl;
        Quick_Sort(data, front, q - 1);
        Quick_Sort(data, q + 1, back);
    }
}

template <typename T>
void Randomized_Quick_Sort(T *data, size_t front, size_t back)
{
    if (front - back > 1)
    {
        size_t q = _Randomized_Partition(data, front, back);
        // std::cout << front << " " << q << " " << back << std::endl;
        Randomized_Quick_Sort(data, front, q - 1);
        Randomized_Quick_Sort(data, q + 1, back);
    }
}