/* ----------------------------------------------------------------<Header>-
 Name: solver.cc
 Title: Solver class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-07
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
	int white_count = field.get_white_count();
	int black_count = field.get_black_count();

	if (white_count == 0 && black_count == 0) {
		Rules::apply_corner_rule(field);
		solve_empty_field();
		return true;
	}

	apply_deduction_rules();

    if (is_solved()) {
        return true;
    }

	return backtrack();
}

/* ---------------------------------------------------------------------[<]-
 Function: Solver::apply_deduction_rules
 Synopsis: Applies deduction rules to the field.
 ---------------------------------------------------------------------[>]*/
void Solver::apply_deduction_rules() {
    Rules::apply_black_rule(field, graph);
    Rules::apply_white_rule(field, graph);
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
 Function: Solver::backtrack
 Synopsis: Backtracking function to find a solution.
---------------------------------------------------------------------[>]*/
bool Solver::backtrack() {
    if (is_solved()) {
        return true;
    }

    for (Cell* cell_ptr : field.get_all_cells()) {
        for (Direction dir : DirectionHelper::get_all_dirs()) {
            Cell& cell = *cell_ptr;
            int nx = cell.get_x() + DirectionHelper::get_dx(dir);
            int ny = cell.get_y() + DirectionHelper::get_dy(dir);

            if (!field.in_bounds(nx, ny)) continue;

            Cell& neighbor = field.get_cell(nx, ny);

            if (graph.get_state(cell, neighbor) != EdgeState::UNKNOWN) continue;

            Field field_snapshot = field;
            Graph graph_snapshot = graph;

            graph.add_edge(cell, neighbor);
            apply_deduction_rules();

            if (backtrack()) return true;

            field = field_snapshot;
            graph = graph_snapshot;

            graph.remove_edge(cell, neighbor);
            apply_deduction_rules();

            if (backtrack()) return true;

            field = field_snapshot;
            graph = graph_snapshot;
        }
    }

    return false;
}

bool Solver::is_solved() {
    std::unordered_set<Cell*> visited;
    std::vector<Cell*> loop_cells;

    for (Cell* cell_ptr : field.get_all_cells()) {
        Cell& cell = *cell_ptr;
        int connected = 0;
        for (Direction dir : DirectionHelper::get_all_dirs()) {
            int nx = cell.get_x() + DirectionHelper::get_dx(dir);
            int ny = cell.get_y() + DirectionHelper::get_dy(dir);
            if (!field.in_bounds(nx, ny)) continue;

            Cell& neighbor = field.get_cell(nx, ny);
            if (graph.get_state(cell, neighbor) == EdgeState::YES) {
                connected++;
            }
        }

        if (connected == 2) {
            loop_cells.push_back(&cell);
        } else if (connected != 0 && connected != 2) {
            return false;
        }
    }

    if (loop_cells.empty()) return false;

    Cell* start = loop_cells.front();
    Cell* current = start;
    Cell* prev = nullptr;

    do {
        visited.insert(current);
        Cell* next = nullptr;

        for (Direction dir : DirectionHelper::get_all_dirs()) {
            int nx = current->get_x() + DirectionHelper::get_dx(dir);
            int ny = current->get_y() + DirectionHelper::get_dy(dir);
            if (!field.in_bounds(nx, ny)) continue;

            Cell& neighbor = field.get_cell(nx, ny);

            if (graph.get_state(*current, neighbor) == EdgeState::YES && &neighbor != prev) {
                next = &neighbor;
                break;
            }
        }

        prev = current;
        current = next;

        if (!current) return false;

    } while (current != start);

    return visited.size() == loop_cells.size();
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