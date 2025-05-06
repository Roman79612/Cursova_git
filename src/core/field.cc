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
 Synopsis: Default constructor initializes a field with no cells.
 ---------------------------------------------------------------------[>]-*/
Field::Field() {
    width = 0;
    height = 0;
}

/* ---------------------------------------------------------------------[<]- 
    Function: init
    Synopsis: Initializes the field with given width and height.
 ---------------------------------------------------------------------[>]-*/
void Field::init(int w, int h) {
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Width and height must be positive integers.");
    }
    width = w;
    height = h;
    cells.resize(height, std::vector<Cell>(width));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x){
            cells[y][x] = Cell(x, y);
        }
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: is_initialized
 Synopsis: Checks if the field is initialized with valid dimensions and cells.
 ---------------------------------------------------------------------[>]-*/
bool Field::is_initialized() const {
    return width > 0 && height > 0;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_cell
 Synopsis: Returns a copy of the cell at (x, y).
 ---------------------------------------------------------------------[>]-*/
Cell& Field::get_cell(int x, int y) {
    if (!in_bounds(x, y)) {
        throw std::out_of_range("Coordinates out of bounds" + std::to_string(x) + ", " + std::to_string(y));
    }
    return cells[y][x];
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_cell
 Synopsis: Sets the cell at the specified coordinates.
 ---------------------------------------------------------------------[>]-*/
void Field::set_cell(const Cell& cell) {
    int x = cell.get_x();
    int y = cell.get_y();
    if (!in_bounds(x, y)) {
        throw std::out_of_range("Coordinates out of bounds" + std::to_string(x) + ", " + std::to_string(y));
    }
    cells[y][x] = cell;
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_cell_type
 Synopsis: Sets the type of the cell at (x, y).
 ---------------------------------------------------------------------[>]-*/
void Field::set_cell_type(const Cell& cell, CellType type) {
    int x = cell.get_x();
    int y = cell.get_y();
    if (!in_bounds(x, y)) {
        throw std::out_of_range("Coordinates out of bounds" + std::to_string(x) + ", " + std::to_string(y));
    }
    try {
        cells[y][x].set_type(type);
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Error setting cell: " + std::string(e.what()));
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: reset_all_dirs
 Synopsis: Resets directions of all cells in the field.
 ---------------------------------------------------------------------[>]-*/
void Field::reset_all_dirs() {
    for (auto& row : cells) {
        for (auto& cell : row) {
            cell.reset_dirs();
        }
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: reset_all_visited
 Synopsis: Resets visited status of all cells.
 ---------------------------------------------------------------------[>]-*/
void Field::reset_all_visited() {
    for (auto& row : cells) {
        for (auto& cell : row) {
            cell.set_visited(false);
        }
    }
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
    Field copy;
    copy.init(width, height);
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
    if (!is_initialized()) {
        std::wcerr << L"Field is not initialized." << std::endl;
        return;
    }

    int rows = get_height();
    int cols = get_width();

    std::wcout << L'┌';
    for (int x = 0; x < cols - 1; ++x)
        std::wcout << L"───┬";
    std::wcout << L"───┐\n";

    for (int y = 0; y < rows; ++y) {
        std::wcout << L'│';
        for (int x = 0; x < cols; ++x) {
            const Cell& cell = cells[y][x];

            wchar_t symbol = cell.get_symbol();

            wchar_t right_border = L'│';
            if (cell.get_exit_dir() == Direction::RIGHT || cell.get_entry_dir() == Direction::RIGHT) {
                right_border = L'┼';
            }

            std::wcout << L' ' << symbol << L' ' << right_border;
        }
        std::wcout << L'\n';

        if (y != rows - 1) {
            std::wcout << L'├';
            for (int x = 0; x < cols; ++x) {
                const Cell& cell = cells[y][x];

                if (cell.get_exit_dir() == Direction::DOWN || cell.get_entry_dir() == Direction::DOWN) {
                    std::wcout << L"─┼─";
                } else {
                    std::wcout << L"───";
                }

                if (x != cols - 1) {
                    std::wcout << L'┼';
                }
            }
            std::wcout << L'┤' << std::endl;
        }
    }

    std::wcout << L'└';
    for (int x = 0; x < cols - 1; ++x)
        std::wcout << L"───┴";
    std::wcout << L"───┘\n";
}
