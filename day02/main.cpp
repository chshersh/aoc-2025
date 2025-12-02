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

[[nodiscard]] std::optional<long long> to_int(std::string_view sv)
{
    long long r;
    auto result = std::from_chars(sv.data(), sv.data() + sv.size(), r);
    return result.ec == std::errc() ? std::optional{r} : std::nullopt;
}

long long pow10(int n) {
    long long res = 1;
    for (int i = 0; i < n; ++i) res *= 10;
    return res;
}

long long sum_invalid_ids(std::string_view range) {
    const auto delim_pos = range.find_first_of('-');
    const auto range_start_str = range.substr(0, delim_pos);
    const auto range_end_str   = range.substr(delim_pos + 1);

    const auto range_start = to_int(range_start_str).value();
    const auto range_end   = to_int(range_end_str).value();

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

long long add_invalid(std::string_view contents) {
    long long sum = 0;

    for (const auto line : lines(contents)) {
        for (const auto range : line | std::views::split(',')) {
            sum += sum_invalid_ids(std::string_view{range});
        }
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

    std::println("{}", add_invalid(file_contents));
}
