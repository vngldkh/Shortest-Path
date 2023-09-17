#ifndef TASK_3_SEARCHALGORITHMS_H
#define TASK_3_SEARCHALGORITHMS_H

#include "../Graph/Graph.h"

pair<uint64_t, std::chrono::nanoseconds> dijkstra(const Graph&, uint32_t, uint32_t);
pair<uint64_t, std::chrono::nanoseconds> floydWarshall(const Graph&, uint32_t, uint32_t);
pair<uint64_t, std::chrono::nanoseconds> bellmanFord(const Graph&, uint32_t, uint32_t);
pair<uint64_t, std::chrono::nanoseconds> danzig(const Graph&, uint32_t, uint32_t);

#endif //TASK_3_SEARCHALGORITHMS_H
