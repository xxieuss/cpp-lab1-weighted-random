#include "PrefixSumGenerator.h"
#include <limits>
#include <stdexcept>

PrefixSumGenerator::PrefixSumGenerator(const std::vector<Item>& items, std::uint32_t seed) : engine_(seed) {
    if (items.empty()) {
        throw std::invalid_argument("PrefixSumGenerator: порожній список елементів");
    }

    values_.reserve(items.size());
    cumulative_.reserve(items.size());

    std::uint64_t running = 0;
    for (const Item& item : items) {
        if (item.weight == 0) {
            throw std::invalid_argument("PrefixSumGenerator: частота має бути додатною");
        }
        if (running > std::numeric_limits<std::uint64_t>::max() - item.weight) {
            throw std::invalid_argument("PrefixSumGenerator: сума частот переповнює 64-бітний тип");
        }
        running += item.weight;
        values_.push_back(item.value);
        cumulative_.push_back(running);
    }

    total_ = running;
    dist_ = std::uniform_int_distribution<std::uint64_t>(0, total_ - 1);
}

int PrefixSumGenerator::operator()() {
    throw std::logic_error("PrefixSumGenerator::operator(): not implemented yet");
}