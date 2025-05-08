/* ----------------------------------------------------------------<Header>-
 Name: rules.h
 Title: Rules header for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-07
 Description: Header file for rule validation logic in Masyu puzzle.
 ------------------------------------------------------------------</Header>-*/

#ifndef RULES_H
#define RULES_H

#include "../core_headers/field.h"
#include "../core_headers/cell.h"
#include "../core_headers/direction.h"
#include "../logic_headers/graph.h"

namespace Rules {
    // Empty field rules
    void apply_corner_rule(Field& field);

    // Helper function to pattern rules
    bool is_on_border(int x, int y, int width, int height);
    bool is_near_border(int x, int y, int width, int height);
    void force_straight_path(Field& field, Graph& graph, Cell& cell, Direction dir);
    void force_through_path(Field& field, Graph& graph, Cell& cell, Direction dir );
    void apply_white_pair_connection(Field& field, Graph& graph, Cell& c1, Cell& c2, Direction dir);

    // Pattern rules
    void apply_black_corner_rule(Field& field, Graph& graph);
    void apply_white_edge_rule(Field& field, Graph& graph);
    void apply_black_edge_rule(Field& field, Graph& graph);
    void apply_black_near_border_rule(Field& field, Graph& graph);
    void apply_adjacent_black_rule(Field& field, Graph& graph);
    void apply_adjacent_black_near_edge_rule(Field& field, Graph& graph);
    void apply_white_border_pair_rule(Field& field, Graph& graph);
    void enforce_white_triplets(Field& field, Graph& graph);
}

#endif // RULES_H
