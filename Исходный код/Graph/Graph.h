#ifndef TASK_3_GRAPH_H
#define TASK_3_GRAPH_H
#include <vector>
#include <cstdint>
#include <tuple>
#include <cstdlib>
#include <algorithm>
#include <chrono>

using std::vector;
using std::pair;
using std::tuple;

struct Graph {
    uint32_t size;
    uint64_t edges = 0;
    vector<vector<pair<uint32_t, uint32_t>>> adj_list;

    explicit Graph(uint32_t);

    static Graph generateFullGraph(uint32_t);
    static Graph getTree(uint32_t);
    static Graph complement(Graph);
};


#endif //TASK_3_GRAPH_H
