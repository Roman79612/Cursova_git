/* ----------------------------------------------------------------<Header>-
 Name: rules.cc
 Title: Rules implementation for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Implements edge and pattern rules for Masyu puzzle solving.
 ------------------------------------------------------------------</Header>-*/

#include "../logic_headers/rules.h"

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_white_edge_rule
 Synopsis: Applies the white edge rule.
 ---------------------------------------------------------------------[>]-*/
void Rules::apply_white_edge_rule(Field& field, int x, int y) {
    // Check if the cell is a white dot
    if (field.get_cell(x, y).get_type() == CellType::WHITE) {
        // Check the surrounding cells for line direction
        int line_count = 0;
        for (Direction dir : {Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT}) {
            int nx = x + DirectionHelper::get_dx(dir);
            int ny = y + DirectionHelper::get_dy(dir);
            if (field.in_bounds(nx, ny) && field.get_cell(nx, ny).get_type() == CellType::LINE) {
                line_count++;
            }
        }
        // Apply the rule: must have exactly two lines entering the cell
        if (line_count != 2) {
            // Mark the cell as invalid or take appropriate action
        }
    }
}
/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_black_edge_rule
 Synopsis: Applies the black edge rule.
 ---------------------------------------------------------------------[>]-*/
void Rules::apply_black_edge_rule(Field& field, int x, int y) {
    // Check if the cell is a black dot
    if (field.get_cell(x, y).get_type() == CellType::BLACK) {
        // Check the surrounding cells for line direction
        int line_count = 0;
        for (Direction dir : {Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT}) {
            int nx = x + DirectionHelper::get_dx(dir);
            int ny = y + DirectionHelper::get_dy(dir);
            if (field.in_bounds(nx, ny) && field.get_cell(nx, ny).get_type() == CellType::LINE) {
                line_count++;
            }
        }
        // Apply the rule: must have exactly one line entering the cell
        if (line_count != 1) {
            // Mark the cell as invalid or take appropriate action
        }
    }
}

/* ---------------------------------------------------------------------[<]-
Function: Rules::apply_white_pair_rule
Synopsis: Applies the white pair rule.
---------------------------------------------------------------------[>]-*/
void Rules::apply_white_pair_rule(Field& field, int x, int y) {
    // Check if the cell is a white dot
    if (field.get_cell(x, y).get_type() == CellType::WHITE) {
        // Check the surrounding cells for line direction
        int line_count = 0;
        for (Direction dir : {Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT}) {
            int nx = x + DirectionHelper::get_dx(dir);
            int ny = y + DirectionHelper::get_dy(dir);
            if (field.in_bounds(nx, ny) && field.get_cell(nx, ny).get_type() == CellType::LINE) {
                line_count++;
            }
        }
        // Apply the rule: must have exactly two lines entering the cell
        if (line_count != 2) {
            // Mark the cell as invalid or take appropriate action
        }
    }
}

/* ---------------------------------------------------------------------[<]-
Function: Rules::apply_white_triplet_rule
Synopsis: Applies the white triplet rule.
---------------------------------------------------------------------[>]-*/
void Rules::apply_white_triplet_rule(Field& field, int x, int y) {
    // Check if the cell is a white dot
    if (field.get_cell(x, y).get_type() == CellType::WHITE) {
        // Check the surrounding cells for line direction
        int line_count = 0;
        for (Direction dir : {Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT}) {
            int nx = x + DirectionHelper::get_dx(dir);
            int ny = y + DirectionHelper::get_dy(dir);
            if (field.in_bounds(nx, ny) && field.get_cell(nx, ny).get_type() == CellType::LINE) {
                line_count++;
            }
        }
        // Apply the rule: must have exactly three lines entering the cell
        if (line_count != 3) {
            // Mark the cell as invalid or take appropriate action
        }
    }
}

/* ---------------------------------------------------------------------[<]-
Function: Rules::apply_black_pair_rule
Synopsis: Applies the black pair rule.
---------------------------------------------------------------------[>]-*/
void Rules::apply_black_pair_rule(Field& field, int x, int y) {
    // Check if the cell is a black dot
    if (field.get_cell(x, y).get_type() == CellType::BLACK) {
        // Check the surrounding cells for line direction
        int line_count = 0;
        for (Direction dir : {Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT}) {
            int nx = x + DirectionHelper::get_dx(dir);
            int ny = y + DirectionHelper::get_dy(dir);
            if (field.in_bounds(nx, ny) && field.get_cell(nx, ny).get_type() == CellType::LINE) {
                line_count++;
            }
        }
        // Apply the rule: must have exactly two lines entering the cell
        if (line_count != 2) {
            // Mark the cell as invalid or take appropriate action
        }
    }
}

/* ---------------------------------------------------------------------[<]-
Function: Rules::apply_black_white_diagonal_rule
Synopsis: Applies the black and white diagonal rule.
---------------------------------------------------------------------[>]-*/
void Rules::apply_black_white_diagonal_rule(Field& field, int x, int y) {
    // Check if the cell is a black dot
    if (field.get_cell(x, y).get_type() == CellType::BLACK) {
        // Check the surrounding cells for line direction
        int line_count = 0;
        for (Direction dir : {Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT}) {
            int nx = x + DirectionHelper::get_dx(dir);
            int ny = y + DirectionHelper::get_dy(dir);
            if (field.in_bounds(nx, ny) && field.get_cell(nx, ny).get_type() == CellType::LINE) {
                line_count++;
            }
        }
        // Apply the rule: must have exactly one line entering the cell
        if (line_count != 1) {
            // Mark the cell as invalid or take appropriate action
        }
    }
}
