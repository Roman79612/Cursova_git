/* ----------------------------------------------------------------<Header>-
 Name: solver.cc
 Title: Solver class implementation for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-03
 Revised: 2025-05-03
 Description: Implementation of the solver for Masyu puzzle using logical rules.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/field.h"
#include "../core_headers/path.h"
#include "../logic_headers/state.h"
#include "../logic_headers/solver.h"
#include <queue>
#include <stack>
#include <iostream>

/* ---------------------------------------------------------------------[<]-
 Function: Solver
 Synopsis: Constructor for Solver class. Initializes with a field.
 ---------------------------------------------------------------------[>]-*/
Solver::Solver(Field& field) : field(field), current_state(field.clone()) {}

/* ---------------------------------------------------------------------[<]-
 Function: solve
 Synopsis: Solves the puzzle using logical rules and backtracking.
 ---------------------------------------------------------------------[>]-*/
bool Solver::solve() {
    // Start the solving process, exploring the puzzle grid
    for (int y = 0; y < field.get_height(); ++y) {
        for (int x = 0; x < field.get_width(); ++x) {
            // Skip already solved or invalid cells
            if (!is_valid_move(x, y)) continue;
            if (!find_path(x, y)) {
                std::cerr << "Failed to solve the puzzle.\n";
                return false;
            }
        }
    }

    // Check if puzzle is solved
    return is_solved();
}

/* ---------------------------------------------------------------------[<]-
 Function: get_current_state
 Synopsis: Returns the current state of the puzzle.
 ---------------------------------------------------------------------[>]-*/
State Solver::get_current_state() const {
    return current_state;
}

/* ---------------------------------------------------------------------[<]-
 Function: find_path
 Synopsis: Tries to find a valid path starting from the given cell (x, y).
 ---------------------------------------------------------------------[>]-*/
bool Solver::find_path(int x, int y) {
    // Create a stack to backtrack the path
    std::stack<std::pair<int, int>> path_stack;
    path_stack.push({x, y});

    while (!path_stack.empty()) {
        auto [cur_x, cur_y] = path_stack.top();
        path_stack.pop();

        // Apply the rules to check if the move is valid
        if (apply_rules(cur_x, cur_y)) {
            current_state.add_to_path(cur_x, cur_y);
        }

        // Explore neighbors
        auto neighbors = field.get_neighbors(cur_x, cur_y);
        for (auto& neighbor : neighbors) {
            if (is_valid_move(neighbor.first, neighbor.second)) {
                path_stack.push(neighbor);
            }
        }
    }

    return true;
}

/* ---------------------------------------------------------------------[<]-
 Function: apply_rules
 Synopsis: Applies Masyu's logical rules (circle and line constraints).
 ---------------------------------------------------------------------[>]-*/
bool Solver::apply_rules(int x, int y) {
    // Example: Check if the current cell has a circle and apply its rule
    Cell current_cell = field.get_cell(x, y);
    if (current_cell.is_circle()) {
        // Apply specific rules for a circle
        if (!current_cell.satisfy_circle_rule()) {
            return false; // Invalid path, backtrack
        }
    }

    // Apply other rules for lines (if necessary)
    return true;
}

/* ---------------------------------------------------------------------[<]-
 Function: is_valid_move
 Synopsis: Checks if moving to the specified cell is a valid move.
 ---------------------------------------------------------------------[>]-*/
bool Solver::is_valid_move(int x, int y) {
    if (!field.in_bounds(x, y)) return false;
    // Check if the cell is empty or contains a valid state for solving
    Cell cell = field.get_cell(x, y);
    return cell.is_empty() || cell.is_circle(); // Allow empty or circle cells for now
}

/* ---------------------------------------------------------------------[<]-
 Function: is_solved
 Synopsis: Checks if the puzzle is solved (based on specific conditions).
 ---------------------------------------------------------------------[>]-*/
bool Solver::is_solved() const {
    // Puzzle is solved if all cells are correctly filled (this is a basic check)
    for (int y = 0; y < field.get_height(); ++y) {
        for (int x = 0; x < field.get_width(); ++x) {
            Cell cell = field.get_cell(x, y);
            if (!cell.is_filled()) return false;
        }
    }

    // If all cells are filled according to the rules, the puzzle is solved
    return true;
}