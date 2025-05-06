/* ----------------------------------------------------------------<Header>-
 Name: rules.h
 Title: Rules header for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-06
 Description: Header file for rule validation logic in Masyu puzzle.
 ------------------------------------------------------------------</Header>-*/

#ifndef RULES_H
#define RULES_H

#include "../core_headers/field.h"
#include "../core_headers/cell.h"
#include "../core_headers/direction.h"

namespace Rules {
    void apply_corner_rule(Field& field);
    void force_straight_path(Field& field, int x, int y, Direction dir);
    void apply_white_edge_rule(Field& field);
    void apply_black_edge_rule(Field& field);
    /*
    void apply_white_pair_rule(Field& field, int x, int y);
    void apply_white_triplet_rule(Field& field, int x, int y);
    void apply_black_pair_rule(Field& field, int x, int y);
    void apply_black_white_diagonal_rule(Field& field, int x, int y);
    */
}

#endif // RULES_H
