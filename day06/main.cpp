#include <filesystem>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

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
    return sv
        | std::views::split('\n')
        | std::views::transform([](auto seq) { return std::string_view{seq}; });
}

[[nodiscard]] constexpr auto words(std::string_view sv) {
    return sv
        | std::views::split(' ')
        | std::views::filter([](auto seq) { return !seq.empty(); })
        | std::views::transform([](auto seq) { return std::string_view{seq}; });
}

[[nodiscard]] std::optional<long long> to_num(std::string_view sv)
{
    long long r;
    auto result = std::from_chars(sv.data(), sv.data() + sv.size(), r);
    return result.ec == std::errc() ? std::optional{r} : std::nullopt;
}

long long solve(std::string_view contents) {
    const std::vector<std::string_view> rows =
        lines(contents) | std::ranges::to<std::vector>();

    std::vector<std::vector<long long>> numbers = rows
        | std::views::take(rows.size() - 1)
        | std::views::transform([](std::string_view sv) {
           return words(sv)
               | std::views::transform([](auto sv) { return to_num(sv).value(); })
               | std::ranges::to<std::vector>();
        })
        | std::ranges::to<std::vector>();

    std::vector<std::string_view> operations = words(rows.back())
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
    if (argc < 2) {
        std::println("Usage: program <filepath>");
        return 1;
    }

    std::filesystem::path file_path = argv[1];
    auto file_contents = read_file(file_path);

    std::println("{}", solve(file_contents));
}
