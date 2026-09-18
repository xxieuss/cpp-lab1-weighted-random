#pragma once
#include <cstdint>
#include <random>
#include <vector>
#include "Item.h"

class DiscreteGenerator {
public:
    DiscreteGenerator(const std::vector<Item>& items, std::uint32_t seed);
    int operator()();
private:
    std::vector<int> values_;
    std::mt19937 engine_;
    std::discrete_distribution<std::size_t> dist_;
};