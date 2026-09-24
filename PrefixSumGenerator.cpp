#include "PrefixSumGenerator.h"
#include <stdexcept>
#include <algorithm>

PrefixSumGenerator::PrefixSumGenerator(const std::vector<Item>& items, std::uint32_t seed) : engine_(seed) {
    if (items.empty()) {
        throw std::invalid_argument("PrefixSumGenerator: порожній список елементів");
    }

    total_ = sum_of_weights(items);

    values_.reserve(items.size());
    cumulative_.reserve(items.size());

    std::uint64_t running = 0;
    for (const Item& item : items) {
        running += item.weight;
        values_.push_back(item.value);
        cumulative_.push_back(running);
    }

    dist_ = std::uniform_int_distribution<std::uint64_t>(0, total_ - 1);
}

int PrefixSumGenerator::operator()() {
    const std::uint64_t random_value = dist_(engine_);
    const auto it = std::upper_bound(cumulative_.begin(), cumulative_.end(), random_value);
    return values_[static_cast<std::size_t>(it - cumulative_.begin())];
}