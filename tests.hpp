#pragma once
#include <functional>
#include <chrono>
#include <string>

template <typename T>
using sorting_algorithm = std::function<void(T *, size_t, size_t)>;
template <typename T>
struct sort_entry
{
    sorting_algorithm<T> algorithm;
    std::string name;
};
using int_algorithm = sorting_algorithm<int>;
using int_sorting_entry = sort_entry<int>;

/**
 * @brief Performs a single run of the algorithm on the given data
 * @param algorithm
 * @param data
 * @return number of milliseconds to complete
 */
std::chrono::milliseconds test_ints_perform_run(sorting_algorithm<int> algorithm, const std::vector<int> &data);
/**
 * @brief Performs [count] runs of the algorithm on the data
 * @param algorithm
 * @param data
 * @param count
 * @return Average number of milliseconds to complete
 */
std::chrono::milliseconds test_ints_perform_run_n_times(sorting_algorithm<int> algorithm, const std::vector<int> &data, size_t count, double tolerance = 5);

// TODO: Fix this to use above and possibly time prediction
size_t test_ints_random_1_sec(sorting_algorithm<int> algorithm, std::string name);

// TODO: Replace ALL OF THIS

/**
 * @brief
 * @param algorithm
 * @param n
 * @param test_count
 * @param tolerance
 * @return
 */
std::chrono::milliseconds test_ints_random_fixed_size(sorting_algorithm<int> algorithm, size_t n, size_t test_count = 10, double tolerance = 5);
std::chrono::milliseconds test_ints_ascending_fixed_size(sorting_algorithm<int> algorithm, size_t n, size_t test_count = 10, double tolerance = 5);
std::chrono::milliseconds test_ints_descending_fixed_size(sorting_algorithm<int> algorithm, size_t n, size_t test_count = 10, double tolerance = 5);
std::chrono::milliseconds test_ints_all_same_fixed_size(sorting_algorithm<int> algorithm, size_t n, size_t test_count = 10, double tolerance = 5);
std::chrono::milliseconds test_ints_all_unique_fixed_size(sorting_algorithm<int> algorithm, size_t n, size_t test_count = 10, double tolerance = 5);