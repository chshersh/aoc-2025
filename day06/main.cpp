// std includes
#include <vector>

// local includes
#include <aoc_common.hpp>

long long solve(std::string_view contents) {
    const std::vector<std::string_view> rows =
        aoc::lines(contents) | std::ranges::to<std::vector>();

    std::vector<std::vector<long long>> numbers = rows
        | std::views::take(rows.size() - 1)
        | std::views::transform([](std::string_view sv) {
           return aoc::words(sv)
               | std::views::transform([](auto sv) { return aoc::to_ll(sv); })
               | std::ranges::to<std::vector>();
        })
        | std::ranges::to<std::vector>();

    std::vector<std::string_view> operations = aoc::words(rows.back())
        | std::ranges::to<std::vector>();

    auto fold = [&numbers](size_t col, long long init, auto f) -> long long {
        long long acc = init;
        for (size_t row = 0; row < numbers.size(); ++row) {
            acc = f(acc, numbers[row][col]);
        }
        return acc;
    };

    long long total = 0;
    for (size_t col = 0; col < numbers[0].size(); ++col) {
        long long current = operations[col] == "+"
            ? fold(col, 0, std::plus{})
            : fold(col, 1, std::multiplies{});

        total += current;
    }
    return total;
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", solve(file_contents));
}
