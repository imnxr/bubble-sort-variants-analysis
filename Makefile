.PHONY: build run clean

CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -pedantic
TARGET := bin/bubble_sort_analysis
RESULTS := results/benchmark_results.csv

build:
	mkdir -p bin
	$(CXX) $(CXXFLAGS) src/main.cpp -o $(TARGET)

run: build
	mkdir -p results
	$(TARGET) $(RESULTS)
	@echo "Results written to $(RESULTS)"

clean:
	rm -rf bin
