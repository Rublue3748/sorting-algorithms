#pragma once

#include <utility>
#include <cstddef>
#include <cmath>

size_t _Heap_Parent(size_t node)
{
    return node / 2;
}
size_t _Heap_Left(size_t node)
{
    return node * 2;
}
size_t _Heap_Right(size_t node)
{
    return node * 2 + 1;
}

template <typename T>
void _Heap_Max_Heapify(T *data, size_t node, size_t back)
{
    if (node <= back)
    {
        size_t max_index = node;

        size_t left_node = _Heap_Left(node);
        size_t right_node = _Heap_Right(node);

        if (left_node <= back && data[left_node] > data[max_index])
        {
            max_index = left_node;
        }
        if (right_node <= back && data[right_node] > data[max_index])
        {
            max_index = right_node;
        }
        if (max_index != node)
        {
            std::swap(data[max_index], data[node]);
            _Heap_Max_Heapify(data, max_index, back);
        }
    }
};

template <typename T>
void _Heap_Create_Max_Heap(T *data, size_t front, size_t back)
{
    for (size_t i = back; i >= front && i <= back; i--)
    {
        _Heap_Max_Heapify(data, i, back);
    }
    // size_t level = 0;
    // for (size_t i = front; i < back; i++)
    // {
    //     std::cout << data[i] << " ";
    //     if ((i - front) % (1 << level) == 0)
    //     {
    //         std::cout << std::endl;
    //         level++;
    //     }
    // }
    // std::cout << std::endl;
    // exit(1);
}

template <typename T>
void Heap_Sort(T *data, size_t front, size_t back)
{
    _Heap_Create_Max_Heap(data, front, back);
    for (size_t i = back; i != front; i--)
    {
        std::swap(data[front], data[i]);
        _Heap_Max_Heapify(data, front, i - 1);
    }
}