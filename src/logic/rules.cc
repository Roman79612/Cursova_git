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
 Synopsis: Applies the corner rule to the field. (Empty field case)
 ---------------------------------------------------------------------[>]*/
void Rules::apply_corner_rule(Field& field) {
    int max_x = field.get_width() - 1;
    int max_y = field.get_height() - 1;

    Cell& tl = field.get_cell(0, 0);
    tl.set_dir_from(Direction::DOWN);
    tl.set_dir_to(Direction::RIGHT);
    tl.set_type(CellType::LINE);

    Cell& tr = field.get_cell(max_x, 0);
    tr.set_dir_from(Direction::DOWN);
    tr.set_dir_to(Direction::LEFT);
    tr.set_type(CellType::LINE);

    Cell& bl = field.get_cell(0, max_y);
    bl.set_dir_from(Direction::UP);
    bl.set_dir_to(Direction::RIGHT);
    bl.set_type(CellType::LINE);

    Cell& br = field.get_cell(max_x, max_y);
    br.set_dir_from(Direction::UP);
    br.set_dir_to(Direction::LEFT);
    br.set_type(CellType::LINE);
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::is_on_black_corner
 Synopsis: Checks if the cell is on a black corner.
 ---------------------------------------------------------------------[>]*/
bool Rules::is_on_border(int x, int y, int width, int height) {
    return x == 0 || y == 0 || x == width - 1 || y == height - 1;
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::is_on_black_corner
 Synopsis: Checks if the cell is on a black corner.
 ---------------------------------------------------------------------[>]*/
bool Rules::is_near_border(int x, int y, int width, int height) {
    return x == 1 || y == 1 || x == width - 2 || y == height - 2;
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::force_straight_path
 Synopsis: Forces a straight path in the specified direction using Graph.
 ---------------------------------------------------------------------[>]*/
void Rules::force_straight_path(Field& field, Graph& graph, Cell& cell, Direction dir) {
    Cell& next = graph.get_neighbor(cell, dir);
    Cell& after_next = graph.get_neighbor(next, dir);

    graph.add_edge(cell, next);
    graph.add_edge(next, after_next);

    if (next.get_type() == CellType::EMPTY) {
        next.set_type(CellType::LINE);
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::force_through_path
 Synopsis: Forces a path through the specified cell in the given direction, using the graph.
 ---------------------------------------------------------------------[>]*/
void Rules::force_through_path(Field& field, Graph& graph, Cell& cell, Direction dir) {
    Direction opp = DirectionHelper::opposite(dir);

    Cell& next = graph.get_neighbor(cell, dir);
    Cell& prev = graph.get_neighbor(cell, opp);

    graph.add_edge(cell, next);
    graph.add_edge(cell, prev);
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_black_corner_rule
 Synopsis: Applies the black corner rule to the puzzle, forcing the path to travel in specific directions at black corners.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_black_corner_rule(Field& field, Graph& graph) {
    std::vector<Cell*> black_cells = field.get_black_cells();
    if (black_cells.empty()) return;

    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell_ptr : black_cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        if (x == 0 && y == 0) {
            force_straight_path(field, graph, cell, Direction::DOWN);
            force_straight_path(field, graph, cell, Direction::RIGHT);

        } else if (x == width - 1 && y == 0) {
            force_straight_path(field, graph, cell, Direction::DOWN);
            force_straight_path(field, graph, cell, Direction::LEFT);
        } else if (x == 0 && y == height - 1) {
            force_straight_path(field, graph, cell, Direction::UP);
            force_straight_path(field, graph, cell, Direction::RIGHT);
        } else if (x == width - 1 && y == height - 1) {
            force_straight_path(field, graph, cell, Direction::UP);
            force_straight_path(field, graph, cell, Direction::LEFT);
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_white_edge_rule
 Synopsis: Applies the white edge rule for white pearls on the grid's edges.
 ---------------------------------------------------------------------[>]-*/
void Rules::apply_white_edge_rule(Field& field, Graph& graph) {
    std::vector<Cell*> white_cells = field.get_white_cells();
    if (white_cells.empty()) return;

    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell_ptr : white_cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        if (!is_on_border(x, y, width, height)) {
            continue;
        }

        if (x == 0 || x == width - 1) {
            force_through_path(field, graph, cell, Direction::DOWN);
            force_through_path(field, graph, cell, Direction::UP);
        } else if (y == 0 || y == height - 1) {
            force_through_path(field, graph, cell, Direction::RIGHT);
            force_through_path(field, graph, cell, Direction::LEFT);
        } else {
            continue;
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_black_edge_rule
 Synopsis: Applies black circle constraints on edges and corners.
 ---------------------------------------------------------------------[>]-*/
void Rules::apply_black_edge_rule(Field& field, Graph& graph) {
    std::vector<Cell*> cells = field.get_black_cells();
    if (cells.empty()) return;

    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell_ptr : cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        if (!is_on_border(x, y, width, height)) {
            continue;
        }

        if (x == 0) {
            force_straight_path(field, graph, cell, Direction::RIGHT);
        } else if (x == width - 1) {
            force_straight_path(field, graph, cell, Direction::LEFT);
        } else if (y == 0) {
            force_straight_path(field, graph, cell, Direction::DOWN);
        } else if (y == height - 1) {
            force_straight_path(field, graph, cell, Direction::UP);
        } else {
            continue;
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_black_near_border_rule
 Synopsis: Applies the black near border rule.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_black_near_border_rule(Field& field, Graph& graph) {
    std::vector<Cell*> cells = field.get_black_cells();
    if (cells.empty()) return;

    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell_ptr : cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        if (!is_near_border(x, y, width, height)) {
            continue;
        }

        if (x == 1) {
            force_straight_path(field, graph, cell, Direction::RIGHT);
        } else if (x == width - 2) {
            force_straight_path(field, graph, cell, Direction::LEFT);
        } else if (y == 1) {
            force_straight_path(field, graph, cell, Direction::DOWN);
        } else if (y == height - 2) {
            force_straight_path(field, graph, cell, Direction::UP);
        } else {
            continue;
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: apply_adjacent_black_rule
 Synopsis: Enforces the rule that adjacent black pearls must each have one line pointing away from the other.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_adjacent_black_rule(Field& field, Graph& graph) {
    std::vector<Cell*> black_cells = field.get_black_cells();
    if (black_cells.empty()) return;

    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell_ptr : black_cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        if (is_on_border(x, y, width, height) || is_near_border(x, y, width, height)) {
            continue;
        }

        auto neighbors = field.get_neighbors(cell);

        for (Cell* neighbor_ptr : neighbors) {
            if (neighbor_ptr->get_type() != CellType::BLACK) {
                continue;
            }

            Cell& neighbor_cell = *neighbor_ptr;
            int nx = neighbor_cell.get_x();
            int ny = neighbor_cell.get_y();

            int dx = nx - x;
            int dy = ny - y;

            Direction dir = DirectionHelper::get_dir_delta(dx, dy);

            if (dir == Direction::LEFT) {
                force_straight_path(field, graph, cell, Direction::RIGHT);
                force_straight_path(field, graph, neighbor_cell, Direction::LEFT);
                graph.ban_edge(cell, neighbor_cell);
            } else if (dir == Direction::RIGHT) {
                force_straight_path(field, graph, cell, Direction::LEFT);
                force_straight_path(field, graph, neighbor_cell, Direction::RIGHT);
                graph.ban_edge(cell, neighbor_cell);
            } else if (dir == Direction::UP) {
                force_straight_path(field, graph, cell, Direction::UP);
                force_straight_path(field, graph, neighbor_cell, Direction::DOWN);
                graph.ban_edge(cell, neighbor_cell);
            } else if (dir == Direction::DOWN) {
                force_straight_path(field, graph, cell, Direction::DOWN);
                force_straight_path(field, graph, neighbor_cell, Direction::UP);
                graph.ban_edge(cell, neighbor_cell);
            }
        }
    }
}


/* ---------------------------------------------------------------------[<]-
 Function: apply_adjacent_black_near_edge_rule
 Synopsis: Enforces rules for adjacent black pearls that are near the edge 
           of the field. Ensures straight paths and corner constraints.
 ---------------------------------------------------------------------[>]-*/
void Rules::apply_adjacent_black_near_edge_rule(Field& field, Graph& graph) {
    std::vector<Cell*> black_cells = field.get_black_cells();
    if (black_cells.empty()) return;

    int width = field.get_width();
    int height = field.get_height();

    int top = 1;
    int down = height - 2;
    int left = 1;
    int right = width - 2;

    for (Cell* cell_ptr : black_cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        if (!is_near_border(x, y, width, height)) {
            continue;
        }

        auto neighbors = field.get_neighbors(cell);

        for (Cell* neighbor_ptr : neighbors) {
            if (neighbor_ptr->get_type() != CellType::BLACK) {
                continue;
            }

            Cell& neighbor_cell = *neighbor_ptr;
            int nx = neighbor_cell.get_x();
            int ny = neighbor_cell.get_y();

            int dx = nx - x;
            int dy = ny - y;

            Direction dir = DirectionHelper::get_dir_delta(dx, dy);

            if (dir == Direction::LEFT) {
                force_straight_path(field, graph, cell, Direction::RIGHT);
                force_straight_path(field, graph, neighbor_cell, Direction::LEFT);
                graph.ban_edge(cell, neighbor_cell);
            } else if (dir == Direction::RIGHT) {
                force_straight_path(field, graph, cell, Direction::LEFT);
                force_straight_path(field, graph, neighbor_cell, Direction::RIGHT);
                graph.ban_edge(cell, neighbor_cell);
            } else if (dir == Direction::UP) {
                force_straight_path(field, graph, cell, Direction::UP);
                force_straight_path(field, graph, neighbor_cell, Direction::DOWN);
                graph.ban_edge(cell, neighbor_cell);
            } else if (dir == Direction::DOWN) {
                force_straight_path(field, graph, cell, Direction::DOWN);
                force_straight_path(field, graph, neighbor_cell, Direction::UP);
                graph.ban_edge(cell, neighbor_cell);
            }

            if (y == top && ny == top) {
                force_straight_path(field, graph, cell, Direction::DOWN);
                force_straight_path(field, graph, neighbor_cell, Direction::DOWN);
            } else if (y == down && ny == down) {
                force_straight_path(field, graph, cell, Direction::UP);
                force_straight_path(field, graph, neighbor_cell, Direction::UP);
            } else if (x == left && nx == left) {
                force_straight_path(field, graph, cell, Direction::RIGHT);
                force_straight_path(field, graph, neighbor_cell, Direction::RIGHT);
            } else if (x == right && nx == right) {
                force_straight_path(field, graph, cell, Direction::LEFT);
                force_straight_path(field, graph, neighbor_cell, Direction::LEFT);
            }
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_white_border_pair_rule
 Synopsis: Forces a line between two border-aligned white pearls to be 
           parallel to border and turn at each end.
 ---------------------------------------------------------------------[>]-*/
void Rules::apply_white_border_pair_rule(Field& field, Graph& graph) {
    std::vector<Cell*> white_cells = field.get_white_cells();
    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell_ptr : white_cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        if (!is_on_border(x, y, width, height)) continue;

        for (Direction dir : DirectionHelper::get_all_dirs()) {
            if (field.can_go(x, y, dir)) {
                Cell& neighbor = graph.get_neighbor(cell, dir);
                int nx = neighbor.get_x();
                int ny = neighbor.get_y();

                if (neighbor.get_type() == CellType::WHITE && is_on_border(nx, ny, width, height)) {
                    if ((x < nx) || (y < ny)){
                    apply_white_pair_connection(field, graph, cell, neighbor, dir);
                    }
                }
            }

            if (field.can_go(x, y, dir) && field.can_go_in_steps(x, y, dir, 2)) {
                Cell& middle = graph.get_neighbor(cell, dir);
                Cell& second = graph.get_neighbor(middle, dir);

                if (second.get_type() == CellType::WHITE && is_on_border(second.get_x(), second.get_y(), width, height)) {
                    if ((middle.get_x() < second.get_x()) || (middle.get_y() < second.get_y())){
                        apply_white_pair_connection(field, graph, cell, second, dir);
                    }
                }
            }
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_white__pair_connection
 Synopsis: Helper for apply_white_border_pair_rule
 ---------------------------------------------------------------------[>]-*/
void Rules::apply_white_pair_connection(Field& field, Graph& graph, Cell& c1, Cell& c2, Direction dir) {
    force_through_path(field, graph, c1, dir);
    force_through_path(field, graph, c2, DirectionHelper::opposite(dir));

    Cell& next1 = graph.get_neighbor(c1, dir);
    for (Direction turn : DirectionHelper::get_perpendicular(dir)) {
        if (field.can_go(next1.get_x(), next1.get_y(), turn)) {
            Cell& turn_cell = graph.get_neighbor(next1, turn);
            graph.add_edge(next1, turn_cell);
        }
    }

    Cell& next2 = graph.get_neighbor(c2, DirectionHelper::opposite(dir));
    for (Direction turn : DirectionHelper::get_perpendicular(dir)) {
        if (field.can_go(next2.get_x(), next2.get_y(), turn)) {
            Cell& turn_cell = graph.get_neighbor(next2, turn);
            graph.add_edge(next2, turn_cell);
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_parallel_directions
 Synopsis: Applies parallel directions to the given cells.
 ---------------------------------------------------------------------[>]*/
void Rules::enforce_white_triplets(Field& field, Graph& graph) {
    std::vector<Cell*> white_cells = field.get_white_cells();

    for (Cell* cell_ptr : white_cells) {
        Cell& cell = *cell_ptr;

        for (Direction dir : DirectionHelper::get_all_dirs()) {
            if (!field.can_go(cell.get_x(), cell.get_y(), dir)) continue;
            if (!field.can_go(cell.get_x(), cell.get_y(), DirectionHelper::opposite(dir))) continue;

            Cell& neighbor_1 = graph.get_neighbor(cell, dir);
            Cell& neighbor_2 = graph.get_neighbor(cell, DirectionHelper::opposite(dir));

            if (neighbor_1.get_type() == CellType::WHITE && neighbor_2.get_type() == CellType::WHITE) {

                std::vector<Direction> perp_dirs = DirectionHelper::get_perpendicular(dir);
                Direction perp_dir = perp_dirs.front();

                force_through_path(field, graph, cell, perp_dir);
                force_through_path(field, graph, neighbor_1, perp_dir);
                force_through_path(field, graph, neighbor_2, perp_dir);
            }
        }
    }
}
