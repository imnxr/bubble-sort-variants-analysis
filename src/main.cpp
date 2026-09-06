// Comparative Analysis of Bubble Sort Variants
// Academic project implementation reconstructed from the project's documented
// algorithms, methodology, and reported operation-count study.
//
// Algorithms:
//   1. Standard Bubble Sort
//   2. Optimized Bubble Sort
//   3. Cocktail Shaker Sort
//   4. Comb Sort
//   5. Odd-Even Sort
//   6. Adaptive Comb Sort (proposed hybrid)
//
// The implementation records comparisons, swaps, elapsed time, and whether
// the final output is correctly sorted. A fixed seed makes generated random
// datasets reproducible. Wall-clock measurements remain machine-dependent.

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

struct Metrics {
    std::uint64_t comparisons = 0;
    std::uint64_t swaps = 0;
};

template <typename T>
inline bool greater_counted(const T& a, const T& b, Metrics& m) {
    ++m.comparisons;
    return a > b;
}

template <typename T>
inline void swap_counted(T& a, T& b, Metrics& m) {
    std::swap(a, b);
    ++m.swaps;
}

void standard_bubble_sort(std::vector<int>& a, Metrics& m) {
    const std::size_t n = a.size();
    for (std::size_t pass = 0; pass + 1 < n; ++pass) {
        for (std::size_t j = 0; j + 1 < n - pass; ++j) {
            if (greater_counted(a[j], a[j + 1], m)) {
                swap_counted(a[j], a[j + 1], m);
            }
        }
    }
}

