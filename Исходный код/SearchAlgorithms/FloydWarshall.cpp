#include "SearchAlgorithms.h"

pair<uint64_t, std::chrono::nanoseconds> floydWarshall(const Graph& graph, uint32_t a, uint32_t b) {
    std::vector<std::vector<uint64_t>> d(graph.size, std::vector<uint64_t>(graph.size, UINT32_MAX));
    for (uint32_t i = 0; i < graph.size; ++i) {
        d[i][i] = 0;
    }
    for (uint32_t i = 0; i < graph.size; ++i) {
        for (const auto& e : graph.adj_list[i]) {
            d[i][e.first] = e.second;
            d[e.first][i] = e.second;
        }
    }

    auto begin = std::chrono::high_resolution_clock::now();
    for (uint32_t k = 0; k < graph.size; ++k) {
        for (uint32_t i = 0; i < graph.size; ++i) {
            for (uint32_t j = 0; j < graph.size; ++j) {
                if (d[i][k] == UINT32_MAX || d[k][j] == UINT32_MAX) {
                    continue;
                }
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    return {d[a][b], end - begin};
}