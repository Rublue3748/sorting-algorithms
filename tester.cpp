#include <iostream>
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <numeric>

#include "bubble_sort.hpp"
#include "selection_sort.hpp"
#include "gnome_sort.hpp"
#include "insertion_sort.hpp"
#include "shell_sort.hpp"
#include "quick_sort.hpp"
#include "heap_sort.hpp"

template <typename T>
using sorting_algorithm = std::function<void(T *, size_t, size_t)>;
template <typename T>
struct sort_entry
{
    sorting_algorithm<T> algorithm;
    std::string name;
};

std::chrono::milliseconds test_ints_perform_run(sorting_algorithm<int> algorithm, const std::vector<int> &data);
size_t test_ints_perform_run_n_times(sorting_algorithm<int> algorithm, const std::vector<int> &data, size_t count);

size_t test_ints_random_1_sec(sorting_algorithm<int> algorithm, std::string name);
template <size_t count>
size_t test_ints_random_fixed_size_N(sorting_algorithm<int> algorithm, std::string name);
template <size_t count>
size_t test_ints_ascending_fixed_size_N(sorting_algorithm<int> algorithm, std::string name);
template <size_t count>
size_t test_ints_descending_fixed_size_N(sorting_algorithm<int> algorithm, std::string name);
template <size_t count>
size_t test_ints_all_same_fixed_size_N(sorting_algorithm<int> algorithm, std::string name);

size_t test_ints_random_fixed_size_10k(sorting_algorithm<int> algorithm, std::string name) { return test_ints_random_fixed_size_N<10000>(algorithm, name); }
size_t test_ints_random_fixed_size_100k(sorting_algorithm<int> algorithm, std::string name) { return test_ints_random_fixed_size_N<100000>(algorithm, name); }
size_t test_ints_random_fixed_size_1M(sorting_algorithm<int> algorithm, std::string name) { return test_ints_random_fixed_size_N<1000000>(algorithm, name); }

size_t test_ints_ascending_fixed_size_10k(sorting_algorithm<int> algorithm, std::string name) { return test_ints_ascending_fixed_size_N<10000>(algorithm, name); }
size_t test_ints_ascending_fixed_size_100k(sorting_algorithm<int> algorithm, std::string name) { return test_ints_ascending_fixed_size_N<100000>(algorithm, name); }
size_t test_ints_ascending_fixed_size_1M(sorting_algorithm<int> algorithm, std::string name) { return test_ints_ascending_fixed_size_N<1000000>(algorithm, name); }

size_t test_ints_descending_fixed_size_10k(sorting_algorithm<int> algorithm, std::string name) { return test_ints_descending_fixed_size_N<10000>(algorithm, name); }
size_t test_ints_descending_fixed_size_100k(sorting_algorithm<int> algorithm, std::string name) { return test_ints_descending_fixed_size_N<100000>(algorithm, name); }
size_t test_ints_descending_fixed_size_1M(sorting_algorithm<int> algorithm, std::string name) { return test_ints_descending_fixed_size_N<1000000>(algorithm, name); }

size_t test_ints_all_same_fixed_size_10k(sorting_algorithm<int> algorithm, std::string name)
{
    return test_ints_all_same_fixed_size_N<10000>(algorithm, name);
}
size_t test_ints_all_same_fixed_size_100k(sorting_algorithm<int> algorithm, std::string name)
{
    return test_ints_all_same_fixed_size_N<100000>(algorithm, name);
}
size_t test_ints_all_same_fixed_size_1M(sorting_algorithm<int> algorithm, std::string name)
{
    return test_ints_all_same_fixed_size_N<1000000>(algorithm, name);
}

// Sorting algorithms: ShellSort (Variants), MergeSort, Quicksort, HeapSort, InPlaceMergeSort
// Done: BubbleSort, SelectionSort, GnomeSort, InsertionSort
// Also: Counting sort, Radix sort, and Bucket sort

