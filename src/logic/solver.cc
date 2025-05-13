/* ----------------------------------------------------------------<Header>-
 Name: solver.cc
 Title: Solver class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-14
  Description: Implementation of the Solver class for solving Masyu puzzles.
 ------------------------------------------------------------------</Header>-*/

#include "../logic_headers/solver.h"

/* ---------------------------------------------------------------------[<]-
 Function: Solver::Solver
 Synopsis: Constructor for the Solver class.
 ---------------------------------------------------------------------[>]*/
Solver::Solver(Field& field) : field(field), graph(field) {
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
	if (!field.has_black_cell() && !field.has_white_cell()) {
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
    Rules::apply_black_corner_rule(field, graph);
    Rules::apply_white_border_pair_rule(field, graph);
	Rules::apply_white_edge_rule(field, graph);
	Rules::apply_black_edge_rule(field, graph);
    Rules::apply_black_near_border_rule(field, graph);
    Rules::apply_adjacent_black_rule(field, graph);
    Rules::apply_adjacent_black_near_edge_rule(field, graph);
    Rules::enforce_white_triplets(field, graph);
    Rules::apply_combination_rule(field, graph);
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
        tr.set_dir_from(Direction::LEFT);
        tr.set_dir_to(Direction::RIGHT);
		tr.set_type(CellType::LINE);
    }

    //Right column
    for (int y = 1; y < height - 1; y++) {
        Cell& rc = field.get_cell(width - 1, y);
        rc.set_dir_from(Direction::UP);
        rc.set_dir_to(Direction::DOWN);
		rc.set_type(CellType::LINE);
    }

    //Bottom row
    for (int x = 1; x < width - 1; x++) {
        Cell& br = field.get_cell(x, height - 1);
        br.set_dir_from(Direction::RIGHT);
        br.set_dir_to(Direction::LEFT);
		br.set_type(CellType::LINE);
    }

    //Left column
    for (int y = 1; y < height - 1; y++) {
        Cell& lc = field.get_cell(0, y);
        lc.set_dir_from(Direction::DOWN);
        lc.set_dir_to(Direction::UP);
		lc.set_type(CellType::LINE);
    }
}