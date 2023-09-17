#include <iostream>
#include "Graph/Graph.h"
#include "SearchAlgorithms/SearchAlgorithms.h"
#include <fstream>

int main() {
    srand(time(nullptr));

    std::string names[] = {"Dijkstra", "FloydWarshall", "BellmanFord", "Danzig"};
    pair<uint64_t, std::chrono::nanoseconds> (*funcs[])(const Graph&, uint32_t, uint32_t) = { dijkstra, floydWarshall, bellmanFord, danzig};

    std::ofstream ofs[] = {std::ofstream("complete.csv"), std::ofstream("connected.csv"), std::ofstream("spare.csv")};

    for (auto& of : ofs) {
        of << "Vertecies;Edges;";
        for (const auto& name : names) {
            of << name << ";";
        }
        of << "\n";
    }

    for (uint32_t v_count = 10; v_count <= 1010; v_count += 50) {
        std::vector<std::vector<uint64_t>> totals(3, std::vector<uint64_t>(4, 0));
        Graph tree = Graph::getTree(v_count);
        Graph graphs[] = {Graph::generateFullGraph(v_count), Graph::complement(tree), tree};
        uint64_t e_count[] = {graphs[0].edges, graphs[1].edges, graphs[2].edges};

        for (uint32_t test = 0; test < 5; ++test) {
            uint32_t a = rand() % v_count, b = rand() % v_count;

            for (uint32_t graph_no = 0; graph_no < 3; ++graph_no) {
                for (uint32_t f = 0; f < 4; ++f) {
                    auto res = funcs[f](graphs[graph_no], a, b);
                    totals[graph_no][f] += res.second.count() / 5;
                }
            }
        }
        for (uint32_t i = 0; i < 3; ++i) {
            ofs[i] << v_count << ';' << e_count[i] << ';';
            for (const auto& time : totals[i]) {
                ofs[i] << time << ';';
            }
            ofs[i] << '\n';
        }
    }
    for (auto& of : ofs) {
        of.close();
    }
}
