// std headers
#include <string_view>

// local
#include <aoc_common.hpp>

long long rotate(long long& cur_pos, std::string_view combination) {
    char direction = combination[0];
    auto rotation = aoc::to_ll(combination.substr(1));

    long long cnt = 0;
    auto tick = [&cnt, &cur_pos, rotation](long long direction) {
        for (long long i = 0; i < rotation; ++i) {
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

long long count_zero_rotations(std::string_view sequences) {
    auto combinations = aoc::lines(sequences);
    long long cnt = 0;
    long long cur_pos = 50;

    for (auto combination : combinations) {
        cnt += rotate(cur_pos, combination);
    }

    return cnt;
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", count_zero_rotations(file_contents));
}
