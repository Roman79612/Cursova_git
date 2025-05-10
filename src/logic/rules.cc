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
    return (x == 0 || y == 0 || x == width - 1 || y == height - 1);
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
 Function: Rules::force_ban_perpendicular
 Synopsis: Ban a path through the specified cell in the given perpendicular direction, using the graph.
 ---------------------------------------------------------------------[>]*/
void Rules::force_ban_perpendicular(Field& field, Graph& graph, Cell& cell, Direction dir) {
    int width = field.get_width();
    int height = field.get_height();

    for (Direction perp_dir : DirectionHelper::get_perpendicular(dir)) {
        auto [dx, dy] = DirectionHelper::get_delta(perp_dir);
        int px = cell.get_x() + dx;
        int py = cell.get_y() + dy;

        if (px < 0 || py < 0 || px >= width || py >= height) {
            continue;
        }
        Cell& perp = field.get_cell(px, py);
        graph.remove_edge(cell, perp);
    }
}

/* ----------------------------------------------------------------<Method>-
 Function: Rules::turn_in_next_cell
 Description: Connects the 'from_cell' in the given 'move_dir' to its neighbor,
              then connects that neighbor in the specified 'turn_dir' to simulate
              a required bent line. Skips if directions are equal or opposite.
 ------------------------------------------------------------------</Method>-*/
void Rules::turn_in_next_cell(Field& field, Graph& graph, Cell& from_cell, Direction move_dir, Direction turn_dir) {
    if (move_dir == turn_dir || DirectionHelper::opposite(move_dir) == turn_dir) return;
    auto [dx, dy] = DirectionHelper::get_delta(move_dir);
    int nx = from_cell.get_x() + dx;
    int ny = from_cell.get_y() + dy;

    if (!field.in_bounds(nx, ny)) {
            return;
    }

    Direction opp = DirectionHelper::opposite(turn_dir);
    auto [ox, oy] = DirectionHelper::get_delta(opp);
    int fx = from_cell.get_x() + ox;
    int fy = from_cell.get_y() + oy;
    if (field.in_bounds(fx, fy)) {
        Cell& forbidden = field.get_cell(fx, fy);
        graph.remove_edge(from_cell, forbidden);
    }

    Cell& next = field.get_cell(nx, ny);
    graph.add_edge(from_cell, next);

    auto [tdx, tdy] = DirectionHelper::get_delta(turn_dir);
    int tx = nx + tdx;
    int ty = ny + tdy;

    if (!field.in_bounds(tx, ty)) {
        return;
    }

    Cell& bend = field.get_cell(tx, ty);
    graph.add_edge(next, bend);
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
                graph.remove_edge(cell, neighbor_cell);
            } else if (dir == Direction::RIGHT) {
                force_straight_path(field, graph, cell, Direction::LEFT);
                force_straight_path(field, graph, neighbor_cell, Direction::RIGHT);
                graph.remove_edge(cell, neighbor_cell);
            } else if (dir == Direction::UP) {
                force_straight_path(field, graph, cell, Direction::UP);
                force_straight_path(field, graph, neighbor_cell, Direction::DOWN);
                graph.remove_edge(cell, neighbor_cell);
            } else if (dir == Direction::DOWN) {
                force_straight_path(field, graph, cell, Direction::DOWN);
                force_straight_path(field, graph, neighbor_cell, Direction::UP);
                graph.remove_edge(cell, neighbor_cell);
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
                force_straight_path(field, graph, cell, Direction::DOWN);
                force_straight_path(field, graph, cell, Direction::UP);
                graph.remove_edge(cell, neighbor_cell);
            } else if (dir == Direction::RIGHT) {
                force_straight_path(field, graph, cell, Direction::LEFT);
                force_straight_path(field, graph, neighbor_cell, Direction::RIGHT);
                graph.remove_edge(cell, neighbor_cell);
            } else if (dir == Direction::UP) {
                force_straight_path(field, graph, cell, Direction::UP);
                force_straight_path(field, graph, neighbor_cell, Direction::DOWN);
                graph.remove_edge(cell, neighbor_cell);
            } else if (dir == Direction::DOWN) {
                force_straight_path(field, graph, cell, Direction::DOWN);
                force_straight_path(field, graph, neighbor_cell, Direction::UP);
                graph.remove_edge(cell, neighbor_cell);
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
           parallel to the border and turn at each end. If the pair of white pearls 
           is located on the border and is close enough, a line between them must turn 
           at each of their ends (i.e., it must follow the required constraints).
 ---------------------------------------------------------------------[>]*/
void Rules::apply_white_border_pair_rule(Field& field, Graph& graph) {
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

        for (Cell* neighbor_ptr : white_cells) {
            Cell& neighbor = *neighbor_ptr;
            if (&cell == &neighbor) continue;

            int nx = neighbor.get_x();
            int ny = neighbor.get_y();
            if (nx - x < -2 || nx - x > 2 || ny - y < -2 || ny - y > 2) {
                continue;
            }

            if (is_on_border(nx, ny, width, height)) {
                graph.add_edge(cell, neighbor);
                if (y == 0 && ny == 0) {
                    apply_turn_for_top_border(field, graph, cell, neighbor);
                } else if (y == height - 1 && ny == height - 1) {
                    apply_turn_for_bottom_border(field, graph, cell, neighbor);
                } else if (x == 0 && nx == 0) {
                    apply_turn_for_left_border(field, graph, cell, neighbor);
                } else if (x == width - 1 && nx == width - 1) {
                    apply_turn_for_right_border(field, graph, cell, neighbor);
                } else {
                    continue;
                }
            }
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_turn_for_left_border
 Synopsis: Applies a turn rule for the left border, ensuring the path 
           bends properly between two white pearls on the left edge of the grid.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_turn_for_left_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor) {
    if (cell.get_y() < neighbor.get_y()) {
        Rules::turn_in_next_cell(field, graph, cell, Direction::LEFT, Direction::DOWN);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::RIGHT, Direction::DOWN);
    } else {
        Rules::turn_in_next_cell(field, graph, cell, Direction::LEFT, Direction::UP);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::RIGHT, Direction::UP);
    }    
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_turn_for_right_border
 Synopsis: Applies a turn rule for the right border, ensuring the path 
           bends properly between two white pearls on the right edge of the grid.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_turn_for_right_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor) {
    if (cell.get_y() < neighbor.get_y()) {
        Rules::turn_in_next_cell(field, graph, cell, Direction::RIGHT, Direction::DOWN);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::LEFT, Direction::DOWN);
    } else {
        Rules::turn_in_next_cell(field, graph, cell, Direction::RIGHT, Direction::UP);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::LEFT, Direction::UP);
    }    
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_turn_for_top_border
 Synopsis: Applies a turn rule for the top border, ensuring the path 
           bends properly between two white pearls on the top edge of the grid.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_turn_for_top_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor) {
    if (cell.get_x() < neighbor.get_x()) {
        Rules::turn_in_next_cell(field, graph, cell, Direction::UP, Direction::RIGHT);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::DOWN, Direction::RIGHT);
    } else {
        Rules::turn_in_next_cell(field, graph, cell, Direction::UP, Direction::LEFT);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::DOWN, Direction::LEFT);
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_turn_for_bottom_border
 Synopsis: Applies a turn rule for the bottom border, ensuring the path 
           bends properly between two white pearls on the bottom edge of the grid.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_turn_for_bottom_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor) {
    if (cell.get_x() < neighbor.get_x()) {
        Rules::turn_in_next_cell(field, graph, cell, Direction::DOWN, Direction::RIGHT);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::UP, Direction::RIGHT);
    } else {
        Rules::turn_in_next_cell(field, graph, cell, Direction::DOWN, Direction::LEFT);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::UP, Direction::LEFT);
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

