/* ----------------------------------------------------------------<Header>-
 Name: solver.h
 Title: Solver class definition for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-03
 Revised: 2025-05-03
 Description: Header file for solving the Masyu puzzle using logical rules.
 ------------------------------------------------------------------</Header>-*/

#ifndef SOLVER_H
#define SOLVER_H

#include "../core_headers/field.h"
#include "../core_headers/path.h"
#include "../logic_headers/state.h"

class Solver {
public:
    Solver(Field& field);

    bool solve();

    State get_current_state() const;

private:
    Field& field;
    State current_state;

    bool find_path(int x, int y);
    bool apply_rules(int x, int y);
    bool is_valid_move(int x, int y);
    bool is_solved() const;
};

#endif // SOLVER_H
