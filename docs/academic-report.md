# Academic Report

## A Comparative Analysis of Bubble Sort Variants: Performance Evaluation and Algorithmic Enhancement

### Abstract

This project presents a comparative study of six Bubble Sort variants: Standard Bubble Sort, Optimized Bubble Sort, Cocktail Shaker Sort, Comb Sort, Odd-Even Sort, and a proposed Adaptive Comb Sort hybrid. The purpose was to investigate how algorithmic modifications influence sorting behavior under different input conditions.

The study combines theoretical complexity analysis with controlled empirical experiments based primarily on operation counts. The tested input characteristics include sorted, nearly sorted, reverse-sorted, random, and duplicate-heavy datasets. The proposed Adaptive Comb Sort combines gap reduction, bidirectional traversal, and early termination. In the reported small-input experiments, this hybrid achieved lower comparison and swap counts than the other evaluated variants in selected cases.

The project demonstrates how seemingly small changes to a sorting algorithm can substantially alter its behavior on structured inputs. The experimental findings are promising, but they should be understood as empirical observations rather than a formal proof of universal superiority.

## 1. Introduction

Sorting is a fundamental problem in computer science and is frequently used to illustrate algorithm design, complexity, optimization, and input sensitivity. Bubble Sort is particularly useful for educational analysis because its basic operation is simple: adjacent elements are compared and exchanged when they are in the wrong order.

Although Standard Bubble Sort is inefficient for large inputs, several variants attempt to improve practical behavior by changing traversal direction, comparison distance, termination conditions, or execution structure.

This project investigates those variants experimentally and asks a central question:

> How much can practical performance improve when Bubble Sort is modified to exploit input structure and move elements more effectively?

## 2. Objectives

The project objectives were to:

- Implement six related sorting algorithms.
- Review and compare their theoretical behavior.
- Examine how input distributions affect their operation counts.
- Measure comparisons and swaps/writes under controlled datasets.
- Develop a hybrid Adaptive Comb Sort variant.
- Compare the proposed hybrid with established algorithms.
- Draw conclusions while clearly distinguishing empirical evidence from theoretical guarantees.

## 3. Algorithms

### 3.1 Standard Bubble Sort

Standard Bubble Sort repeatedly scans the array and swaps adjacent elements when they are out of order.

Because the baseline implementation used in this study does not stop early when a pass makes no swaps, its best, average, and worst cases are all **O(n²)** in terms of comparisons/pass structure.

### 3.2 Optimized Bubble Sort

The optimized version adds an early-termination condition. If a complete pass performs no swap, the array is already sorted and the algorithm stops.

Therefore:

- Best case: **O(n)**
- Average case: **O(n²)**
- Worst case: **O(n²)**

It remains stable when implemented using adjacent swaps only.

### 3.3 Cocktail Shaker Sort

Cocktail Shaker Sort extends Bubble Sort by traversing the array in both directions. A forward pass moves larger elements toward the end, while a backward pass moves smaller elements toward the beginning.

With early-exit behavior, its best case can be **O(n)**, while average and worst cases remain **O(n²)**.

### 3.4 Comb Sort

Comb Sort addresses a weakness of Bubble Sort in which an element may need many adjacent swaps to move a long distance. It compares elements separated by a gap and progressively shrinks that gap until the algorithm behaves like a final gap-1 pass.

Comb Sort is generally treated as an **O(n²) worst-case** sorting method. Practical behavior is often substantially better than basic Bubble Sort, although exact average-case analysis depends on the shrink factor and analytical model.

### 3.5 Odd-Even Sort

Odd-Even Sort alternates compare-swap phases over odd/even index pairs and even/odd index pairs. It is closely related to parallel sorting networks and can be useful in parallel settings.

In the sequential implementation considered here, its practical operation count remains quadratic in general. Parallel-time complexity depends on the execution model and should not be confused with sequential runtime.

### 3.6 Adaptive Comb Sort

Adaptive Comb Sort is the proposed hybrid in this project. It combines:

1. **Comb-style gap reduction** for long-distance movement.
2. **Bidirectional traversal** inspired by Cocktail Shaker Sort.
3. **Early termination** inspired by Optimized Bubble Sort.

The design goal is to reduce unnecessary local swaps while allowing the algorithm to react to the state of the input.

The proposed algorithm should be understood as a **course-project hybrid design**. The experiments provide empirical evidence about its behavior, but they do not constitute a proof that it is asymptotically superior to all other algorithms.

## 4. Complexity Comparison

