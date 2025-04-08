#pragma once

#include <utility>
#include <functional>
#include <cmath>
#include <cstddef>
#include <iostream>

template <typename T>
void _k_sort(T *data, size_t front, size_t back, size_t k)
{
    for (size_t i = front; i < front + k && i <= back; i++)
    {
        for (size_t j = i + k; j <= back; j += k)
        {
            size_t h = j;
            T old = data[h];
            while (h > i && h <= back && old < data[h - k])
            {
                data[h] = data[h - k];
                h -= k;
            }
            data[h] = old;
        }
    }
}

template <typename T>
void _Shell_Sort_Intr(T *data, size_t front, size_t back, std::function<size_t(size_t, size_t)> divisor_function)
{
    size_t step = 1;
    size_t n = back - front;
    size_t divisor = divisor_function(n, step);
    while (divisor != 0)
    {
        _k_sort(data, front, back, divisor);
        if (divisor == 1)
        {
            break;
        }
        step++;
        divisor = divisor_function(n, step);
    }
}

template <typename T>
void Shell_Sort_Dumb(T *data, size_t front, size_t back)
{
    _Shell_Sort_Intr(data, front, back,
                     [](size_t n, size_t step)
                     { return n - step; });
}

template <typename T>
void Shell_Sort_Div_Powers_2(T *data, size_t front, size_t back)
{
    _Shell_Sort_Intr(data, front, back,
                     [](size_t n, size_t step)
                     {
                         return n / std::pow(2, step);
                     });
}

template <typename T>
void Shell_Sort_Frank_Lazarus(T *data, size_t front, size_t back)
{
    _Shell_Sort_Intr(data, front, back,
                     [](size_t n, size_t step)
                     {
                         return 2 * (n / (2 << (step - 1))) + 1;
                     });
}

constexpr size_t _Tokuda_Gen_Function(size_t step)
{
    if (step <= 1)
    {
        return 1;
    }
    else
    {
        return std::ceil(2.25 * _Tokuda_Gen_Function(step - 1));
    }
}

size_t _Tokuda_Function(size_t n, size_t step)
{
    size_t i = 1;
    while (_Tokuda_Gen_Function(i) < n)
    {
        i++;
    }
    if (i < step)
    {
        return _Tokuda_Gen_Function(1);
    }
    else
    {
        return _Tokuda_Gen_Function(i - step);
    }
}

template <typename T>
void Shell_Sort_Tokuda(T *data, size_t front, size_t back)
{
    _Shell_Sort_Intr(data, front, back, _Tokuda_Function);
}

size_t _Skean_Function(size_t n, size_t step)
{
    int64_t max_val = std::floor(2.2449 * (std::log2(n / 4.0816) / std::log2(8.5714))) + 2;
    int64_t k = max_val - step;

    return std::floor(4.0816 * std::pow(8.5714, (k - 2) / 2.2449));
}

template <typename T>
void Shell_Sort_Skean(T *data, size_t front, size_t back)
{
    _Shell_Sort_Intr(data, front, back, _Skean_Function);
}