#pragma once
#include <compare>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

struct Item {
    int value{};
    std::uint64_t weight{};
    constexpr auto operator<=>(const Item& other) const noexcept {
        return value <=> other.value;
    }
    constexpr bool operator==(const Item& other) const noexcept {
        return value == other.value;
    }
};

inline std::uint64_t sum_of_weights(const std::vector<Item>& items) {
    std::uint64_t total = 0;
    for (const Item& item : items) {
        if (item.weight == 0) {
            throw std::invalid_argument("частота має бути додатною");
        }
        if (total > std::numeric_limits<std::uint64_t>::max() - item.weight) {
            throw std::invalid_argument("сума частот переповнює 64-бітний тип");
        }
        total += item.weight;
    }
    return total;
}