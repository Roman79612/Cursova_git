/* ----------------------------------------------------------------<Header>-
 Name: graph.h
 Title: Helper for Rules of Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-07
 Revised: 2025-05-14
 Description: Header file for validation logic in Masyu puzzle.
 ------------------------------------------------------------------</Header>-*/
#ifndef GRAPH_H
#define GRAPH_H

#include "../core_headers/field.h"
#include "../core_headers/cell.h"
#include "../core_headers/direction.h"
#include "../utils/ui.h"
#include <map>

enum class EdgeState { UNKNOWN, YES, NO };

class Graph {
public:
    //constructor
    Graph(Field& field);

    //public methods
    void add_edge(Cell& a, Cell& b);
    void remove_edge(Cell& a, Cell& b);
    bool is_connected(const Cell& a, const Cell& b);
    Cell& get_neighbor(Cell& cell, Direction dir);
    void set_edge(Cell& a, Cell& b, EdgeState state);
    EdgeState get_state(Cell& a, Cell& b) const;
private:
    Field& field;
    std::map<std::pair<Cell*, Cell*>, EdgeState> edge_matrix;
};

#endif // GRAPH_H
