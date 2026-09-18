#pragma once
#include <cstdint>
#include <stdexcept>
#include <vector>
#include "Item.h"

struct ExperimentResult {
    std::vector<int> values;
    std::vector<std::uint64_t> weights;
    std::vector<double> expected;
    std::vector<double> observed;
    double max_deviation{};
    int worst_value{};
};

template <typename Generator>
ExperimentResult run_experiment(Generator&, std::uint64_t, const std::vector<Item>&) {
    throw std::logic_error("run_experiment: not implemented yet");
}