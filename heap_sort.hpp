#pragma once

#include <utility>
#include <cstddef>
#include <cmath>

namespace Heap_Sort
{

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
    }

    template <typename T>
    void Heap_Sort(T *data, size_t front, size_t back)
    {
        T *data_fixed = data + front;
        size_t front_front = front - front;
        size_t back_front = back - front;
        _Heap_Create_Max_Heap(data_fixed, front_front, back_front);
        for (size_t i = back_front; i != front_front; i--)
        {
            std::swap(data_fixed[front_front], data_fixed[i]);
            _Heap_Max_Heapify(data_fixed, front_front, i - 1);
        }
    }
}