int main()
{

    sort_entry<int> int_algorithms[] = {
        {Bubble_Sort<int>, "Bubble_Sort"},
        {Insertion_Sort<int>, "Insertion_Sort"},
        {Selection_Sort<int>, "Selection_Sort"},
        {Gnome_Sort<int>, "Gnome_Sort"},
        {Shell_Sort_Dumb<int>, "Shell_Sort_Dumb"},
        {Shell_Sort_Div_Powers_2<int>, "Shell_Sort_Div_Powers_2"},
        {Shell_Sort_Frank_Lazarus<int>, "Shell_Sort_Frank_Lazarus"},
        {Shell_Sort_Tokuda<int>, "Shell_Sort_Tokuda"},
        {Shell_Sort_Skean<int>, "Shell_Sort_Skean"},
        {Quick_Sort<int>, "Quick_Sort"},
        {Randomized_Quick_Sort<int>, "Randomized_Quick_Sort"}};

    constexpr size_t algorithm_count = 1;

    for (size_t i = 0; i < algorithm_count; i++)
    {
        test_ints_random_1_sec(int_algorithms[i].algorithm, int_algorithms[i].name);
    }

    bool continue_run[algorithm_count];
    for (size_t i = 0; i < algorithm_count; i++)
    {
        continue_run[i] = true;
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            size_t time_taken = test_ints_random_fixed_size_10k(int_algorithms[i].algorithm, int_algorithms[i].name);
            if (time_taken > 100)
            {
                continue_run[i] = false;
            }
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 10k random test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            size_t time_taken = test_ints_random_fixed_size_100k(int_algorithms[i].algorithm, int_algorithms[i].name);
            if (time_taken > 1000)
            {
                continue_run[i] = false;
            }
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 100k random test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            test_ints_random_fixed_size_1M(int_algorithms[i].algorithm, int_algorithms[i].name);
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 1M random test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        continue_run[i] = true;
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            size_t time_taken = test_ints_ascending_fixed_size_10k(int_algorithms[i].algorithm, int_algorithms[i].name);
            if (time_taken > 100)
            {
                continue_run[i] = false;
            }
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 10k ascending test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            size_t time_taken = test_ints_ascending_fixed_size_100k(int_algorithms[i].algorithm, int_algorithms[i].name);
            if (time_taken > 1000)
            {
                continue_run[i] = false;
            }
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 100k ascending test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            test_ints_ascending_fixed_size_1M(int_algorithms[i].algorithm, int_algorithms[i].name);
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 1M ascending test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        continue_run[i] = true;
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            size_t time_taken = test_ints_descending_fixed_size_10k(int_algorithms[i].algorithm, int_algorithms[i].name);
            if (time_taken > 100)
            {
                continue_run[i] = false;
            }
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 10k descending test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            size_t time_taken = test_ints_descending_fixed_size_100k(int_algorithms[i].algorithm, int_algorithms[i].name);
            if (time_taken > 1000)
            {
                continue_run[i] = false;
            }
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 100k descending test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            test_ints_descending_fixed_size_1M(int_algorithms[i].algorithm, int_algorithms[i].name);
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 1M descending test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        continue_run[i] = true;
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            size_t time_taken = test_ints_all_same_fixed_size_10k(int_algorithms[i].algorithm, int_algorithms[i].name);
            if (time_taken > 100)
            {
                continue_run[i] = false;
            }
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 10k all same test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            size_t time_taken = test_ints_all_same_fixed_size_100k(int_algorithms[i].algorithm, int_algorithms[i].name);
            if (time_taken > 1000)
            {
                continue_run[i] = false;
            }
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 100k all same test." << std::endl;
        }
    }
    for (size_t i = 0; i < algorithm_count; i++)
    {
        if (continue_run[i])
        {
            test_ints_all_same_fixed_size_1M(int_algorithms[i].algorithm, int_algorithms[i].name);
        }
        else
        {
            std::cout << int_algorithms[i].name << ": Skipping 1M all same test." << std::endl;
        }
    }

    return 0;
}