void optimized_bubble_sort(std::vector<int>& a, Metrics& m) {
    const std::size_t n = a.size();
    for (std::size_t pass = 0; pass + 1 < n; ++pass) {
        bool swapped = false;
        for (std::size_t j = 0; j + 1 < n - pass; ++j) {
            if (greater_counted(a[j], a[j + 1], m)) {
                swap_counted(a[j], a[j + 1], m);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void cocktail_shaker_sort(std::vector<int>& a, Metrics& m) {
    if (a.size() < 2) {
        return;
    }

    std::size_t left = 0;
    std::size_t right = a.size() - 1;
    bool swapped = true;

    while (swapped) {
        swapped = false;

        for (std::size_t i = left; i < right; ++i) {
            if (greater_counted(a[i], a[i + 1], m)) {
                swap_counted(a[i], a[i + 1], m);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }

        swapped = false;
        --right;

        for (std::size_t i = right; i > left; --i) {
            if (greater_counted(a[i - 1], a[i], m)) {
                swap_counted(a[i - 1], a[i], m);
                swapped = true;
            }
        }

        ++left;
    }
}

void comb_sort(std::vector<int>& a, Metrics& m, double shrink = 1.3) {
    std::size_t gap = a.size();
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = static_cast<std::size_t>(gap / shrink);
        if (gap < 1) {
            gap = 1;
        }

        swapped = false;
        for (std::size_t i = 0; i + gap < a.size(); ++i) {
            if (greater_counted(a[i], a[i + gap], m)) {
                swap_counted(a[i], a[i + gap], m);
                swapped = true;
            }
        }
    }
}

void odd_even_sort(std::vector<int>& a, Metrics& m) {
    const std::size_t n = a.size();
    bool sorted = false;

    while (!sorted) {
        sorted = true;

        for (std::size_t i = 1; i + 1 < n; i += 2) {
            if (greater_counted(a[i], a[i + 1], m)) {
                swap_counted(a[i], a[i + 1], m);
                sorted = false;
            }
        }

        for (std::size_t i = 0; i + 1 < n; i += 2) {
            if (greater_counted(a[i], a[i + 1], m)) {
                swap_counted(a[i], a[i + 1], m);
                sorted = false;
            }
        }
    }
}

void adaptive_comb_sort(std::vector<int>& a, Metrics& m, double shrink = 1.3) {
    if (a.size() < 2) {
        return;
    }

    std::size_t gap = a.size();
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = static_cast<std::size_t>(gap / shrink);
        if (gap < 1) {
            gap = 1;
        }

        swapped = false;

        // Forward Comb-style pass for long-distance movement.
        for (std::size_t i = 0; i + gap < a.size(); ++i) {
            if (greater_counted(a[i], a[i + gap], m)) {
                swap_counted(a[i], a[i + gap], m);
                swapped = true;
            }
        }

        // Backward Cocktail-style pass.
        if (a.size() > gap) {
            for (std::size_t i = a.size() - 1; i >= gap; --i) {
                if (greater_counted(a[i - gap], a[i], m)) {
                    swap_counted(a[i - gap], a[i], m);
                    swapped = true;
                }
                if (i == gap) {
                    break;
                }
            }
        }

        // Early termination once the gap-1 cycle makes no changes.
        if (gap == 1 && !swapped) {
            break;
        }
    }
}

using SortFunction = void (*)(std::vector<int>&, Metrics&);

struct Algorithm {
    const char* name;
    SortFunction function;
};

void comb_sort_runner(std::vector<int>& a, Metrics& m) {
    comb_sort(a, m, 1.3);
}

void adaptive_comb_sort_runner(std::vector<int>& a, Metrics& m) {
    adaptive_comb_sort(a, m, 1.3);
}

const std::vector<Algorithm> algorithms = {
    {"Standard Bubble Sort", standard_bubble_sort},
    {"Optimized Bubble Sort", optimized_bubble_sort},
    {"Cocktail Shaker Sort", cocktail_shaker_sort},
    {"Comb Sort", comb_sort_runner},
    {"Odd-Even Sort", odd_even_sort},
    {"Adaptive Comb Sort", adaptive_comb_sort_runner},
};

std::vector<int> make_dataset(std::size_t n, const std::string& kind, std::mt19937_64& rng) {
    std::vector<int> a(n);

    if (kind == "sorted") {
        for (std::size_t i = 0; i < n; ++i) {
            a[i] = static_cast<int>(i);
        }
    } else if (kind == "nearly_sorted") {
        for (std::size_t i = 0; i < n; ++i) {
            a[i] = static_cast<int>(i);
        }
        if (n >= 4) {
            std::swap(a[n / 3], a[n / 3 + 1]);
            std::swap(a[(2 * n) / 3], a[(2 * n) / 3 + 1]);
        }
    } else if (kind == "reverse") {
        for (std::size_t i = 0; i < n; ++i) {
            a[i] = static_cast<int>(n - i);
        }
    } else if (kind == "random") {
        std::uniform_int_distribution<int> distribution(0, static_cast<int>(n * 10 + 1));
        for (auto& value : a) {
            value = distribution(rng);
        }
    } else if (kind == "duplicate_heavy") {
        std::uniform_int_distribution<int> distribution(0, 9);
        for (auto& value : a) {
            value = distribution(rng);
        }
    } else {
        throw std::invalid_argument("Unknown dataset type: " + kind);
    }

    return a;
}

bool sorted_correctly(const std::vector<int>& a) {
    return std::is_sorted(a.begin(), a.end());
}

int main(int argc, char** argv) {
    const std::string output_path = argc >= 2 ? argv[1] : "results/benchmark_results.csv";

    std::ofstream output(output_path);
    if (!output) {
        std::cerr << "Could not open output path: " << output_path << '\n';
        return 1;
    }

    // Includes the detailed n=8/9/10 cases and the larger sizes described by
    // the academic methodology.
    const std::vector<std::size_t> sizes = {8, 9, 10, 100, 1000, 5000, 10000};
    const std::vector<std::string> datasets = {
        "sorted", "nearly_sorted", "reverse", "random", "duplicate_heavy"
    };

    std::mt19937_64 rng(20260906ULL);

    output << "algorithm,dataset,n,comparisons,swaps,elapsed_us,correct\n";

    for (const auto& algorithm : algorithms) {
        for (const auto& dataset : datasets) {
            for (const auto n : sizes) {
                const auto input = make_dataset(n, dataset, rng);
                auto values = input;
                Metrics metrics;

                const auto start = std::chrono::steady_clock::now();
                algorithm.function(values, metrics);
                const auto stop = std::chrono::steady_clock::now();

                const auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(
                    stop - start
                ).count();

                output << '"' << algorithm.name << '"' << ','
                       << dataset << ','
                       << n << ','
                       << metrics.comparisons << ','
                       << metrics.swaps << ','
                       << elapsed_us << ','
                       << (sorted_correctly(values) ? "true" : "false")
                       << '\n';
            }
        }
    }

    std::cout << "Benchmark complete: " << output_path << '\n';
    return 0;
}
