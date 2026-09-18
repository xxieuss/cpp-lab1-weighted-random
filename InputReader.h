#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Item.h"

struct InputData {
    std::uint64_t n{};
    std::vector<Item> items;
};

InputData read_input(const std::string& path);