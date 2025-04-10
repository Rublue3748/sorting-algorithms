#include <iostream>

#include "bubble_sort.hpp"
#include "selection_sort.hpp"
#include "gnome_sort.hpp"
#include "insertion_sort.hpp"
#include "shell_sort.hpp"
#include "quick_sort.hpp"
#include "heap_sort.hpp"

#include "tests.hpp"

// Sorting algorithms:  MergeSort, Quicksort variants (Median of three, with equal value correction), InPlaceMergeSort
// Done: BubbleSort, SelectionSort, GnomeSort, InsertionSort, ShellSort (Variants), Quicksort (+Randomized), HeapSort
// Also: Counting sort, Radix sort, and Bucket sort

template <size_t T>
void set_all_running(std::array<bool, T> &arr, bool value) { std::fill(arr.begin(), arr.end(), value); }
template <size_t T>
bool should_continue_running(std::array<bool, T> &arr)
{
    return std::any_of(arr.begin(), arr.end(), [](const bool &val)
                       { return val; });
}

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

    constexpr size_t algorithm_count = 11;

    // Fixed random array test
    std::array<bool, algorithm_count> continue_run;
    set_all_running(continue_run, true);
    size_t current_test_size = 10000;
    while (should_continue_running(continue_run))
    {
        for (size_t i = 0; i < algorithm_count; i++)
        {
            std::cout << int_algorithms[i].name << ": ";
            if (continue_run[i])
            {
                auto duration = test_ints_random_fixed_size(int_algorithms[i].algorithm, current_test_size);
                std::cout << "took " << duration.count() << "ms to perform " << current_test_size << " random test" << std::endl;
                if (duration.count() > 200)
                {
                    continue_run[i] = false;
                }
            }
            else
            {
                std::cout << "skipping " << current_test_size << " random test" << std::endl;
            }
        }
        current_test_size *= 2;
    }

    for (size_t i = 0; i < algorithm_count; i++)
    {
        test_ints_random_1_sec(int_algorithms[i].algorithm, int_algorithms[i].name);
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
            // std::cout << n << std::endl;
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
        duration = test_ints_perform_run_n_times(algorithm, current_data, 10);
        out << n << "," << duration.count() << "\n";
    } while (!(duration.count() > 1000 && duration.count() < 1100) && n != SIZE_MAX);
    out.close();
    std::cout << name << " - " << "Max n: " << n << std::endl;
    return n;
}