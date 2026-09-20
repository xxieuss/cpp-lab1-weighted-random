#pragma once
#include <cstdint>
#include <stdexcept>
#include <unordered_map>
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
ExperimentResult run_experiment(Generator& generator, std::uint64_t n, const std::vector<Item>& items) {
    if (items.empty()) {
        throw std::invalid_argument("run_experiment: порожній список елементів");
    }
    if (n == 0) {
        throw std::invalid_argument("run_experiment: n має бути натуральним");
    }

    std::unordered_map<int, std::size_t> index_of;
    index_of.reserve(items.size());
    for (std::size_t i = 0; i < items.size(); ++i) {
        index_of.emplace(items[i].value, i);
    }

    std::vector<std::uint64_t> counts(items.size(), 0);
    for (std::uint64_t i = 0; i < n; ++i) {
        const auto found = index_of.find(generator());
        if (found == index_of.end()) {
            throw std::logic_error("run_experiment: генератор повернув стороннє число");
        }
        ++counts[found->second];
    }

    ExperimentResult result;
    result.values.reserve(items.size());
    result.weights.reserve(items.size());
    result.observed.reserve(items.size());
    for (std::size_t i = 0; i < items.size(); ++i) {
        result.values.push_back(items[i].value);
        result.weights.push_back(items[i].weight);
        result.observed.push_back(static_cast<double>(counts[i]) / static_cast<double>(n));
    }

    return result;
}