size_t test_ints_random_1_sec(sorting_algorithm<int> algorithm, std::string name)
{
    std::minstd_rand rng;
    std::minstd_rand shuffler;
    std::uniform_int_distribution<> int_distr(0, INT32_MAX); // TODO: Check if int distribution is necessary
    std::chrono::milliseconds duration(0);
    size_t n = 0;
    std::vector<int> current_data;
    // int64_t previous_time = 0;
    size_t increment = 50;

    std::stringstream directory;
    directory << "./output/" << name;
    std::filesystem::create_directories(directory.str());

    std::ofstream out;
    std::stringstream filename;
    filename << directory.str() << "/random_1_int.csv";
    out.open(filename.str());
    if (out.fail())
    {
        std::cerr << "File output failure" << std::endl;
        return 0;
    }
    do
    {
        if (n % (increment * 10) == 0)
        {
            std::cout << n << std::endl;
        }
        if (n == 10000)
        {
            increment = 500;
        }
        if (n == 1000000)
        {
            increment = 5000;
        }
        if (n == 10000000)
        {
            increment = 50000;
        }
        n += increment;
        for (size_t i = 0; i < increment; i++)
        {
            current_data.push_back(int_distr(rng));
        }
        std::shuffle(current_data.begin(), current_data.end(), shuffler);
        auto start = std::chrono::high_resolution_clock::now();

        algorithm(current_data.data(), 0, n - 1);

        auto end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (!std::is_sorted(current_data.begin(), current_data.end()))
        {
            std::cout << name << " - Sorting error. Aborting" << std::endl;
            std::cout << "Array: ";
            for (auto iter = current_data.begin(); iter != current_data.end(); iter++)
            {
                std::cout << *iter << ", ";
            }
            std::cout << std::endl;
            return 0;
        }
        out << n << "," << duration.count() << "\n";
    } while (!(duration.count() > 1000 && duration.count() < 1100) && n != SIZE_MAX);
    out.close();
    std::cout << name << " - " << "Max n: " << n << std::endl;
    return n;
}

