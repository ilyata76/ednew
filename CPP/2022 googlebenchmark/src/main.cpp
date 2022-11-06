#include <iostream>
#include <sstream>

#include <benchmark/benchmark.h>

#include <vector>
#include <numeric>
#include <string>

#define TEST_NUM_COUNT10 10
#define TEST_NUM_COUNT100 100
#define TEST_NUM_COUNT1000 1000

auto IntToStringConversionTest(int count) {
	std::vector<int> inputNumbers(count);
	std::vector<std::string> outNumbers;

	std::iota(std::begin(inputNumbers), std::end(inputNumbers), 0);
	for (auto& num : inputNumbers)
		outNumbers.push_back(std::to_string(num));

	return outNumbers;
}

auto DoubleToStringConversionTest(int count) {
	std::vector<double> inputNumbers(count);
	std::vector<std::string> outNumbers;

	std::iota(std::begin(inputNumbers), std::end(inputNumbers), 0.12345);
	for (auto& num : inputNumbers)
		outNumbers.push_back(std::to_string(num));

	return outNumbers;
}


void IntToString(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            IntToStringConversionTest(state.range_x())
        );
    }
}
BENCHMARK(IntToString)->Arg(TEST_NUM_COUNT1000);

void DoubleToString(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
            DoubleToStringConversionTest(state.range_x())
        );
    }
}
BENCHMARK(DoubleToString)->Arg(TEST_NUM_COUNT1000);

BENCHMARK_MAIN();