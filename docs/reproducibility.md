# Reproducibility

## Current Repository State

This repository contains the cleaned documentation and the numerical results that were available in the supplied academic project material.

The original archive did not contain the C++ implementation files. For that reason, this repository intentionally does not fabricate or reconstruct source code and does not claim that the missing large-scale numerical outputs can currently be reproduced from this repository alone.

## To Reproduce the Study Fully

Add the original C++ implementation under `src/`, then document:

1. Compiler and version.
2. Compiler flags.
3. Operating system and hardware.
4. Random-number seed, if applicable.
5. Dataset-generation procedure.
6. Exact gap-shrink rule for Comb Sort and Adaptive Comb Sort.
7. Number of repetitions per experiment.
8. Definition of a comparison.
9. Definition of a swap/write.
10. Raw experiment outputs.

## Recommended Structure for the Missing Implementation

```text
src/
├── bubble_sort.cpp
├── optimized_bubble_sort.cpp
├── cocktail_shaker_sort.cpp
├── comb_sort.cpp
├── odd_even_sort.cpp
├── adaptive_comb_sort.cpp
└── benchmark.cpp
```

Use this only as a suggested organizational structure. The actual course implementation should be added rather than recreated from assumptions.

## Reporting Rule

Only measurements that were actually produced by the project should be published. Missing results should be marked as unavailable instead of estimated.
