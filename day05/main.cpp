// std includes
#include <algorithm>
#include <vector>

// local
#include <aoc_common.hpp>

struct IdRange {
    long long start;
    long long end;

    auto operator<=>(const IdRange&) const = default;
};

// Parse "12-18" into IdRange{12, 18}
IdRange parse_range(std::string_view sv) {
    const auto delim_pos   = sv.find_first_of('-');
    const auto range_start = sv.substr(0, delim_pos);
    const auto range_end   = sv.substr(delim_pos + 1);
    const auto start       = aoc::to_ll(range_start);
    const auto end         = aoc::to_ll(range_end);
    return { start, end };
}

std::vector<IdRange> compress_ranges(std::span<IdRange> id_ranges) {
    std::vector<IdRange> output;

    IdRange latest_range = id_ranges[0];
    for (size_t i = 1; i < id_ranges.size(); ++i) {
        const auto cur_range = id_ranges[i];
        if (cur_range.start > latest_range.end) {
            output.push_back(latest_range);
            latest_range = cur_range;
        } else {
            latest_range = {latest_range.start, std::max(cur_range.end, latest_range.end)};
        }
    }

    output.push_back(latest_range);
    return output;
}

int count_fresh(std::span<IdRange> id_ranges, std::span<long long> product_ids) {
    int fresh = 0;
    size_t i = 0, j = 0;
    while (i < id_ranges.size() && j < product_ids.size()) {
        const auto range = id_ranges[i];
        const auto id = product_ids[j];

        if (range.start <= id && id <= range.end) {
            fresh++;
            j++;
        } else if (id < range.start) {
            j++;
        } else {
            i++;
        }
    }
    return fresh;
}

long long solve_part1(std::string_view contents) {
    auto all_lines = aoc::lines(contents);
    std::vector<IdRange> id_ranges = all_lines
        | std::views::take_while([](auto line){ return !line.empty(); })
        | std::views::transform([](auto sv) { return parse_range(sv); })
        | std::ranges::to<std::vector>();

    std::vector<long long> product_ids = all_lines
        | std::views::drop_while([](auto line){ return !line.empty(); })
        | std::views::drop(1)
        | std::views::transform([](auto sv) { return aoc::to_ll(sv); })
        | std::ranges::to<std::vector>();

    std::ranges::sort(id_ranges);
    std::ranges::sort(product_ids);

    auto compressed_ranges = compress_ranges(id_ranges);
    return count_fresh(compressed_ranges, product_ids);
}

long long solve_part2(std::string_view contents) {
    auto all_lines = aoc::lines(contents);
    std::vector<IdRange> id_ranges = all_lines
        | std::views::take_while([](auto line){ return !line.empty(); })
        | std::views::transform([](auto sv) { return parse_range(sv); })
        | std::ranges::to<std::vector>();

    std::ranges::sort(id_ranges);
    auto compressed_ranges = compress_ranges(id_ranges);
    auto counts = compressed_ranges
        | std::views::transform([](IdRange range) { return range.end - range.start + 1; });

    return std::ranges::fold_left(counts, 0, std::plus{});
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", solve_part2(file_contents));
}
