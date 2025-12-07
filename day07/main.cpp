// std includes
#include <string_view>

// local
#include <aoc_common.hpp>

long long solve(std::string_view contents) {
    return 0;
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", solve(file_contents));
}
