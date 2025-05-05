/* ----------------------------------------------------------------<Header>-
 Name: rules.h
 Title: Rules class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Header file for rule validation logic in Masyu puzzle.
 ------------------------------------------------------------------</Header>-*/

#ifndef RULES_H
#define RULES_H

#include "../core_headers/field.h"
#include "../core_headers/cell.h"
#include "../core_headers/direction.h"

namespace Rules {
    // Applies the white edge rule
    void apply_white_edge_rule(Field& field, int x, int y);

    // Applies the black edge rule
    void apply_black_edge_rule(Field& field, int x, int y);

    // Applies the white pair rule
    void apply_white_pair_rule(Field& field, int x, int y);

    // Applies the white triplet rule
    void apply_white_triplet_rule(Field& field, int x, int y);

    // Applies the black pair rule
    void apply_black_pair_rule(Field& field, int x, int y);

    // Applies the black and white diagonal rule
    void apply_black_white_diagonal_rule(Field& field, int x, int y);
}

#endif // RULES_H
