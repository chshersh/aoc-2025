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

int max_joltage(std::string_view bank) {
    int max = 0;

    constexpr auto to_digit = [](char c) -> int { return c - '0'; };

    for (size_t i = 0; i < bank.size() - 1; ++i) {
        for (size_t j = i + 1; j < bank.size(); ++j) {
            int joltage = to_digit(bank[i]) * 10 + to_digit(bank[j]);
            if (max < joltage) max = joltage;
        }
    }

    return max;
}

int solve_part1(std::string_view contents) {
    int sum = 0;

    for (auto line : lines(contents)) {
        sum += max_joltage(std::string_view{line});

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

    std::println("{}", solve_part1(file_contents));
}
