# Source Code

`main.cpp` is the runnable C++17 reference implementation for this repository.

## Included algorithms

- Standard Bubble Sort
- Optimized Bubble Sort
- Cocktail Shaker Sort
- Comb Sort
- Odd-Even Sort
- Adaptive Comb Sort

## Instrumentation

Each implementation records:

- element comparisons,
- swaps,
- elapsed wall-clock time,
- final sorting correctness.

The benchmark runner generates all five documented dataset categories at the documented input sizes.

## Important provenance note

The original course submission source was not present in the supplied archive. Therefore, `main.cpp` is a **reconstructed reference implementation based on the documented project design**, not a recovered copy of the original source.

That distinction is also documented in [`../docs/implementation-notes.md`](../docs/implementation-notes.md).
