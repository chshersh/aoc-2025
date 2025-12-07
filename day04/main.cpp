// std includes
#include <array>
#include <vector>

// local
#include <aoc_common.hpp>

constexpr auto directions = std::to_array<std::pair<int, int>>({
    {-1, -1}, {-1, 0}, {-1, 1},
    { 0, -1},          { 0, 1},
    { 1, -1}, { 1, 0}, { 1, 1},
});

long long remove_accessible(
    std::vector<std::string>& input_grid,
    std::vector<std::string>& output_grid,
    int rows,
    int cols
) {
    auto in_bounds = [rows, cols](int i, int j) -> bool {
        return 0 <= i && i < rows &&
               0 <= j && j < cols;
    };

    long long accessible_rolls = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (input_grid[i][j] != '@') {
                output_grid[i][j] = '.';
                continue;
            }

            int adjacent_rolls = 0;

            for (auto [dir_row, dir_col] : directions) {
                int row = i + dir_row;
                int col = j + dir_col;
                if (in_bounds(row, col) && input_grid[row][col] == '@')
                    adjacent_rolls++;
            }

            if (adjacent_rolls < 4) {
                accessible_rolls++;
                output_grid[i][j] = '.';
            } else {
                output_grid[i][j] = '@';
            }
        }
    }

    return accessible_rolls;
}

long long solve(std::string_view contents) {
    std::vector<std::string> grid =
        aoc::lines(contents)
        | std::views::transform([](auto sv) { return std::string{sv}; })
        | std::ranges::to<std::vector>();

    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    auto next_grid = std::vector<std::string>(rows, std::string(cols, '.'));

    int total_removed_rolls = 0;
    while (int removed_rolls = remove_accessible(grid, next_grid, rows, cols)) {
        total_removed_rolls += removed_rolls;
        grid.swap(next_grid);

    }
    return total_removed_rolls;
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", solve(file_contents));
}
