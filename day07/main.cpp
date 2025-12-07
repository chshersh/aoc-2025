// std includes
#include <algorithm>
#include <vector>

// local
#include <aoc_common.hpp>

long long solve(std::string_view contents) {
    const std::vector<std::string_view> diagram =
        aoc::lines(contents) | std::ranges::to<std::vector>();

    size_t rows = diagram.size();
    size_t cols = diagram[0].size();
    std::vector<std::vector<long long>> paths(rows, std::vector<long long>(cols, 0));

    for (size_t col = 0; col < cols; ++col) {
        if (diagram[0][col] == 'S') paths[0][col] = 1;
    }

    for (size_t row = 1; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            switch (diagram[row][col]) {
                case '.':
                    paths[row][col] += paths[row - 1][col];
                    break;
                case '^':
                    paths[row][col - 1] += paths[row - 1][col];
                    paths[row][col + 1] += paths[row - 1][col];
                    break;
            }
        }
    }

    return std::ranges::fold_left(paths.back(), 0, std::plus{});
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", solve(file_contents));
}
