# Implementation Notes

## Why this file exists

The academic project archive supplied for this repository did not contain the original C++ source files. Rather than leave the repository non-runnable, a reference implementation was reconstructed from the documented algorithm descriptions, methodology, and reported experimental design.

## What was reconstructed

The implementation in [`../src/main.cpp`](../src/main.cpp) provides:

- Standard Bubble Sort
- Optimized Bubble Sort with early exit
- Cocktail Shaker Sort
- Comb Sort with shrink factor 1.3
- Odd-Even Sort with early termination
- Adaptive Comb Sort combining gap reduction, forward/backward traversal, and adaptive termination
- Dataset generators for sorted, nearly sorted, reverse, random, and duplicate-heavy input
- Comparison and swap counters
- Wall-clock timing using `std::chrono`
- Correctness verification using `std::is_sorted`

## What was not reconstructed

The implementation does **not** claim to be the missing original submission. In particular, the exact original gap policy, dataset values, random seed, instrumentation details, and control flow cannot be recovered from the report alone.

For this reason, the repository maintains two separate evidence layers:

1. **Reported academic results** in `data/operation_counts.csv`, which are preserved from the supplied project material.
2. **Reconstructed reference benchmarks** in `results/generated_*.csv`, generated from the new runnable implementation.

This separation prevents the repository from presenting reconstructed measurements as historical results.

## Adaptive Comb Sort design

The proposed hybrid is intentionally simple and inspectable:

```text
while gap > 1 or previous cycle swapped:
    shrink gap
    forward gap-based compare/swap pass
    backward gap-based compare/swap pass
    stop after a gap-1 cycle makes no swaps
```

Its purpose is to explore whether three complementary heuristics can work together:

- long-distance movement,
- movement in both directions,
- stopping when additional work is unnecessary.

## Benchmark interpretation

Operation counts are the most useful machine-independent comparison in this project. `elapsed_us` is included for practical context, but wall-clock timings vary with compiler, optimization level, processor, system load, and implementation details.

The reconstructed benchmark is therefore useful as a runnable demonstration and extension point, not as a statistically rigorous performance claim.
