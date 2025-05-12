/* ----------------------------------------------------------------<Header>-
 Name: graph.h
 Title: Helper for Rules of Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-07
 Revised: 2025-05-08
 Description: Header file for validation logic in Masyu puzzle.
 ------------------------------------------------------------------</Header>-*/
#ifndef GRAPH_H
#define GRAPH_H

#include "../core_headers/field.h"
#include "../core_headers/cell.h"
#include "../core_headers/direction.h"
#include "../utils/ui.h"
#include <map>
#include <set>
#include <utility>

enum class EdgeState { UNKNOWN, YES, NO };

class Graph {
public:
    Graph(const Field& field);
    Graph(const Graph& other);

    void add_edge(Cell& a, Cell& b);
    void remove_edge(Cell& a, Cell& b);
    bool is_connected(const Cell& a, const Cell& b);
    Cell& get_neighbor(Cell& cell, Direction dir);
    void set_edge(Cell& a, Cell& b, EdgeState state);
    EdgeState get_state(Cell& a, Cell& b) const;
    void dfs_collect(Cell& cell, std::set<Cell*>& visited, std::vector<Cell*>& comp);
    std::vector<std::vector<Cell*>> get_connected_components();
    void dfs_visit(Cell& cell, std::set<Cell*>& visited);
    bool is_valid_path();
    std::vector<std::pair<Cell&, Cell&>> get_all_possible_edges();
    bool can_connect(Cell& a, Cell& b);
    void force_edge(Cell& a, Cell& b);
    void ban_edge(Cell& a, Cell& b);
private:
    Field field;
    std::map<std::pair<Cell*, Cell*>, EdgeState> edge_matrix;
};

#endif // GRAPH_H
