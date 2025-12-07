// std includes
#include <unordered_map>

// local
#include <aoc_common.hpp>

long long pow10(int n) {
    long long res = 1;
    for (int i = 0; i < n; ++i) res *= 10;
    return res;
}

long long sum_invalid_ids(std::string_view range) {
    const auto delim_pos = range.find_first_of('-');
    const auto range_start_str = range.substr(0, delim_pos);
    const auto range_end_str   = range.substr(delim_pos + 1);

    const auto range_start = aoc::to_ll(range_start_str);
    const auto range_end   = aoc::to_ll(range_end_str);

    int start_half_size = range_start_str.size() / 2;
    int end_half_size   = range_end_str.size() / 2;
    if (range_start_str.size() % 2 == 1) start_half_size++;

    long long sum = 0;

    for (int half_size = start_half_size; half_size <= end_half_size; ++half_size) {
        const auto half_mul = pow10(half_size);
        auto cur_half = half_mul / 10;

        while (true) {
            const long long cur = cur_half + half_mul * cur_half;
            if (cur_half >= half_mul || cur > range_end) break;
            cur_half++;
            if (cur < range_start) continue;
            sum += cur;
        }
    }

    return sum;
}

bool is_invalid(long long n) {
    auto id = std::to_string(n);

    for (size_t i = 1; i <= id.size() / 2; ++i) {
        if (id.size() % i == 0) {
            auto part = std::string_view{id}.substr(0, i);

            bool is_repeated = true;
            for (size_t j = i; j < id.size() && is_repeated; j += i) {
                auto cur_part = std::string_view{id}.substr(j, i);
                is_repeated &= part == cur_part;
            }

            if (is_repeated) return true;
        }
    }

    return false;

}

long long sum_invalid_ids2(std::string_view range) {
    const auto delim_pos = range.find_first_of('-');
    const auto range_start_str = range.substr(0, delim_pos);
    const auto range_end_str   = range.substr(delim_pos + 1);

    const auto range_start = aoc::to_ll(range_start_str);
    const auto range_end   = aoc::to_ll(range_end_str);

    long long sum = 0;

    for (long long n = range_start; n <= range_end; ++n) {
        if (is_invalid(n)) sum += n;
    }

    return sum;
}

long long add_invalid(std::string_view contents) {
    long long sum = 0;

    for (auto line : aoc::lines(contents)) {
        for (auto range : line | std::views::split(',')) {
            sum += sum_invalid_ids2(std::string_view{range});
        }
    }

    return sum;
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", add_invalid(file_contents));
}
