/* ----------------------------------------------------------------<Header>-
 Name: rules.cc
 Title: Rules implementation for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-14
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
 Function: Rules::force_straight
 Synopsis: Forces a straight path in the specified direction using Graph.
 ---------------------------------------------------------------------[>]*/
 void Rules::force_straight(Field& field, Graph& graph, Cell& cell, Direction dir) {
    try {
        Cell& next = graph.get_neighbor(cell, dir);
        graph.add_edge(cell, next);

        Cell& after_next = graph.get_neighbor(next, dir);
        graph.add_edge(next, after_next);

        if (next.get_type() == CellType::EMPTY) {
            next.set_type(CellType::LINE);
        }

        int width = field.get_width();
        int height = field.get_height();
        int x = after_next.get_x();
        int y = after_next.get_y();

        if (x == 1 && y == 0) {
            Rules::turn_in_next_cell(field, graph, after_next, Direction::LEFT, Direction::DOWN);
        } else if (x == width - 2 && y == 0) {
            Rules::turn_in_next_cell(field, graph, after_next, Direction::RIGHT, Direction::DOWN);
        } else if (x == 0 && y == 1) {
            Rules::turn_in_next_cell(field, graph, after_next, Direction::UP, Direction::RIGHT);
        } else if (x == 0 && y == height - 2) {
            Rules::turn_in_next_cell(field, graph, after_next, Direction::DOWN, Direction::RIGHT);
        } else if (x == 1 && y == height - 1) {
            Rules::turn_in_next_cell(field, graph, after_next, Direction::LEFT, Direction::UP);
        } else if (x == width - 2 && y == height - 1) {
            Rules::turn_in_next_cell(field, graph, after_next, Direction::RIGHT, Direction::UP);
        } else if (x == width -1 && y == height - 2) {
            Rules::turn_in_next_cell(field, graph, after_next, Direction::DOWN, Direction::LEFT);
        } else if (x == width - 1 && y == 1) {
            Rules::turn_in_next_cell(field, graph, after_next, Direction::UP, Direction::LEFT);
        } else {
            return;
        }

    } catch (const std::exception& e) {
        std::wcerr << L"[force_straight] Exception: " << e.what() << L"\n";
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::connect_with_next
 Synopsis: Forces a path through the specified cell in the given direction, using the graph.
 ---------------------------------------------------------------------[>]*/
 void Rules::connect_with_next(Field& field, Graph& graph, Cell& cell, Direction dir) {
    try {
        Cell& next = graph.get_neighbor(cell, dir);
        graph.add_edge(cell, next);
        if (next.get_type() == CellType::EMPTY && next.get_dir_to() != Direction::NONE && next.get_dir_from() != Direction::NONE) {
            next.set_type(CellType::LINE);
        }
        Cell& prev = graph.get_neighbor(cell, DirectionHelper::opposite(dir));
        if (prev.get_type() == CellType::EMPTY && prev.get_dir_to() != Direction::NONE && prev.get_dir_from() != Direction::NONE) {
            prev.set_type(CellType::LINE);
        }
    } catch (const std::exception& e) {
        std::wcerr << L"[connect_with_next] Error: " << e.what() << L"\n";
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::force_ban_perpendicular
 Synopsis: Ban a path through the specified cell in the given perpendicular direction, using the graph.
 ---------------------------------------------------------------------[>]*/
 void Rules::ban(Field& field, Graph& graph, Cell& cell, Direction dir) {
    std::pair<int, int> delta = DirectionHelper::get_delta(dir);
    int nx = cell.get_x() + delta.first;
    int ny = cell.get_y() + delta.second;

    if (!field.in_bounds(nx, ny)) {
        return;
    }

    cell.set_forbidden_dir(dir);

    try {
        Cell& next = graph.get_neighbor(cell, dir);
        graph.remove_edge(cell, next);
    } catch (const std::exception& e) {
        std::wcerr << L"[ban] Error: " << e.what() << L"\n";
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

    int x = from_cell.get_x();
    int y = from_cell.get_y();

    std::pair<int, int> delta = DirectionHelper::get_delta(move_dir);
    int nx = x + delta.first;
    int ny = y + delta.second;

    if (!field.in_bounds(nx, ny)) {
        std::wcerr << L"[turn_in_next_cell] Move target out of bounds: (" << nx << L"," << ny << L")\n";
        return;
    }

    try {
        Cell& next = graph.get_neighbor(from_cell, move_dir);
        graph.add_edge(from_cell, next);

        std::pair<int, int> delta_turn = DirectionHelper::get_delta(turn_dir);
        int tx = nx + delta_turn.first;
        int ty = ny + delta_turn.second;

        if (!field.in_bounds(tx, ty)) {
            return;
        }

        Cell& turn = graph.get_neighbor(next, turn_dir);
        graph.add_edge(next, turn);

        Direction opp_turn = DirectionHelper::opposite(turn_dir);
        next.set_forbidden_dir(move_dir);
        next.set_forbidden_dir(opp_turn);

    } catch (const std::exception& e) {
        std::wcerr << L"[turn_in_next_cell] Error: " << e.what() << L"\n";
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_black_corner_rule
 Synopsis: Applies the black corner rule to the puzzle, forcing the path to travel in specific directions at black corners.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_black_corner_rule(Field& field, Graph& graph) {
    std::vector<Cell*> black_cells = field.get_black_cells();
    if (black_cells.empty()) {
        return;
    } 

    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell_ptr : black_cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        if (x == 0 && y == 0) {
            force_straight(field, graph, cell, Direction::RIGHT);
            force_straight(field, graph, cell, Direction::DOWN);
            ban(field, graph, cell, Direction::LEFT);
            ban(field, graph, cell, Direction::UP);
        } else if (x == width - 1 && y == 0) {
            force_straight(field, graph, cell, Direction::LEFT);
            force_straight(field, graph, cell, Direction::DOWN);
            ban(field, graph, cell, Direction::RIGHT);
            ban(field, graph, cell, Direction::UP);
        } else if (x == 0 && y == height - 1) {
            force_straight(field, graph, cell, Direction::RIGHT);
            force_straight(field, graph, cell, Direction::UP);
            ban(field, graph, cell, Direction::LEFT);
            ban(field, graph, cell, Direction::DOWN);
        } else if (x == width - 1 && y == height - 1) {
            force_straight(field, graph, cell, Direction::LEFT);
            force_straight(field, graph, cell, Direction::UP);
            ban(field, graph, cell, Direction::RIGHT);
            ban(field, graph, cell, Direction::DOWN);
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_white_edge_rule
 Synopsis: Applies the white edge rule for white pearls on the grid's edges.
 ---------------------------------------------------------------------[>]-*/
void Rules::apply_white_edge_rule(Field& field, Graph& graph) {
    std::vector<Cell*> white_cells = field.get_white_cells();
    if (white_cells.empty()) {
        return;
    } 

    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell_ptr : white_cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        if (!is_on_border(x, y, width, height)) {
            continue;
        }

        if (x == 0) {
            connect_with_next(field, graph, cell, Direction::UP);
            connect_with_next(field, graph, cell, Direction::DOWN);
            ban(field, graph, cell, Direction::LEFT);
            ban(field, graph, cell, Direction::RIGHT);
            if (y == 1) {
                turn_in_next_cell(field, graph, cell, Direction::UP, Direction::RIGHT);
            } else if (y == width - 2) {
                turn_in_next_cell(field, graph, cell, Direction::DOWN, Direction::RIGHT);
            } else {
                continue;
            }
        } else if (y == 0) {
            connect_with_next(field, graph, cell, Direction::RIGHT);
            connect_with_next(field, graph, cell, Direction::LEFT);
            ban(field, graph, cell, Direction::UP);
            ban(field, graph, cell, Direction::DOWN);
            if (x == 1) {
                turn_in_next_cell(field, graph, cell, Direction::LEFT, Direction::DOWN);
            } else if (x == width - 2) {
                turn_in_next_cell(field, graph, cell, Direction::RIGHT, Direction::DOWN);
            } else {
                continue;
            }
        } else if (x == width - 1) {
            connect_with_next(field, graph, cell, Direction::DOWN);
            connect_with_next(field, graph, cell, Direction::UP);
            if (y == 1) {
                turn_in_next_cell(field, graph, cell, Direction::UP, Direction::LEFT);
            } else if (y == width - 2) {
                turn_in_next_cell(field, graph, cell, Direction::DOWN, Direction::LEFT);
            } else {
                continue;
            }
        } else if (y == height - 1) {
            connect_with_next(field, graph, cell, Direction::RIGHT);
            connect_with_next(field, graph, cell, Direction::LEFT);
            ban(field, graph, cell, Direction::UP);
            ban(field, graph, cell, Direction::DOWN);
            if (x == 1) {
                turn_in_next_cell(field, graph, cell, Direction::LEFT, Direction::UP);
            } else if (x == width - 2) {
                turn_in_next_cell(field, graph, cell, Direction::RIGHT, Direction::UP);
            } else {
                continue;
            }
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
    if (cells.empty()) {
        return;
    } 

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
            force_straight(field, graph, cell, Direction::RIGHT);
            ban(field, graph, cell, Direction::LEFT);
        } else if (x == width - 1) {
            force_straight(field, graph, cell, Direction::LEFT);
            ban(field, graph, cell, Direction::RIGHT);
        } else if (y == 0) {
            force_straight(field, graph, cell, Direction::DOWN);
            ban(field, graph, cell, Direction::UP);
        } else if (y == height - 1) {
            force_straight(field, graph, cell, Direction::UP);
            ban(field, graph, cell, Direction::DOWN);
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
    if (cells.empty()) {
        return;
    } 

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
            force_straight(field, graph, cell, Direction::RIGHT);
            ban(field, graph, cell, Direction::LEFT);
        } else if (x == width - 2) {
            force_straight(field, graph, cell, Direction::LEFT);
            ban(field, graph, cell, Direction::RIGHT);
        } else if (y == 1) {
            force_straight(field, graph, cell, Direction::DOWN);
            ban(field, graph, cell, Direction::UP);
        } else if (y == height - 2) {
            force_straight(field, graph, cell, Direction::UP);
            ban(field, graph, cell, Direction::DOWN);
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
    if (black_cells.empty()) {
        return;
    } 

    int width = field.get_width();
    int height = field.get_height();

    for (Cell* cell_ptr : black_cells) {
        Cell& cell = *cell_ptr;
        int x = cell.get_x();
        int y = cell.get_y();

        if (is_near_border(x, y, width, height)) {
            continue;
        }

        std::vector<Cell*> neighbors = field.get_neighbors(cell);

        for (Cell* neighbor_ptr : neighbors) {
            if (neighbor_ptr->get_type() != CellType::BLACK) {
                continue;
            }

            Cell& neighbor_cell = *neighbor_ptr;
            int nx = neighbor_cell.get_x();
            int ny = neighbor_cell.get_y();

            if (x > nx) {
                force_straight(field, graph, cell, Direction::RIGHT);
                force_straight(field, graph, neighbor_cell, Direction::LEFT);
                ban(field, graph, cell, Direction::LEFT);
                ban(field, graph, neighbor_cell, Direction::RIGHT);
            } else if (x < nx) {
                force_straight(field, graph, cell, Direction::LEFT);
                force_straight(field, graph, neighbor_cell, Direction::RIGHT);
                ban(field, graph, cell, Direction::RIGHT);
                ban(field, graph, neighbor_cell, Direction::LEFT);
            } else if (y > ny) {
                force_straight(field, graph, cell, Direction::UP);
                force_straight(field, graph, neighbor_cell, Direction::DOWN);
                ban(field, graph, cell, Direction::DOWN);
                ban(field, graph, neighbor_cell, Direction::UP);
            } else if (y < ny) {
                force_straight(field, graph, cell, Direction::DOWN);
                force_straight(field, graph, neighbor_cell, Direction::UP);
                ban(field, graph, cell, Direction::UP);
                ban(field, graph, neighbor_cell, Direction::DOWN);
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
    if (black_cells.empty()) {
        return;
    } 

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

        std::vector<Cell*> neighbors = field.get_neighbors(cell);

        for (Cell* neighbor_ptr : neighbors) {
            if (neighbor_ptr->get_type() != CellType::BLACK) {
                continue;
            }

            Cell& neighbor_cell = *neighbor_ptr;
            int nx = neighbor_cell.get_x();
            int ny = neighbor_cell.get_y();

            if (y == top && ny == top) {
                force_straight(field, graph, cell, Direction::DOWN);
                force_straight(field, graph, neighbor_cell, Direction::DOWN);
                ban(field, graph, cell, Direction::UP);
                ban(field, graph, neighbor_cell, Direction::UP);
            } else if (y == down && ny == down) {
                force_straight(field, graph, cell, Direction::UP);
                force_straight(field, graph, neighbor_cell, Direction::UP);
                ban(field, graph, cell, Direction::DOWN);
                ban(field, graph, neighbor_cell, Direction::DOWN);
            } else if (x == left && nx == left) {
                force_straight(field, graph, cell, Direction::RIGHT);
                force_straight(field, graph, neighbor_cell, Direction::RIGHT);
                ban(field, graph, cell, Direction::LEFT);
                ban(field, graph, neighbor_cell, Direction::LEFT);
            } else if (x == right && nx == right) {
                force_straight(field, graph, cell, Direction::LEFT);
                force_straight(field, graph, neighbor_cell, Direction::LEFT);
                ban(field, graph, cell, Direction::RIGHT);
                ban(field, graph, neighbor_cell, Direction::RIGHT);
            } else {
                continue;
            }

            if (x > nx) {
                force_straight(field, graph, cell, Direction::RIGHT);
                force_straight(field, graph, neighbor_cell, Direction::LEFT);
                ban(field, graph, cell, Direction::LEFT);
                ban(field, graph, neighbor_cell, Direction::RIGHT);
            } else if (x < nx) {
                force_straight(field, graph, cell, Direction::LEFT);
                force_straight(field, graph, neighbor_cell, Direction::RIGHT);
                ban(field, graph, cell, Direction::RIGHT);
                ban(field, graph, neighbor_cell, Direction::LEFT);
            } else if (y < ny) {
                force_straight(field, graph, cell, Direction::UP);
                force_straight(field, graph, neighbor_cell, Direction::DOWN);
                ban(field, graph, cell, Direction::DOWN);
                ban(field, graph, neighbor_cell, Direction::UP);
            } else if (y > ny) {
                force_straight(field, graph, cell, Direction::DOWN);
                force_straight(field, graph, neighbor_cell, Direction::UP);
                ban(field, graph, cell, Direction::UP);
                ban(field, graph, neighbor_cell, Direction::DOWN);
            } else {
                continue;
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
    if (white_cells.empty()) {
        return;
    } 

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
 Function: Rules::apply_turn_for_top_border
 Synopsis: Applies a turn rule for the top border, ensuring the path 
           bends properly between two white pearls on the top edge of the grid.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_turn_for_top_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor) {
    if (cell.get_x() < neighbor.get_x()) {
        Rules::turn_in_next_cell(field, graph, cell, Direction::LEFT, Direction::DOWN);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::RIGHT, Direction::DOWN);
    } else {
        Rules::turn_in_next_cell(field, graph, cell, Direction::RIGHT, Direction::DOWN);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::LEFT, Direction::DOWN);
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_turn_for_bottom_border
 Synopsis: Applies a turn rule for the bottom border, ensuring the path 
           bends properly between two white pearls on the bottom edge of the grid.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_turn_for_bottom_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor) {
    if (cell.get_x() < neighbor.get_x()) {
        Rules::turn_in_next_cell(field, graph, cell, Direction::LEFT, Direction::UP);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::RIGHT, Direction::UP);
    } else {
        Rules::turn_in_next_cell(field, graph, cell, Direction::RIGHT, Direction::UP);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::LEFT, Direction::UP);
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_turn_for_left_border
 Synopsis: Applies a turn rule for the left border, ensuring the path 
           bends properly between two white pearls on the left edge of the grid.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_turn_for_left_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor) {
    if (cell.get_y() < neighbor.get_y()) {
        Rules::turn_in_next_cell(field, graph, cell, Direction::UP, Direction::RIGHT);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::DOWN, Direction::RIGHT);
    } else {
        Rules::turn_in_next_cell(field, graph, cell, Direction::DOWN, Direction::RIGHT);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::UP, Direction::RIGHT);
    }    
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::apply_turn_for_right_border
 Synopsis: Applies a turn rule for the right border, ensuring the path 
           bends properly between two white pearls on the right edge of the grid.
 ---------------------------------------------------------------------[>]*/
void Rules::apply_turn_for_right_border(Field& field, Graph& graph, Cell& cell, Cell& neighbor) {
    if (cell.get_y() < neighbor.get_y()) {
        Rules::turn_in_next_cell(field, graph, cell, Direction::UP, Direction::LEFT);
        Rules::turn_in_next_cell(field, graph, neighbor, Direction::DOWN, Direction::LEFT);
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

                std::pair<Direction, Direction> perp_dirs = DirectionHelper::get_perpendicular(dir);
                Direction perp_dir_1 = perp_dirs.first;
                Direction perp_dir_2 = perp_dirs.second;

                connect_with_next(field, graph, cell, perp_dir_1);
                connect_with_next(field, graph, neighbor_1, perp_dir_1);
                connect_with_next(field, graph, neighbor_2, perp_dir_1);
                
                connect_with_next(field, graph, cell, perp_dir_2);
                connect_with_next(field, graph, neighbor_1, perp_dir_2);
                connect_with_next(field, graph, neighbor_2, perp_dir_2);
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
        
        for (std::pair<int, int> offset : offsets) {
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
                    force_straight(field, graph, cell, Direction::LEFT);
                } else if (dir1 == Direction::LEFT) {
                    force_straight(field, graph, cell, Direction::RIGHT);
                } else if (dir2 == Direction::UP) {
                    force_straight(field, graph, cell, Direction::DOWN);
                } else if (dir2 == Direction::DOWN) {
                    force_straight(field, graph, cell, Direction::UP);
                }
            }
        }
    }
}