void Rules::apply_combination_rule(Field& field, Graph& graph) {
    std::vector<Cell*> black_cells = field.get_black_cells();

    for (Cell* cell_ptr : black_cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        std::vector<Cell*> diagonal_neighbors;
        
        std::vector<std::pair<int, int>> offsets = {
            {-1, -1}, {1, 1}, {-1, 1}, {1, -1}
        };
        
        for (auto offset : offsets) {
            int nx = x + offset.first;
            int ny = y + offset.second;
            
            if (field.in_bounds(nx, ny)) {
                Cell& neighbor = field.get_cell(nx, ny);
                if (neighbor.is_white()) {
                    diagonal_neighbors.push_back(&neighbor);
                }
            }
        }

        if (diagonal_neighbors.size() == 2) {
            Cell& white1 = *diagonal_neighbors[0];
            Cell& white2 = *diagonal_neighbors[1];

            Direction dir1, dir2;

            if (white1.get_x() > x) {
                dir1 = Direction::RIGHT;
            } else {
                dir1 = Direction::LEFT;
            }

            if (white2.get_y() > y) {
                dir2 = Direction::DOWN;
            } else {
                dir2 = Direction::UP;
            }

            
            if (dir1 != dir2) {
                if (dir1 == Direction::RIGHT) {
                    force_straight_path(field, graph, cell, Direction::LEFT);
                } else if (dir1 == Direction::LEFT) {
                    force_straight_path(field, graph, cell, Direction::RIGHT);
                } else if (dir2 == Direction::UP) {
                    force_straight_path(field, graph, cell, Direction::DOWN);
                } else if (dir2 == Direction::DOWN) {
                    force_straight_path(field, graph, cell, Direction::UP);
                }
            }
        }
    }
}
