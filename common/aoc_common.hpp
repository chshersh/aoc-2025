#pragma once

#include <filesystem>
#include <fstream>
#include <optional>
#include <print>
#include <ranges>
#include <string>
#include <string_view>

namespace aoc {

[[nodiscard]] std::string read_file(const std::filesystem::path& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Cannot open file: " + path.string());
    }
    std::ostringstream s;
    s << in.rdbuf();
    return s.str();
}

[[nodiscard]] std::string read_input_file(int argc, char* argv[]) {
    if (argc < 2) {
        std::println("Usage: program <filepath>");
        std::exit(1);
    }

    std::filesystem::path file_path = argv[1];
    return read_file(file_path);
}

[[nodiscard]] constexpr auto lines(std::string_view sv) {
    // Remove trailing '\n'
    while (!sv.empty() && sv.back() == '\n') sv.remove_suffix(1);
    return sv
        | std::views::split('\n')
        | std::views::transform([](auto seq) { return std::string_view{seq}; });
}

// "123   456 3" -> [123, 456, 3]
[[nodiscard]] constexpr auto words(std::string_view sv) {
    return sv
        | std::views::split(' ')
        | std::views::filter([](auto seq) { return !seq.empty(); })
        | std::views::transform([](auto seq) { return std::string_view{seq}; });
}

[[nodiscard]] std::optional<long long> to_ll_opt(std::string_view sv)
{
    long long r;
    auto result = std::from_chars(sv.data(), sv.data() + sv.size(), r);
    return result.ec == std::errc() ? std::optional{r} : std::nullopt;
}

[[nodiscard]] long long to_ll(std::string_view sv)
{
    return to_ll_opt(sv).value();
}

}
