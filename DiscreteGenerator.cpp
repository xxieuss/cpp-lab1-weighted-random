#include "DiscreteGenerator.h"
#include <stdexcept>

DiscreteGenerator::DiscreteGenerator(const std::vector<Item>& items, std::uint32_t seed) : engine_(seed) {
    if (items.empty()) {
        throw std::invalid_argument("DiscreteGenerator: порожній список елементів");
    }

    values_.reserve(items.size());
    std::vector<double> weights;
    weights.reserve(items.size());

    for (const Item& item : items) {
        if (item.weight == 0) {
            throw std::invalid_argument("DiscreteGenerator: частота має бути додатною");
        }
        values_.push_back(item.value);
        weights.push_back(static_cast<double>(item.weight));
    }

    dist_ = std::discrete_distribution<std::size_t>(weights.begin(), weights.end());
}

int DiscreteGenerator::operator()() {
    return values_[dist_(engine_)];
}
