#include "SearchAlgorithms.h"

pair<uint64_t, std::chrono::nanoseconds> bellmanFord(const Graph& graph, uint32_t a, uint32_t b) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<uint64_t> weights(graph.size, UINT32_MAX);
    weights[a] = 0;
    bool flag;
    for (uint64_t k = 0; k < graph.size - 1; ++k) {
        flag = false;
        for (uint32_t i = 0; i < graph.size; ++i) {
            for (const auto& edge : graph.adj_list[i]) {
                if (weights[i] == UINT32_MAX) {
                    continue;
                }

                if (weights[i] + edge.second < weights[edge.first]) {
                    weights[edge.first] = weights[i] + edge.second;
                    flag = true;
                }
            }
        }
        if (!flag) {
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    return {weights[b], end - begin};
}