#pragma once
#include <compare>
#include <cstdint>

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