/* ----------------------------------------------------------------<Header>-
 Name: rules.h
 Title: Rules header for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-14
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
    void force_straight(Field& field, Graph& graph, Cell& cell, Direction dir);
    void connect_with_next(Field& field, Graph& graph, Cell& cell, Direction dir);
    void ban(Field& field, Graph& graph, Cell& cell, Direction dir);
    void turn_in_next_cell(Field& field, Graph& graph, Cell& from_cell, Direction move_dir, Direction turn_dir);
    void apply_turn_for_left_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor);
    void apply_turn_for_right_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor);
    void apply_turn_for_top_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor);
    void apply_turn_for_bottom_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor);

    // Pattern rules
    void apply_black_corner_rule(Field& field, Graph& graph);
    void apply_white_edge_rule(Field& field, Graph& graph);
    void apply_black_edge_rule(Field& field, Graph& graph);
    void apply_black_near_border_rule(Field& field, Graph& graph);
    void apply_adjacent_black_rule(Field& field, Graph& graph);
    void apply_adjacent_black_near_edge_rule(Field& field, Graph& graph);
    void apply_white_border_pair_rule(Field& field, Graph& graph);
    void enforce_white_triplets(Field& field, Graph& graph);
    void apply_combination_rule(Field& field, Graph& graph);
}

#endif // RULES_H
