#include <filesystem>
#include <fstream>
#include <optional>
#include <print>
#include <ranges>
#include <string>
#include <string_view>

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

[[nodiscard]] std::optional<int> to_int(std::string_view sv)
{
    int r;
    auto result = std::from_chars(sv.data(), sv.data() + sv.size(), r);
    if (result.ec == std::errc())
        return r;
    else
        return std::nullopt;
}

int rotate(int& cur_pos, std::string_view combination) {
    char direction = combination[0];
    auto rotation = to_int(combination.substr(1)).value();

    int cnt = 0;
    auto tick = [&cnt, &cur_pos, rotation](int direction) {
        for (int i = 0; i < rotation; ++i) {
            cur_pos = (cur_pos + 100 + direction) % 100;
            if (cur_pos == 0) cnt++;
        }
    };

    switch (direction) {
        case 'L': tick(-1); break;
        case 'R': tick(1); break;
    }

    return cnt;
}

int count_zero_rotations(std::string_view sequences) {
    auto combinations = lines(sequences);
    int cnt = 0;
    int cur_pos = 50;

    for (auto combination : combinations) {
        cnt += rotate(cur_pos, std::string_view{combination});
    }

    return cnt;

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::println("Usage: program <filepath>");
        return 1;
    }

    std::filesystem::path file_path = argv[1];
    auto file_contents = read_file(file_path);

    std::println("{}", count_zero_rotations(file_contents));
}
