/* ----------------------------------------------------------------<Header>-
 Name: field.cc
 Title: Field class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Source file implementing the puzzle grid logic.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/field.h"

/* ---------------------------------------------------------------------[<]-
 Function: Field::Field
 Synopsis: Constructor initializing the field with given dimensions.
 ---------------------------------------------------------------------[>]-*/
Field::Field(int width, int height) : width(width), height(height), cells(height, std::vector<Cell>(width)) {}

/* ---------------------------------------------------------------------[<]-
 Function: Field::get_cell
 Synopsis: Returns the cell at specified coordinates.
 ---------------------------------------------------------------------[>]-*/
Cell Field::get_cell(int x, int y) const {
    return cells[y][x];
}

/* ---------------------------------------------------------------------[<]-
 Function: Field::set_cell
 Synopsis: Sets the cell at specified coordinates.
 ---------------------------------------------------------------------[>]-*/
void Field::set_cell(int x, int y, Cell cell) {
    cells[y][x] = cell;
}

/* ---------------------------------------------------------------------[<]-
 Function: Field::in_bounds
 Synopsis: Checks whether the given coordinates are within the field.
 ---------------------------------------------------------------------[>]-*/
bool Field::in_bounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

/* ---------------------------------------------------------------------[<]-
 Function: Field::get_width
 Synopsis: Returns the width of the field.
 ---------------------------------------------------------------------[>]-*/
int Field::get_width() const {
    return width;
}

/* ---------------------------------------------------------------------[<]-
 Function: Field::get_height
 Synopsis: Returns the height of the field.
 ---------------------------------------------------------------------[>]-*/
int Field::get_height() const {
    return height;
}

/* ---------------------------------------------------------------------[<]-
 Function: Field::reset
 Synopsis: Resets the field to all empty cells.
 ---------------------------------------------------------------------[>]-*/
void Field::reset() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cells[y][x] = Cell(CellType::EMPTY);
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Field::clone
 Synopsis: Creates a copy of the current field.
 ---------------------------------------------------------------------[>]-*/
Field Field::clone() const {
    Field copy(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            copy.set_cell(x, y, cells[y][x]);
        }
    }
    return copy;
}

/* ---------------------------------------------------------------------[<]-
 Function: Field::get_neighbors
 Synopsis: Returns coordinates of valid neighbor cells (UP, DOWN, LEFT, RIGHT).
 ---------------------------------------------------------------------[>]-*/
std::vector<std::pair<int, int>> Field::get_neighbors(int x, int y) const {
    std::vector<std::pair<int, int>> neighbors;
    for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}) {
        int nx = x + DirectionHelper::get_dx(dir);
        int ny = y + DirectionHelper::get_dy(dir);
        if (in_bounds(nx, ny)) {
            neighbors.emplace_back(nx, ny);
        }
    }
    return neighbors;
}

/* ---------------------------------------------------------------------[<]- 
 Function: Field::print_initial_state
 Synopsis: Prints the initial state of the puzzle grid, showing all cell types.
 ---------------------------------------------------------------------[>]-*/
void Field::print_initial_state() const {
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            switch (cell.get_type()) {
                case CellType::EMPTY:
                    std::cout << " .";
                    break;
                case CellType::WHITE_DOT:
                    std::cout << u8"○";
                    break;
                case CellType::BLACK_DOT:
                    std::cout << u8"●";
                    break;
                case CellType::LINE:
                    std::wcout << cell.get_line_symbol();
                    break;
                default:
                    std::cout << '?';
            }
        }
        std::cout << std::endl;
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: Field::print_final_state
 Synopsis: Prints the final state of the puzzle grid, displaying only the line path.
 ---------------------------------------------------------------------[>]-*/
void Field::print_final_state() const {
    std::wcout << L"Final Field:\n";
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            if (cell.has_line()) {
                std::wcout << cell.get_line_symbol();
            } else {
                std::wcout << L' ';
            }
        }
        std::wcout << std::endl;
    }
}
