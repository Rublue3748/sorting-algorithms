#include <iostream>

#include "bubble_sort.hpp"
#include "selection_sort.hpp"
#include "gnome_sort.hpp"
#include "insertion_sort.hpp"
#include "shell_sort.hpp"
#include "quick_sort.hpp"
#include "heap_sort.hpp"
#include "introsort.hpp"
#include "tests.hpp"

// Sorting algorithms:  Cocktail Shaker Sort, BMIS/CBIS?, MergeSort, Quicksort variants (Median of three, with equal value correction), InPlaceMergeSort
// Done: BubbleSort, SelectionSort, GnomeSort, InsertionSort, ShellSort (Variants), Quicksort (+Randomized), HeapSort
// Also: Counting sort, Radix sort, and Bucket sort

void set_all_running(std::vector<bool> &arr, bool value) { std::fill(arr.begin(), arr.end(), value); }
bool should_continue_running(const std::vector<bool> &arr)
{
    return std::any_of(arr.begin(), arr.end(), [](const bool &val)
                       { return val; });
}

void test_suite_int_random(const std::vector<int_sorting_entry> &);

int main()
{

    std::vector<int_sorting_entry> int_algorithms = {
        {Bubble_Sort::Bubble_Sort<int>, "Bubble_Sort"},
        {Insertion_Sort::Insertion_Sort<int>, "Insertion_Sort"},
        {Selection_Sort::Selection_Sort<int>, "Selection_Sort"},
        {Gnome_Sort::Gnome_Sort<int>, "Gnome_Sort"},
        {Shell_Sort::Shell_Sort_Dumb<int>, "Shell_Sort_Dumb"},
        {Shell_Sort::Shell_Sort_Div_Powers_2<int>, "Shell_Sort_Div_Powers_2"},
        {Shell_Sort::Shell_Sort_Frank_Lazarus<int>, "Shell_Sort_Frank_Lazarus"},
        {Shell_Sort::Shell_Sort_Tokuda<int>, "Shell_Sort_Tokuda"},
        {Shell_Sort::Shell_Sort_Skean<int>, "Shell_Sort_Skean"},
        {Heap_Sort::Heap_Sort<int>, "Heap_Sort"},
        {Quick_Sort::Quick_Sort<int>, "Quick_Sort"},
        {Quick_Sort::Randomized_Quick_Sort<int>, "Randomized_Quick_Sort"},
        {Intro_Sort::Intro_Sort<int>, "Intro_Sort"}};

    // Fixed random array test
    test_suite_int_random(int_algorithms);

    // for (size_t i = 0; i < int_algorithms.size(); i++)
    // {
    //     test_ints_random_1_sec(int_algorithms[i].algorithm, int_algorithms[i].name);
    // }

    return 0;
}

void test_suite_int_random(const std::vector<int_sorting_entry> &algorithms)
{
    std::vector<bool> continue_run;
    continue_run.resize(algorithms.size());
    set_all_running(continue_run, true);
    size_t current_test_size = 2000;
    while (should_continue_running(continue_run))
    {
        for (size_t i = 0; i < algorithms.size(); i++)
        {
            const int_sorting_entry &algorithm = algorithms.at(i);
            std::cout << algorithm.name << ": ";
            if (continue_run[i])
            {
                auto duration = test_ints_random_fixed_size(algorithm.algorithm, current_test_size);
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
}