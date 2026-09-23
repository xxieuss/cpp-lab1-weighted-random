#pragma once
#include <cmath>
#include <cstdint>
#include <numeric>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include "Item.h"

struct ExperimentResult {
    std::uint64_t samples{};
    std::vector<int> values;
    std::vector<std::uint64_t> weights;
    std::vector<double> expected;
    std::vector<double> observed;
    std::vector<double> deviations;
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

    const std::uint64_t total = std::accumulate(
        items.begin(), items.end(), std::uint64_t{0},
        [](std::uint64_t sum, const Item& item) { return sum + item.weight; });

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

    const auto share = [](std::uint64_t part, std::uint64_t whole) {
        return static_cast<double>(part) / static_cast<double>(whole);
    };

    ExperimentResult result;
    result.samples = n;
    result.values.reserve(items.size());
    result.weights.reserve(items.size());
    result.expected.reserve(items.size());
    result.observed.reserve(items.size());
    for (std::size_t i = 0; i < items.size(); ++i) {
        result.values.push_back(items[i].value);
        result.weights.push_back(items[i].weight);
        result.expected.push_back(share(items[i].weight, total));
        result.observed.push_back(share(counts[i], n));
    }

    result.deviations.reserve(items.size());
    result.worst_value = result.values.front();
    for (std::size_t i = 0; i < items.size(); ++i) {
        const double deviation = std::abs(result.expected[i] - result.observed[i]);
        result.deviations.push_back(deviation);
        if (deviation > result.max_deviation) {
            result.max_deviation = deviation;
            result.worst_value = result.values[i];
        }
    }

    return result;
}