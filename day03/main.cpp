// std includes
#include <unordered_map>

// local
#include <aoc_common.hpp>

int to_digit(char c) { return c - '0'; }

int max_joltage1(std::string_view bank) {
    int max = 0;

    for (size_t i = 0; i < bank.size() - 1; ++i) {
        for (size_t j = i + 1; j < bank.size(); ++j) {
            int joltage = to_digit(bank[i]) * 10 + to_digit(bank[j]);
            if (max < joltage) max = joltage;
        }
    }

    return max;
}

long long max_joltage2(std::string_view bank, size_t start, size_t len, long long acc) {
    if (len == 0) return acc;

    size_t max_digit_pos = 0;
    int max_digit = 0;

    for (size_t i = start; i < bank.size() - len + 1; ++i) {
        int digit = to_digit(bank[i]);
        if (digit > max_digit) {
            max_digit_pos = i;
            max_digit = digit;
        }
    }

    return max_joltage2(bank, max_digit_pos + 1, len - 1, acc * 10 + max_digit);
}

long long solve(std::string_view contents) {
    long long sum = 0;

    for (auto line : aoc::lines(contents)) {
        sum += max_joltage2(line, 0, 12, 0);;
    }

    return sum;
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", solve(file_contents));
}
