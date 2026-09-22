#include "InputReader.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <algorithm>

namespace {

template <typename T>
T read_value(std::istream& in, const std::string& field) {
    T value{};
    if (!(in >> value)) {
        throw std::invalid_argument("не вдалося зчитати поле '" + field + "'");
    }
    return value;
}

std::uint64_t read_positive(std::istream& in, const std::string& field) {
    const long long value = read_value<long long>(in, field);
    if (value <= 0) {
        throw std::invalid_argument(
            "поле '" + field + "' має бути натуральним числом, отримано " + std::to_string(value));
    }
    return static_cast<std::uint64_t>(value);
}

void ensure_values_are_distinct(const std::vector<Item>& items) {
    std::vector<Item> sorted = items;
    std::ranges::sort(sorted);

    const auto duplicate = std::ranges::adjacent_find(sorted);
    if (duplicate != sorted.end()) {
        throw std::invalid_argument( "вхідні числа мають бути різними, повторюється " + std::to_string(duplicate->value));
    }
}

}

InputData read_input(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("не вдалося відкрити файл: " + path);
    }

    InputData data;
    data.n = read_positive(file, "n");
    const std::uint64_t k = read_positive(file, "k");

    data.items.resize(static_cast<std::size_t>(k));
    for (auto& item : data.items) {
        item.value = read_value<int>(file, "вхідне число");
    }

    for (auto& item : data.items) {
        item.weight = read_positive(file, "частота");
    }

    ensure_values_are_distinct(data.items);

    return data;
}