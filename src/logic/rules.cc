/* ----------------------------------------------------------------<Header>-
 Name: rules.cc
 Title: Rules implementation for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-06
 Description: Implements edge and pattern rules for Masyu puzzle solving.
 ------------------------------------------------------------------</Header>-*/

#include "../logic_headers/rules.h"

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_corner_rule
 Synopsis: Applies the corner rule to the field.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_corner_rule(Field& field) {
    int max_x = field.get_width() - 1;
    int max_y = field.get_height() - 1;

    Cell& tl = field.get_cell(0, 0);
    tl.set_entry_dir(Direction::DOWN);
    tl.set_exit_dir(Direction::RIGHT);
    tl.set_type(CellType::LINE);

    Cell& tr = field.get_cell(max_x, 0);
    tr.set_entry_dir(Direction::DOWN);
    tr.set_exit_dir(Direction::LEFT);
    tr.set_type(CellType::LINE);

    Cell& bl = field.get_cell(0, max_y);
    bl.set_entry_dir(Direction::UP);
    bl.set_exit_dir(Direction::RIGHT);
    bl.set_type(CellType::LINE);

    Cell& br = field.get_cell(max_x, max_y);
    br.set_entry_dir(Direction::UP);
    br.set_exit_dir(Direction::LEFT);
    br.set_type(CellType::LINE);
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::force_straight_path
 Synopsis: Forces a straight path in the specified direction.
 ---------------------------------------------------------------------[>]*/
void Rules::force_straight_path(Field& field, int x, int y, Direction dir) {
    int dx = DirectionHelper::get_dx(dir), dy = DirectionHelper::get_dy(dir);
    int nx = x + dx;
    int ny = y + dy;

    if (!field.in_bounds(nx, ny)) return;

    Cell& next = field.get_cell(nx, ny);
    Direction opp = DirectionHelper::opposite(dir);

    if (next.get_type() == CellType::EMPTY) {
        next.set_entry_dir(opp);
        next.set_exit_dir(dir);
        next.set_type(CellType::LINE);
    } else if (next.get_type() == CellType::BLACK || next.get_type() == CellType::WHITE) {
        next.set_entry_dir(opp);
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_white_edge_rule
 Synopsis: Applies the white edge rule.
 ---------------------------------------------------------------------[>]-*/
void Rules::apply_white_edge_rule(Field& field) {
    std::vector<Cell*> white_cells = field.get_white_cells();

    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell : white_cells) {
        int x = cell->get_x();
        int y = cell->get_y();

        if (x == 0 || x == width - 1) {
            cell->set_entry_dir(Direction::UP);
            cell->set_exit_dir(Direction::DOWN);

            if (y > 0) {
                Cell& prev = field.get_cell(x, y - 1);
                prev.set_exit_dir(Direction::DOWN);
            }
            if (y < height - 1) {
                Cell& next = field.get_cell(x, y + 1);
                next.set_entry_dir(Direction::UP);
            }

        } else if (y == 0 || y == height - 1) {
            cell->set_entry_dir(Direction::LEFT);
            cell->set_exit_dir(Direction::RIGHT);

            if (x > 0) {
                Cell& prev = field.get_cell(x - 1, y);
                prev.set_exit_dir(Direction::RIGHT);
            }
            if (x < width - 1) {
                Cell& next = field.get_cell(x + 1, y);
                next.set_entry_dir(Direction::LEFT);
            }
        }
        else {
            continue;
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_black_edge_rule
 Synopsis: Applies the black edge rule.
 ---------------------------------------------------------------------[>]-*/
void Rules::apply_black_edge_rule(Field& field) {
    std::vector<Cell*> cells = field.get_black_cells();
    if (cells.empty()) return;

    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell_ptr : cells) {
        Cell& cell = *cell_ptr;
        cell.reset_dirs();
        int x = cell.get_x();
        int y = cell.get_y();

        if (x == 0 && y == 0) {
            cell.set_entry_dir(Direction::RIGHT);
            cell.set_exit_dir(Direction::DOWN);
            force_straight_path(field, x, y, Direction::DOWN);

        } else if (x == width - 1 && y == 0) {
            cell.set_entry_dir(Direction::LEFT);
            cell.set_exit_dir(Direction::DOWN);
            force_straight_path(field, x, y, Direction::DOWN);

        } else if (x == 0 && y == height - 1) {
            cell.set_entry_dir(Direction::UP);
            cell.set_exit_dir(Direction::RIGHT);
            force_straight_path(field, x, y, Direction::RIGHT);

        } else if (x == width - 1 && y == height - 1) {
            cell.set_entry_dir(Direction::UP);
            cell.set_exit_dir(Direction::LEFT);
            force_straight_path(field, x, y, Direction::LEFT);

        } else if (y == 0) {
            cell.set_exit_dir(Direction::DOWN);
            force_straight_path(field, x, y, Direction::DOWN);

        } else if (y == height - 1) {
            cell.set_exit_dir(Direction::UP);
            force_straight_path(field, x, y, Direction::UP);

        } else if (x == 0) {
            cell.set_exit_dir(Direction::RIGHT);
            force_straight_path(field, x, y, Direction::RIGHT);

        } else if (x == width - 1) {
            cell.set_exit_dir(Direction::LEFT);
            force_straight_path(field, x, y, Direction::LEFT);
        }
    }
}

/* ---------------------------------------------------------------------[<]-
Function: Rules::apply_white_pair_rule
Synopsis: Applies the white pair rule.
---------------------------------------------------------------------[>]-*/
//void Rules::apply_white_pair_rule(Field& field, int x, int y) {}

/* ---------------------------------------------------------------------[<]-
Function: Rules::apply_white_triplet_rule
Synopsis: Applies the white triplet rule.
---------------------------------------------------------------------[>]-*/
//void Rules::apply_white_triplet_rule(Field& field, int x, int y) {}

/* ---------------------------------------------------------------------[<]-
Function: Rules::apply_black_pair_rule
Synopsis: Applies the black pair rule.
---------------------------------------------------------------------[>]-*/
//void Rules::apply_black_pair_rule(Field& field, int x, int y) {}

/* ---------------------------------------------------------------------[<]-
Function: Rules::apply_black_white_diagonal_rule
Synopsis: Applies the black and white diagonal rule.
---------------------------------------------------------------------[>]-*/
//void Rules::apply_black_white_diagonal_rule(Field& field, int x, int y) {}
