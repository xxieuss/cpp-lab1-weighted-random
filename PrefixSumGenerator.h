#pragma once
#include <cstdint>
#include <random>
#include <vector>
#include "Item.h"

class PrefixSumGenerator {
public:
    PrefixSumGenerator(const std::vector<Item>& items, std::uint32_t seed);
    int operator()();
private:
    std::vector<int> values_;
    std::vector<std::uint64_t> cumulative_;
    std::uint64_t total_{};
    std::mt19937 engine_;
    std::uniform_int_distribution<std::uint64_t> dist_;
};