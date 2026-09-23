#include "Report.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>

void print_comparison(const ExperimentResult& custom, const ExperimentResult& library) {
    if (custom.values.size() != library.values.size() || custom.samples != library.samples) {
        throw std::logic_error("print_comparison: результати експериментів несумісні");
    }

    std::cout << "\nЗгенеровано чисел: " << custom.samples << "\n";
    std::cout << std::fixed << std::setprecision(6);

    for (std::size_t i = 0; i < custom.values.size(); ++i) {
        std::cout << "\nЧисло " << custom.values[i]
        << ", вага " << custom.weights[i] << '\n'
        << "  задана частота:          " << custom.expected[i] << '\n'
        << "  власний алгоритм:        " << custom.observed[i]
        << "  (розбіжність " << custom.deviations[i] << ")\n"
        << "  discrete_distribution:   " << library.observed[i]
        << "  (розбіжність " << library.deviations[i] << ")\n";
    }

    std::cout << "\nНайбільша розбіжність:\n"
    << "  власний алгоритм: " << custom.max_deviation
    << " (число " << custom.worst_value << ")\n"
    << "  discrete_distribution: " << library.max_deviation
    << " (число " << library.worst_value << ")\n";
}