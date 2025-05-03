/* ----------------------------------------------------------------<Header>-
 Name: graph.h
 Title: Graph class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Header file for grid-based undirected graph operations.
 ------------------------------------------------------------------</Header>-*/

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>
#include <unordered_map>

class Graph {
public:
    Graph(int width, int height);

    void add_edge(int from_x, int from_y, int to_x, int to_y);
    void remove_edge(int from_x, int from_y, int to_x, int to_y);
    bool has_edge(int from_x, int from_y, int to_x, int to_y) const;

    bool is_single_cycle() const;
    bool is_connected_to_start(int start_x, int start_y);

private:
    int width;
    int height;

    std::unordered_map<int, std::unordered_set<int>> adjacency;

    int encode(int x, int y) const;
    void dfs(int current, std::unordered_set<int> &visited) const;
};

#endif // GRAPH_H
