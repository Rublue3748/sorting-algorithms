#include "tests.hpp"
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <random>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>

std::chrono::milliseconds test_ints_perform_run(sorting_algorithm<int> algorithm, const std::vector<int> &data)
{
    std::vector<int> data_copy(data);
    auto start = std::chrono::high_resolution_clock::now();
    algorithm(data_copy.data(), 0, data_copy.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    if (!std::is_sorted(data_copy.begin(), data_copy.end()))
    {
        std::cerr << "\n";
        size_t i = 0;
        for (int val : data_copy)
        {
            std::cerr << i << ": " << val << " ";
            i++;
        }
        std::cerr << "\n";
        auto iter = std::is_sorted_until(data_copy.begin(), data_copy.end());
        std::cerr << "Is sorted until: " << *(iter - 1) << ", " << *iter << std::endl;
        throw std::runtime_error("Array not sorted!");
    }
    return duration;
}

std::chrono::milliseconds test_ints_perform_run_n_times(sorting_algorithm<int> algorithm, const std::vector<int> &data, size_t count, double tolerance)
{
    std::vector<std::chrono::milliseconds> times;
    times.resize(count);
    for (size_t i = 0; i < count; i++)
    {
        times[i] = test_ints_perform_run(algorithm, data);
        if (times[i].count() < 0)
        {
            // std::cout << "Rejecting run. Negative time." << std::endl;
            i--;
            continue;
        }
    }
    bool recheck = true;
    while (recheck)
    {
        recheck = false;
        auto average = std::accumulate(times.begin(), times.end(), std::chrono::milliseconds(0)) / count;
        for (auto &time : times)
        {
            double percent_error = (std::abs(static_cast<double>(time.count()) - static_cast<double>(average.count())) / static_cast<double>(average.count())) * 100;
            //  = (std::abs(static_cast<int64_t>((time - average).count())) / average.count()) * 100;
            // std::cout << "% error: " << percent_error << std::endl;
            if (percent_error > tolerance)
            {
                // std::cout << percent_error << std::endl;
                recheck = true;
                // std::cout << "Rejecting run. Possible outlier. Time: " << time.count() << "\tAvg: " << average.count() << std::endl;
                std::chrono::milliseconds new_time;
                do
                {
                    new_time = test_ints_perform_run(algorithm, data);
                } while (new_time < std::chrono::milliseconds(0));
                time = new_time;
            }
        }
    }
    return std::accumulate(times.begin(), times.end(), std::chrono::milliseconds(0)) / count;
}

std::chrono::milliseconds test_ints_random_fixed_size(sorting_algorithm<int> algorithm, size_t n, size_t test_count, double tolerance)
{
    std::vector<int> original;
    original.resize(n);
    std::minstd_rand rng;
    std::generate_n(original.begin(), n, rng);
    return test_ints_perform_run_n_times(algorithm, original, test_count, tolerance);
}

std::chrono::milliseconds test_ints_ascending_fixed_size(sorting_algorithm<int> algorithm, size_t n, size_t test_count, double tolerance)
{
    std::vector<int> original;
    for (size_t i = 0; i < n; i++)
    {
        original.push_back(i);
    }
    return test_ints_perform_run_n_times(algorithm, original, test_count, tolerance);
}
std::chrono::milliseconds test_ints_descending_fixed_size(sorting_algorithm<int> algorithm, size_t n, size_t test_count, double tolerance)
{
    std::vector<int> original;
    for (size_t i = 0; i < n; i++)
    {
        original.push_back(n - i);
    }
    return test_ints_perform_run_n_times(algorithm, original, test_count, tolerance);
}
std::chrono::milliseconds test_ints_all_same_fixed_size(sorting_algorithm<int> algorithm, size_t n, size_t test_count, double tolerance)
{
    std::vector<int> original;
    for (size_t i = 0; i < n; i++)
    {
        original.push_back(1);
    }
    return test_ints_perform_run_n_times(algorithm, original, test_count, tolerance);
}
std::chrono::milliseconds test_ints_all_unique_fixed_size(sorting_algorithm<int> algorithm, size_t n, size_t test_count, double tolerance)
{
    std::minstd_rand rng;
    std::vector<int> original;
    for (size_t i = 0; i < n; i++)
    {
        original.push_back(i);
    }
    std::shuffle(original.begin(), original.end(), rng);
    return test_ints_perform_run_n_times(algorithm, original, test_count, tolerance);
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