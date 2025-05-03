/* ----------------------------------------------------------------<Header>-
 Name: graph.cc
 Title: Graph implementation for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Implements a grid-based undirected graph for connectivity checks.
 ------------------------------------------------------------------</Header>-*/

#include "../logic_headers/graph.h"

/* ---------------------------------------------------------------------[<]-
 Function: Graph::Graph
 Synopsis: Constructor. Initializes dimensions.
 ---------------------------------------------------------------------[>]-*/
Graph::Graph(int width, int height) : width(width), height(height) {}

/* ---------------------------------------------------------------------[<]-
 Function: Graph::encode
 Synopsis: Converts 2D coordinates into a 1D index.
 ---------------------------------------------------------------------[>]-*/
int Graph::encode(int x, int y) const {
    return y * width + x;
}

/* ---------------------------------------------------------------------[<]-
 Function: Graph::add_edge
 Synopsis: Adds an undirected edge between two cells.
 ---------------------------------------------------------------------[>]-*/
void Graph::add_edge(int from_x, int from_y, int to_x, int to_y) {
    int a = encode(from_x, from_y);
    int b = encode(to_x, to_y);
    adjacency[a].insert(b);
    adjacency[b].insert(a);
}

/* ---------------------------------------------------------------------[<]-
 Function: Graph::remove_edge
 Synopsis: Removes an undirected edge between two cells.
 ---------------------------------------------------------------------[>]-*/
void Graph::remove_edge(int from_x, int from_y, int to_x, int to_y) {
    int a = encode(from_x, from_y);
    int b = encode(to_x, to_y);
    adjacency[a].erase(b);
    adjacency[b].erase(a);
}

/* ---------------------------------------------------------------------[<]-
 Function: Graph::has_edge
 Synopsis: Checks if an undirected edge exists between two cells.
 ---------------------------------------------------------------------[>]-*/
bool Graph::has_edge(int from_x, int from_y, int to_x, int to_y) const {
    int a = encode(from_x, from_y);
    int b = encode(to_x, to_y);
    auto it = adjacency.find(a);
    return it != adjacency.end() && it->second.count(b);
}

/* ---------------------------------------------------------------------[<]-
 Function: Graph::dfs
 Synopsis: Depth-first search traversal from a node.
 ---------------------------------------------------------------------[>]-*/
void Graph::dfs(int current, std::unordered_set<int> &visited) const {
    visited.insert(current);
    if (adjacency.find(current) == adjacency.end()) {
        return;
    }
    for (int neighbor : adjacency.at(current)) {
        if (!visited.count(neighbor)) {
            dfs(neighbor, visited);
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Graph::is_connected_to_start
 Synopsis: Checks whether all connected nodes are reachable from start.
 ---------------------------------------------------------------------[>]-*/
bool Graph::is_connected_to_start(int start_x, int start_y) {
    std::unordered_set<int> visited;
    int start = encode(start_x, start_y);
    dfs(start, visited);

    for (const auto &pair : adjacency) {
        if (!visited.count(pair.first)) {
            return false;
        }
    }
    return true;
}

/* ---------------------------------------------------------------------[<]-
 Function: Graph::is_single_cycle
 Synopsis: Checks whether the current graph forms a single simple cycle.
 ---------------------------------------------------------------------[>]-*/
bool Graph::is_single_cycle() const {
    // Перевірка: кожна вершина має ступінь рівно 2
    for (const auto& [node, neighbors] : adjacency) {
        if (neighbors.size() != 2)
            return false;
    }

    // DFS для перевірки, що всі зв’язані (один компонент)
    std::unordered_set<int> visited;
    if (adjacency.empty())
        return false;

    int start = adjacency.begin()->first;
    dfs(start, visited);

    // Перевірка: всі вершини з ребрами були відвідані
    return visited.size() == adjacency.size();
}
