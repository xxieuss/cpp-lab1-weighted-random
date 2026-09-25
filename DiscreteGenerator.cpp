#include "DiscreteGenerator.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>

DiscreteGenerator::DiscreteGenerator(const std::vector<Item>& items, std::uint32_t seed) : engine_(seed) {
    if (items.empty()) {
        throw std::invalid_argument("DiscreteGenerator: порожній список елементів");
    }

    sum_of_weights(items);

    values_.reserve(items.size());
    std::vector<double> weights;
    weights.reserve(items.size());
    std::ranges::transform(items, std::back_inserter(values_), [](const Item& item) { return item.value; });
    std::ranges::transform(items, std::back_inserter(weights), [](const Item& item) { 
        return static_cast<double>(item.weight); 
    });

    dist_ = std::discrete_distribution<std::size_t>(weights.begin(), weights.end());
}

int DiscreteGenerator::operator()() {
    return values_[dist_(engine_)];
}