| Algorithm | Best Case | Average Case | Worst Case | Extra Space | Stable |
|---|---:|---:|---:|---:|:---:|
| Standard Bubble Sort | O(n²) | O(n²) | O(n²) | O(1) | Yes |
| Optimized Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Cocktail Shaker Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Comb Sort | Depends on implementation/analysis | Typically discussed as sub-quadratic in practice | O(n²) | O(1) | No |
| Odd-Even Sort | O(n) with early termination | O(n²) | O(n²) | O(1) | Yes |
| Adaptive Comb Sort | Depends on input and stopping behavior | Empirically evaluated | O(n²) upper bound | O(1) | No |

## 5. Proposed Algorithm Structure

```text
Start
  |
  v
Initialize gap and swapped flag
  |
  v
Shrink gap according to Comb-style rule
  |
  v
Forward comparison pass using current gap
  |
  v
Backward comparison pass
  |
  v
Were any swaps made?
  |              |
 No              Yes
  |               |
  v               v
Stop       Continue while gap > 1
                 |
                 v
          Final gap-1 pass
                 |
                 v
              Stop when
           no swaps occur
```

## 6. Experimental Methodology

The experiment followed a controlled comparative design:

**Algorithm selection → implementation → dataset generation → execution → operation counting → comparison → visualization → interpretation**

The input distributions were selected to represent different levels and forms of disorder:

- **Sorted:** already in ascending order.
- **Nearly sorted:** mostly ordered with a small number of misplaced elements.
- **Reverse sorted:** descending order, representing strong adverse disorder for adjacent-exchange algorithms.
- **Random:** no intentional order.
- **Duplicate-heavy:** many repeated values, useful for observing behavior when equality is common.

### Measured operations

The principal measurements were:

- **Comparisons:** number of element-order checks.
- **Swaps/writes:** number of data exchanges or writes recorded by the implementation.

These measurements provide a machine-independent way of comparing algorithmic work. They are not equivalent to real elapsed CPU time.

## 7. Reported Results

### Nearly Sorted, n = 10

| Algorithm | Comparisons | Swaps |
|---|---:|---:|
| Standard Bubble | 45 | 3 |
| Optimized Bubble | 25 | 3 |
| Cocktail Shaker | 23 | 3 |
| Comb | 18 | 2 |
| Odd-Even | 45 | 3 |
| Adaptive Comb | **16** | **2** |

### Reverse Sorted, n = 10

| Algorithm | Comparisons | Swaps |
|---|---:|---:|
| Standard Bubble | 45 | 45 |
| Optimized Bubble | 45 | 45 |
| Cocktail Shaker | 45 | 45 |
| Comb | 30 | 22 |
| Odd-Even | 45 | 45 |
| Adaptive Comb | **26** | **20** |

The available project material also describes experiments at **n = 100, 1,000, 5,000, and 10,000**. The actual numerical output for all of those runs was not included in the supplied archive, so this public repository does not invent or estimate missing measurements.

## 8. Discussion

The results demonstrate that algorithmic modifications can substantially alter the amount of work performed on particular input structures.

The early-exit optimization is especially valuable for already sorted or nearly sorted data because the algorithm can detect the absence of swaps. Comb-style gaps are valuable when elements are far from their target positions because a single comparison can span multiple indices.

Cocktail traversal offers a complementary benefit by allowing movement in both directions. Odd-Even Sort provides a different structural approach and remains interesting from the perspective of parallel execution, even when its sequential operation count is not competitive.

The reported examples show Adaptive Comb Sort achieving the lowest comparison count and matching or improving the minimum swap count among the six algorithms. This supports the design hypothesis that combining complementary optimizations can reduce work on selected input distributions.

However, these findings should not be generalized into a claim that Adaptive Comb Sort is universally faster. A more extensive study would require larger datasets, repeated trials, a clearly specified gap policy, reproducible random seeds, and direct wall-clock benchmarking under controlled hardware/compiler settings.

## 9. Limitations

Several limitations should be acknowledged:

- The primary measured quantities were operation counts rather than CPU wall-clock time.
- Not all large-input result tables from the original study were available in the provided materials.
- The proposed hybrid does not have a formal proof of asymptotic superiority.
- Results can change with gap-shrink factor, implementation choices, compiler optimization, hardware, and dataset generation.
- The study is intended as an academic algorithm-analysis experiment rather than a production sorting benchmark.

## 10. Conclusion

This project demonstrates the value of comparative algorithm analysis through both theory and experiment. Bubble Sort provides a simple baseline, while Optimized Bubble Sort, Cocktail Shaker Sort, Comb Sort, and Odd-Even Sort demonstrate different strategies for reducing unnecessary work or changing execution structure.

The proposed Adaptive Comb Sort combines these ideas into a single hybrid approach. In the reported experiments, it achieved strong operation-count results on several tested inputs. The work therefore suggests that combining gap-based movement, bidirectional traversal, and adaptive termination is a useful direction for further experimentation.

The central lesson is that algorithm performance is influenced not only by asymptotic complexity but also by input structure, implementation strategy, and the specific operations being measured.
