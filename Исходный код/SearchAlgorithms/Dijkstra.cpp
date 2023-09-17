#include "SearchAlgorithms.h"
#include <queue>

pair<uint64_t, std::chrono::nanoseconds> dijkstra(const Graph& graph, uint32_t a, uint32_t b) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<uint64_t> nodes(graph.size, UINT32_MAX);

    std::priority_queue<std::pair<uint64_t, uint64_t>> pq;
    nodes[a] = 0;
    pq.emplace(a, 0);

    while (!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        if (node.second > nodes[node.first]) {
            continue;
        }

        for (const auto& edge : graph.adj_list[node.first]) {
            if (edge.second + node.second < nodes[edge.first]) {
                nodes[edge.first] = edge.second + node.second;
                pq.emplace(edge.first, edge.second + node.second);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    return {nodes[b], end - begin};
};