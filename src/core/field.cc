/* ----------------------------------------------------------------<Header>-
 Name: field.cpp
 Title: Field class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-05
 Description: Implementation of the Field class for managing puzzle grid,
              including access, validation, and utility methods.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/field.h"

/* ---------------------------------------------------------------------[<]- 
 Function: Field
 Synopsis: Constructor to initialize the grid with given dimensions.
 ---------------------------------------------------------------------[>]-*/
Field::Field(int width, int height) : width(width), height(height), cells(height, std::vector<Cell>(width)) {
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            cells[y][x] = Cell(x, y);
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_cell
 Synopsis: Returns a copy of the cell at (x, y).
 ---------------------------------------------------------------------[>]-*/
Cell& Field::get_cell(int x, int y) {
    return cells[y][x];
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_cell
 Synopsis: Sets the cell at the specified coordinates.
 ---------------------------------------------------------------------[>]-*/
void Field::set_cell(const Cell& cell) {
    int x = cell.get_x();
    int y = cell.get_y();
    cells[y][x] = cell;
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_cell_type
 Synopsis: Sets the type of the cell at (x, y).
 ---------------------------------------------------------------------[>]-*/
void Field::set_cell_type(const Cell& cell, CellType type) {
    int x = cell.get_x();
    int y = cell.get_y();
    cells[y][x].set_type(type);
}

/* ---------------------------------------------------------------------[<]- 
 Function: reset_all_dirs
 Synopsis: Resets directions of all cells in the field.
 ---------------------------------------------------------------------[>]-*/
void Field::reset_all_dirs() {
    for (auto& row : cells)
        for (auto& cell : row)
            cell.reset_dirs();
}

/* ---------------------------------------------------------------------[<]- 
 Function: reset_all_visited
 Synopsis: Resets visited status of all cells.
 ---------------------------------------------------------------------[>]-*/
void Field::reset_all_visited() {
    for (auto& row : cells)
        for (auto& cell : row)
            cell.set_visited(false);
}

/* ---------------------------------------------------------------------[<]- 
 Function: in_bounds
 Synopsis: Checks if (x, y) is within field bounds.
 ---------------------------------------------------------------------[>]-*/
bool Field::in_bounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

/* ---------------------------------------------------------------------[<]- 
 Function: can_go
 Synopsis: Checks if movement from (x, y) in given direction is within bounds.
 ---------------------------------------------------------------------[>]-*/
bool Field::can_go(int x, int y, Direction dir) const {
    int nx = x + DirectionHelper::get_dx(dir);
    int ny = y + DirectionHelper::get_dy(dir);
    return in_bounds(nx, ny);
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_width
 Synopsis: Returns width of the field.
 ---------------------------------------------------------------------[>]-*/
int Field::get_width() const {
    return width;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_height
 Synopsis: Returns height of the field.
 ---------------------------------------------------------------------[>]-*/
int Field::get_height() const {
    return height;
}

/* ---------------------------------------------------------------------[<]- 
 Function: reset
 Synopsis: Resets all visited flags and directions in the field.
 ---------------------------------------------------------------------[>]-*/
void Field::reset() {
    reset_all_dirs();
    reset_all_visited();
}

/* ---------------------------------------------------------------------[<]- 
 Function: clone
 Synopsis: Returns a deep copy of the field.
 ---------------------------------------------------------------------[>]-*/
Field Field::clone() const {
    Field copy(width, height);
    copy.cells = cells;
    return copy;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_neighbors
 Synopsis: Returns valid (x, y) coordinates of neighboring cells.
 ---------------------------------------------------------------------[>]-*/
std::vector<std::pair<int, int>> Field::get_neighbors(int x, int y) const {
    std::vector<std::pair<int, int>> neighbors;
    for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}) {
        int nx = x + DirectionHelper::get_dx(dir);
        int ny = y + DirectionHelper::get_dy(dir);
        if (in_bounds(nx, ny))
            neighbors.emplace_back(nx, ny);
    }
    return neighbors;
}

/* ---------------------------------------------------------------------[<]- 
 Function: available_directions
 Synopsis: Returns list of directions available from (x, y).
 ---------------------------------------------------------------------[>]-*/
std::vector<Direction> Field::available_directions(int x, int y) const {
    std::vector<Direction> dirs;
    for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}) {
        if (can_go(x, y, dir))
            dirs.push_back(dir);
    }
    return dirs;
}

/* ---------------------------------------------------------------------[<]- 
 Function: Field::print_field
 Synopsis: Prints the grid, showing all cell types.
 ---------------------------------------------------------------------[>]-*/
void Field::print_field() const {
    int rows = get_height();
    int cols = get_width();

    auto print_horizontal = [&](wchar_t left, wchar_t middle, wchar_t right) {
        std::wcout << left;
        for (int x = 0; x < cols; ++x) {
            std::wcout << L"───";
            if (x != cols - 1) std::wcout << middle;
        }
        std::wcout << right << std::endl;
    };

    print_horizontal(L'┌', L'┬', L'┐');

    for (int y = 0; y < rows; ++y) {
        std::wcout << L"│";
        for (int x = 0; x < cols; ++x) {
            std::wcout << L' ' << cells[y][x].get_symbol() << L' ' << L"│";
        }
        std::wcout << L"\n";

        if (y != rows - 1)
            print_horizontal(L'├', L'┼', L'┤');
        else
            print_horizontal(L'└', L'┴', L'┘');
    }
}
