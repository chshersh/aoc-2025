// std includes
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>

// local
#include <aoc_common.hpp>

struct Point3D {
    long long x, y, z;
};

long long distance(Point3D a, Point3D b) {
    const auto dx = a.x - b.x;
    const auto dy = a.y - b.y;
    const auto dz = a.z - b.z;
    return dx*dx + dy*dy + dz*dz;
}

struct Edge {
    size_t from, to;
    long long len;
};

constexpr auto parse_line = [](std::string_view line) -> Point3D {
    auto parts = line
        | std::views::split(',')
        | std::views::transform([](auto&& rng) {
            return aoc::to_ll(std::string_view{rng});
        })
        | std::ranges::to<std::vector<int>>();

    return { parts[0], parts[1], parts[2] };
};

struct DSU {
    explicit DSU(size_t cnt) : size(cnt, 1) {
        parent = std::views::iota(0u, cnt) | std::ranges::to<std::vector<size_t>>();
    }

    size_t get(size_t n) {
        if (parent[n] != n) parent[n] = get(parent[n]);
        return parent[n];
    }

    void combine(size_t a, size_t b) {
        auto par_a = get(a);
        auto par_b = get(b);
        if (par_a == par_b) return;
        if (size[par_a] > size[par_b]) std::swap(par_a, par_b);
        // Invariant: size[par_a] <= size[par_b]
        parent[par_a] = par_b;
        size[par_b] += size[par_a];
    }

    int get_size(size_t i) { return size[get(i)]; }

private:
    std::vector<size_t> parent;
    std::vector<int> size;
};

long long connect_closest(
    std::span<const Edge> edges,
    size_t total_coords,
    int limit
) {
    DSU dsu{total_coords};

    for (int i = 0; i < limit; ++i) {
        Edge edge = edges[i];
        dsu.combine(edge.from, edge.to);
    }

    std::unordered_map<size_t, int> components;
    for (size_t i = 0; i < total_coords; ++i) {
        components[dsu.get(i)] = dsu.get_size(i);
    }

    auto sizes = components
        | std::views::values
        | std::ranges::to<std::vector>();

    std::ranges::sort(sizes, std::greater{});
    return sizes[0] * sizes[1] * sizes[2];
}

long long solve(std::string_view contents) {
    auto coordinates =
        aoc::lines(contents)
        | std::views::transform(parse_line)
        | std::ranges::to<std::vector<Point3D>>();

    std::vector<Edge> edges;
    edges.reserve(coordinates.size() * (coordinates.size() - 1) / 2);

    for (size_t from = 0; from < coordinates.size() - 1; ++from) {
        auto p_from = coordinates[from];
        for (size_t to = from + 1; to < coordinates.size(); ++to) {
            auto p_to = coordinates[to];
            long long len = distance(p_from, p_to);
            edges.emplace_back(from, to, len);
        }
    }

    std::ranges::sort(edges, std::less{}, &Edge::len);
    return connect_closest(edges, coordinates.size(), 1000);
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
    std::println("{}", solve(file_contents));
}
