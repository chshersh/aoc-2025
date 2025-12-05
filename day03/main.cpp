#include <filesystem>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>

std::string read_file(const std::filesystem::path& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Cannot open file: " + path.string());
    }
    std::ostringstream s;
    s << in.rdbuf();
    return s.str();
}

[[nodiscard]] constexpr auto lines(std::string_view sv) {
    // Remove trailing '\n'
    while (!sv.empty() && sv.back() == '\n') sv.remove_suffix(1);
    return sv | std::views::split('\n');
}


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

    for (auto line : lines(contents)) {
        sum += max_joltage2(std::string_view{line}, 0, 12, 0);;
    }

    return sum;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::println("Usage: program <filepath>");
        return 1;
    }

    std::filesystem::path file_path = argv[1];
    auto file_contents = read_file(file_path);

    std::println("{}", solve(file_contents));
}
