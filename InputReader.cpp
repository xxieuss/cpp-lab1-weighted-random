#include "InputReader.h"
#include <fstream>
#include <stdexcept>
#include <string>

namespace {

template <typename T>
T read_value(std::istream& in, const std::string& field) {
    T value{};
    if (!(in >> value)) {
        throw std::invalid_argument("не вдалося зчитати поле '" + field + "'");
    }
    return value;
}

}

InputData read_input(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("не вдалося відкрити файл: " + path);
    }

    InputData data;
    data.n = read_value<std::uint64_t>(file, "n");
    const auto k = read_value<std::size_t>(file, "k");

    data.items.resize(k);
    for (auto& item : data.items) {
        item.value = read_value<int>(file, "вхідне число");
    }

    for (auto& item : data.items) {
        item.weight = read_value<std::uint64_t>(file, "частота");
    }

    return data;
}