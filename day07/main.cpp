// std includes
#include <vector>

// local
#include <aoc_common.hpp>

int solve(std::string_view contents) {
    const std::vector<std::string_view> diagram =
        aoc::lines(contents) | std::ranges::to<std::vector>();

    size_t rows = diagram.size();
    size_t cols = diagram[0].size();
    std::vector<std::vector<int>> rays(rows, std::vector<int>(cols, 0));

    for (size_t col = 0; col < cols; ++col) {
        if (diagram[0][col] == 'S') rays[0][col] = 1;
    }

    int splits = 0;

    for (size_t row = 1; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            if (rays[row - 1][col] == 0) continue;
            switch (diagram[row][col]) {
                case '.':
                    rays[row][col] = 1;
                    break;
                case '^':
                    rays[row][col - 1] = 1;
                    rays[row][col + 1] = 1;
                    splits++;
                    break;
            }
        }
    }

    return splits;
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", solve(file_contents));
}
