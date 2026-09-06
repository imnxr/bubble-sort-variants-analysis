# Reproducibility

## Two evidence layers

This repository intentionally distinguishes between the historical academic results and the new runnable implementation.

### Reported academic results

`data/operation_counts.csv` preserves operation-count values that were present in the supplied project material.

### Reconstructed reference implementation

`src/main.cpp` was reconstructed because the supplied archive did not contain the original C++ source. It implements the six documented algorithms and the documented dataset categories and sizes.

The reconstructed runner uses:

- C++17
- `-O2 -Wall -Wextra -pedantic`
- Random seed `20260906ULL`
- Comb shrink factor `1.3`
- Sizes `8, 9, 10, 100, 1000, 5000, 10000`
- Datasets `sorted`, `nearly_sorted`, `reverse`, `random`, `duplicate_heavy`
- Comparison and swap counters
- `std::chrono` elapsed-time measurement
- `std::is_sorted` correctness verification

Because the original implementation details are unavailable, the generated measurements are supplementary rather than a reconstruction of the original experiment output.

## Reproduce

With Make:

```bash
make run
```

Or directly:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic src/main.cpp -o bubble_sort_analysis
./bubble_sort_analysis results/benchmark_results.csv
```

## Interpreting timings

The operation counts are suitable for comparing algorithmic work across machines. Wall-clock values in `elapsed_us` depend on hardware, compiler, optimization settings, operating-system scheduling, and system load.

## Reproducing the academic report exactly

Exact reproduction of the original project is not possible from the supplied archive because its original C++ implementation, exact input arrays, and full raw output were not included. The repository therefore avoids presenting reconstructed measurements as historical measurements.