template <size_t count>
size_t test_ints_random_fixed_size_N(sorting_algorithm<int> algorithm, std::string name)
{
    std::array<int, count> original;
    std::minstd_rand rng;
    // std::minstd_rand shuffler;
    std::uniform_int_distribution<> int_distr(0, INT32_MAX); // TODO: Check if int distribution is necessary
    std::generate_n(original.begin(), count, rng);

    constexpr size_t iterations = 10;

    std::chrono::milliseconds durations[iterations];

    for (size_t i = 0; i < iterations; i++)
    {
        std::array<int, count> unsorted(original);
        auto start = std::chrono::high_resolution_clock::now();
        algorithm(unsorted.data(), 0, count - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (duration.count() < 0)
        {
            std::cout << "Rejecting run. Negative time." << std::endl;
            i--;
            continue;
        }
        durations[i] = duration;
        if (!std::is_sorted(unsorted.begin(), unsorted.end()))
        {
            std::cout << name << " - Sorting error. Aborting" << std::endl;
        }
    }
    std::chrono::milliseconds total = std::accumulate(begin(durations), end(durations), std::chrono::milliseconds(0));
    size_t average_time = total.count() / iterations;
    std::cout << count << " random test - " << name << ": " << average_time << " ms." << std::endl;
    return average_time;
}

template <size_t count>
size_t test_ints_ascending_fixed_size_N(sorting_algorithm<int> algorithm, std::string name)
{
    std::array<int, count> original;

    for (size_t i = 0; i < count; i++)
    {
        original[i] = i;
    }

    constexpr size_t iterations = 10;

    std::chrono::milliseconds durations[iterations];

    for (size_t i = 0; i < iterations; i++)
    {
        std::array<int, count> unsorted(original);
        auto start = std::chrono::high_resolution_clock::now();
        algorithm(unsorted.data(), 0, count - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (duration.count() < 0)
        {
            std::cout << "Rejecting run. Negative time." << std::endl;
            i--;
            continue;
        }
        durations[i] = duration;
        if (!std::is_sorted(unsorted.begin(), unsorted.end()))
        {
            std::cout << name << " - Sorting error. Aborting" << std::endl;
        }
    }
    std::chrono::milliseconds total = std::accumulate(begin(durations), end(durations), std::chrono::milliseconds(0));
    size_t average_time = total.count() / iterations;
    std::cout << count << " ascending test - " << name << ": " << average_time << " ms." << std::endl;
    return average_time;
}

template <size_t count>
size_t test_ints_descending_fixed_size_N(sorting_algorithm<int> algorithm, std::string name)
{
    std::array<int, count> original;

    for (size_t i = 0; i < count; i++)
    {
        original[i] = count - i - 1;
    }

    constexpr size_t iterations = 10;

    std::chrono::milliseconds durations[iterations];

    for (size_t i = 0; i < iterations; i++)
    {
        std::array<int, count> unsorted(original);
        auto start = std::chrono::high_resolution_clock::now();
        algorithm(unsorted.data(), 0, count - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (duration.count() < 0)
        {
            std::cout << "Rejecting run. Negative time." << std::endl;
            i--;
            continue;
        }
        durations[i] = duration;
        if (!std::is_sorted(unsorted.begin(), unsorted.end()))
        {
            std::cout << name << " - Sorting error. Aborting" << std::endl;
        }
    }
    std::chrono::milliseconds total = std::accumulate(begin(durations), end(durations), std::chrono::milliseconds(0));
    size_t average_time = total.count() / iterations;
    std::cout << count << " descending test - " << name << ": " << average_time << " ms." << std::endl;
    return average_time;
}

template <size_t count>
size_t test_ints_all_same_fixed_size_N(sorting_algorithm<int> algorithm, std::string name)
{
    std::array<int, count> original;

    for (size_t i = 0; i < count; i++)
    {
        original[i] = 10;
    }

    constexpr size_t iterations = 10;

    std::chrono::milliseconds durations[iterations];

    for (size_t i = 0; i < iterations; i++)
    {
        std::array<int, count> unsorted(original);
        auto start = std::chrono::high_resolution_clock::now();
        algorithm(unsorted.data(), 0, count - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (duration.count() < 0)
        {
            std::cout << "Rejecting run. Negative time." << std::endl;
            i--;
            continue;
        }
        durations[i] = duration;
        if (!std::is_sorted(unsorted.begin(), unsorted.end()))
        {
            std::cout << name << " - Sorting error. Aborting" << std::endl;
        }
    }
    std::chrono::milliseconds total = std::accumulate(begin(durations), end(durations), std::chrono::milliseconds(0));
    size_t average_time = total.count() / iterations;
    std::cout << count << " all similar test - " << name << ": " << average_time << " ms." << std::endl;
    return average_time;
}

size_t test_ints_perform_run_n_times(sorting_algorithm<int> algorithm, const std::vector<int> &data, size_t count)
{
    std::vector<std::chrono::milliseconds> times;
    times.resize(count);
    for (size_t i = 0; i < count; i++)
    {
        times[i] = test_ints_perform_run(algorithm, data);
        if (times[i].count() < 0)
        {
            std::cout << "Rejecting run. Negative time." << std::endl;
            i--;
            continue;
        }
    }
    bool recheck = true;
    while (recheck)
    {
        recheck = false;
        auto average = (std::accumulate(times.begin(), times.end(), std::chrono::milliseconds(0)) / static_cast<int64_t>(count)).count();
        for (auto &time : times)
        {
            double percent_error = (std::abs(time.count() - average) / average) * 100;
        }
    }
}

std::chrono::milliseconds test_ints_perform_run(sorting_algorithm<int> algorithm, const std::vector<int> &data)
{
    std::vector<int> data_copy(data);
    auto start = std::chrono::high_resolution_clock::now();
    algorithm(data_copy.data(), 0, data_copy.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}