// Standard: C++23. Compiler: Apple Clang 17 (-std=c++23).

#include <exception>
#include <iostream>
#include <random>
#include <string>
#include "DiscreteGenerator.h"
#include "InputReader.h"
#include "PrefixSumGenerator.h"
#include "Report.h"
#include "Statistics.h"

namespace {
std::string resolve_input_path(int argc, char* argv[]) {
    if (argc > 1)
        return argv[1];
    std::cout << "Введіть ім'я вхідного файлу: ";
    std::string path;
    std::getline(std::cin, path);
    return path;
}
}

int main(int argc, char* argv[]) {
    try {
        const std::string path = resolve_input_path(argc, argv);
        const InputData input = read_input(path);

        std::random_device device;
        const std::uint32_t seed = device();

        PrefixSumGenerator custom(input.items, seed);
        DiscreteGenerator library(input.items, seed);

        const ExperimentResult custom_result = run_experiment(custom, input.n, input.items);
        const ExperimentResult library_result = run_experiment(library, input.n, input.items);

        print_comparison(custom_result, library_result);
        return 0;
    } catch (const std::exception& error) {
        std::cout << "Помилка: " << error.what() << '\n';
        return 0;
    }
}