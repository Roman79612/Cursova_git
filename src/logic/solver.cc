/* ----------------------------------------------------------------<Header>-
 Name: solver.cc
 Title: Solver class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-06
  Description: Implementation of the Solver class for solving Masyu puzzles.
 ------------------------------------------------------------------</Header>-*/

#include "../logic_headers/solver.h"

/* ---------------------------------------------------------------------[<]-
 Function: Solver::Solver
 Synopsis: Constructor for the Solver class.
 ---------------------------------------------------------------------[>]*/
Solver::Solver(Field& field) : field(field) {
    if (!field.is_initialized()) {
        throw std::invalid_argument("Field is not initialized.");
    }
    whit_cells = field.get_white_cells();
    black_cells = field.get_black_cells();
}

/* ---------------------------------------------------------------------[<]-
 Function: Solver::solve
 Synopsis: Main solving function.
 ---------------------------------------------------------------------[>]*/
bool Solver::solve() {
	int white_count = field.get_white_count();
	int black_count = field.get_black_count();

	if (white_count == 0 && black_count == 0) {
		Rules::apply_corner_rule(field);
		solve_empty_field();
		return true;
	}

	apply_deduction_rules();

	return true;
}

/* ---------------------------------------------------------------------[<]-
 Function: Solver::apply_deduction_rules
 Synopsis: Applies deduction rules to the field.
 ---------------------------------------------------------------------[>]*/
void Solver::apply_deduction_rules() {
	Rules::apply_white_edge_rule(field);
	Rules::apply_black_edge_rule(field);
}

/* ---------------------------------------------------------------------[<]-
 Function: Solver::backtrack
 Synopsis: Backtracking function to find a solution.
 ---------------------------------------------------------------------[>]*/
bool Solver::backtrack() {
	return false;
}

/* ---------------------------------------------------------------------[<]-
 Function: Solver::solve_empty_field
 Synopsis: Solves an empty field by setting entry and exit directions.
 ---------------------------------------------------------------------[>]*/
void Solver::solve_empty_field() {
	int width = field.get_width();
    int height = field.get_height();

	Rules::apply_corner_rule(field);
    //Top row
    for (int x = 1; x < width - 1; x++) {
        Cell& tr = field.get_cell(x, 0);
        tr.set_entry_dir(Direction::LEFT);
        tr.set_exit_dir(Direction::RIGHT);
		tr.set_type(CellType::LINE);
    }

    //Right column
    for (int y = 1; y < height - 1; y++) {
        Cell& rc = field.get_cell(width - 1, y);
        rc.set_entry_dir(Direction::UP);
        rc.set_exit_dir(Direction::DOWN);
		rc.set_type(CellType::LINE);
    }

    //Bottom row
    for (int x = 1; x < width - 1; x++) {
        Cell& br = field.get_cell(x, height - 1);
        br.set_entry_dir(Direction::RIGHT);
        br.set_exit_dir(Direction::LEFT);
		br.set_type(CellType::LINE);
    }

    //Left column
    for (int y = 1; y < height - 1; y++) {
        Cell& lc = field.get_cell(0, y);
        lc.set_entry_dir(Direction::DOWN);
        lc.set_exit_dir(Direction::UP);
		lc.set_type(CellType::LINE);
    }
}