/* ----------------------------------------------------------------<Header>-
 Name: solver.h
 Title: Solver class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-06
  Description: Header file for the Solver class, which implements the solving logic for Masyu puzzles.
 ------------------------------------------------------------------</Header>-*/

#ifndef SOLVER_H
#define SOLVER_H

#include "../core_headers/field.h"
#include "../core_headers/cell.h"
#include "../core_headers/direction.h"
#include "../logic_headers/rules.h"
#include "../logic_headers/graph.h"
#include <unordered_set>

class Solver {
public:
    Solver(Field& field);
    bool solve();

private:
    Field& field;
    Graph graph;
    std::vector<Cell*> whit_cells;
    std::vector<Cell*> black_cells;

    void apply_deduction_rules();
    bool backtrack();
    void solve_empty_field();
    bool is_solved();
};

#endif // SOLVER_H