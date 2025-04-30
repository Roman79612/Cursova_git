#include "graph.hpp"

Graph::Graph(int width, int height)
    : width(width), height(height) {}

int Graph::encode(int x, int y) const {
    return y * width + x;
}

void Graph::add_edge(int from_x, int from_y, int to_x, int to_y) {
    int a = encode(from_x, from_y);
    int b = encode(to_x, to_y);
    adjacency[a].insert(b);
    adjacency[b].insert(a);
}

void Graph::remove_edge(int from_x, int from_y, int to_x, int to_y) {
    int a = encode(from_x, from_y);
    int b = encode(to_x, to_y);
    adjacency[a].erase(b);
    adjacency[b].erase(a);
}

bool Graph::has_edge(int from_x, int from_y, int to_x, int to_y) const {
    int a = encode(from_x, from_y);
    int b = encode(to_x, to_y);
    auto it = adjacency.find(a);
    return it != adjacency.end() && it->second.count(b);
}

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

bool Graph::is_connected_to_start(int start_x, int start_y) {
    std::unordered_set<int> visited;
    int start = encode(start_x, start_y);
    dfs(start, visited);
    // якщо всі клітинки, які мають зв’язки, доступні — тоді true
    for (const auto &pair : adjacency) {
        if (!visited.count(pair.first)) {
            return false;
        }
    }
    return true;
}
