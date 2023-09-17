#include "SearchAlgorithms.h"

pair<uint64_t, std::chrono::nanoseconds> danzig(const Graph& graph, uint32_t a, uint32_t b) {
    // Получение матрицы смежности (не учитывается при замере времени, т.к. это форма представления графа)
    vector<vector<uint64_t>> d0(graph.size, vector<uint64_t>(graph.size, UINT32_MAX));
    for (uint32_t i = 0; i < graph.size; ++i) {
        d0[i][i] = 0;
    }
    for (uint32_t i = 0; i < graph.size; ++i) {
        for (const auto& e : graph.adj_list[i]) {
            d0[i][e.first] = e.second;
        }
    }

    auto begin = std::chrono::high_resolution_clock::now();
    vector<vector<uint64_t>> d_last(1, vector<uint64_t>(1, d0[0][0]));
    for (uint32_t m = 2; m <= graph.size; ++m)  {
        vector<vector<uint64_t>> d_new(m, vector<uint64_t>(m, UINT32_MAX));
        for (uint32_t i = 0; i < m - 1; ++i) {
            d_new[i][i] = 0;
            for (uint32_t j = 0; j < m - 1; ++j) {
                d_new[m - 1][j] = std::min(d_new[m - 1][j], d0[m - 1][i] + d_last[i][j]);
                d_new[i][m - 1] = std::min(d_new[i][m - 1], d0[j][m - 1] + d_last[i][j]);
            }
        }
        d_new[m - 1][m - 1] = 0;
        for (uint32_t i = 0; i < m - 1; ++i) {
            for (uint32_t j = 0; j < m - 1; ++j) {
                d_new[i][j] = std::min(d_new[i][m - 1] + d_new[m - 1][j], d_last[i][j]);
            }
        }
        std::swap(d_last, d_new);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return {d_last[a][b], end - begin};
}
