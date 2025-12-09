// std includes
#include <vector>

// local
#include <aoc_common.hpp>

struct Coord {
    long long x, y;
};

long long area(Coord c1, Coord c2) {
    return (std::abs(c1.x - c2.x) + 1) * (std::abs(c1.y - c2.y) + 1);
}

constexpr auto parse_line = [](std::string_view line) -> Coord {
    auto parts = line
        | std::views::split(',')
        | std::views::transform([](auto&& seq) {
            return aoc::to_ll(std::string_view{seq});
        })
        | std::ranges::to<std::vector<long long>>();

    return { parts[0], parts[1] };
};

long long solve(std::string_view contents) {
    auto coordinates =
        aoc::lines(contents)
        | std::views::transform(parse_line)
        | std::ranges::to<std::vector<Coord>>();

    long long max_area = 0;
    for (size_t i = 0; i < coordinates.size() - 1; ++i) {
        for (size_t j = i + 1; j < coordinates.size(); ++j) {
            max_area = std::max(max_area, area(coordinates[i], coordinates[j]));
        }
    }
    return max_area;
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", solve(file_contents));
}
