#include "Graph.h"

Graph::Graph(uint32_t n)  {
    size = n;
    adj_list.resize(n);
}

Graph Graph::generateFullGraph(uint32_t n)  {
    Graph graph(n);
    for (uint32_t i = 0; i < n - 1; ++i) {
        for (uint32_t j = i + 1; j < n; ++j) {
            uint32_t val = rand() % 10 + 1;
            graph.adj_list[i].emplace_back(j, val);
            graph.adj_list[j].emplace_back(i, val);
        }
    }
    graph.edges = n * (n - 1) / 2;
    return graph;
}

Graph Graph::getTree(uint32_t n)  {
    vector<uint32_t> used_vertices;
    used_vertices.reserve(n);

    Graph graph(n);
    used_vertices.push_back(0);
    for (uint32_t i = 1; i < n; ++i) {
        uint32_t parent = used_vertices[rand() % used_vertices.size()];
        uint32_t weight = rand() % 10 + 1;
        graph.adj_list[i].emplace_back(parent, weight);
        graph.adj_list[parent].emplace_back(i, weight);
        used_vertices.push_back(i);
    }

    graph.edges = n - 1;

    return graph;
}

Graph Graph::complement(Graph tree) {
    double divider = static_cast<double>(tree.size) * (tree.size - 1) / 2;

    while (tree.edges / divider < 0.4) {
        uint32_t a = rand() % tree.size, b = rand() % tree.size;
        if (a != b && std::find_if(tree.adj_list[a].begin(), tree.adj_list[a].end(),
                         [b](const pair<uint32_t, uint32_t>& p){ return p.first == b;}) ==
            tree.adj_list[a].end()) {
            ++tree.edges;
            uint32_t weight = rand() % 10 + 1;
            tree.adj_list[a].emplace_back(b, weight);
            tree.adj_list[b].emplace_back(a, weight);
        }
    }

    return tree;
}