# Results

This directory contains two distinct classes of results so the repository never mixes historical academic measurements with newly generated measurements.

## 1. Reported academic results

[`../data/operation_counts.csv`](../data/operation_counts.csv) contains operation counts reproduced from the supplied academic material for selected small-input cases.

Reported cases include:

- Nearly sorted, n = 10
- Reverse sorted, n = 10

## 2. Reconstructed reference benchmarks

The `generated_*.csv` files were produced from the reconstructed `src/main.cpp` implementation using the same five input categories and the documented input sizes:

- `generated_sorted.csv`
- `generated_nearly_sorted.csv`
- `generated_reverse.csv`
- `generated_random.csv`
- `generated_duplicate_heavy.csv`

Each file contains comparisons, swaps, elapsed microseconds, and a correctness flag. The random and duplicate-heavy generators use a fixed seed in the reference runner.

These generated measurements are **supplementary**. Because the original C++ source was unavailable, they are not claimed to reproduce the exact execution or operation counts of the original submission.

Run the project yourself with:

```bash
make run
```

The runner then produces a combined `results/benchmark_results.csv` file.
