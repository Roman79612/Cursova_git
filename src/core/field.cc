/* ----------------------------------------------------------------<Header>-
 Name: field.cpp
 Title: Field class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-06
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
    white_count = 0;
    black_count = 0;
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
    white_count = has_white_cell();
    black_count = has_black_cell();
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
 Function: get_white_count
 Synopsis: Returns the number of white cells in the field.
 ---------------------------------------------------------------------[>]-*/
int Field::get_white_count() const {
    return white_count;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_black_count
 Synopsis: Returns the number of black cells in the field.
 ---------------------------------------------------------------------[>]-*/
int Field::get_black_count() const {
    return black_count;
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
 Function: has_white_cell
 Synopsis: Checks if there are any white cells in the field.
 ---------------------------------------------------------------------[>]-*/
bool Field::has_white_cell() {
    white_count = 0;
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            if (cell.get_type() == CellType::WHITE) {
                ++white_count;
            }
        }
    }
    return white_count > 0;
}

/* ---------------------------------------------------------------------[<]- 
 Function: has_black_cell
 Synopsis: Checks if there are any black cells in the field.
 ---------------------------------------------------------------------[>]-*/
bool Field::has_black_cell() {
    black_count = 0;
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            if (cell.get_type() == CellType::BLACK) {
                ++black_count;
            }
        }
    }
    return black_count > 0; 
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_white_cells
 Synopsis: Returns coordinates of all white cells in the field.
 ---------------------------------------------------------------------[>]-*/
std::vector<Cell*> Field::get_white_cells() {
    std::vector<Cell*> white_cells;
    for (auto& row : cells) {
        for (auto& cell : row) {
            if (cell.get_type() == CellType::WHITE) {
                white_cells.push_back(&cell);
            }
        }
    }
    return white_cells;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_black_cells
 Synopsis: Returns coordinates of all black cells in the field.
 ---------------------------------------------------------------------[>]-*/
std::vector<Cell*> Field::get_black_cells() {
    std::vector<Cell*> black_cells;
    for (auto& row : cells) {
        for (auto& cell : row) {
            if (cell.get_type() == CellType::BLACK) {
                black_cells.push_back(&cell);
            }
        }
    }
    return black_cells;
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

    print_top_border();

    for (int y = 0; y < get_height(); ++y) {
        print_row_cells(y);
        if (y != get_height() - 1) {
            print_row_separator(y);
        }
    }

    print_bottom_border();
}

/* ---------------------------------------------------------------------[<]- 
 Function: print_top_border
 Synopsis: Prints the top border of the field.
 ---------------------------------------------------------------------[>]-*/
void Field::print_top_border() const {
    std::wcout << L'┌';
    for (int x = 0; x < get_width() - 1; ++x)
        std::wcout << L"───┬";
    std::wcout << L"───┐\n";
}

/* ---------------------------------------------------------------------[<]- 
 Function: print_row_cells
 Synopsis: Prints the cells in a row with their symbols and borders.
 ---------------------------------------------------------------------[>]-*/
void Field::print_row_cells(int y) const {
    std::wcout << L'│';
    int max_x = get_width();
    for (int x = 0; x < max_x; ++x) {
        const Cell& cell = cells[y][x];
        CellType type = cell.get_type();
        Direction in = cell.get_entry_dir();
        Direction out = cell.get_exit_dir();
        wchar_t symbol = cell.get_symbol();

        bool dir_left  = (in == Direction::LEFT || out == Direction::LEFT);
        bool dir_right = (in == Direction::RIGHT || out == Direction::RIGHT);
        bool is_dot = (type == CellType::WHITE || type == CellType::BLACK);

        if (cell.is_line()) {
            if (dir_left) {
                std::wcout << L"\b\x1b[32m" << L'┼' << L" " << symbol << L" \x1b[0m" << L"│";
            } else if (dir_right) {
                std::wcout << L"\x1b[32m " << symbol << L" " << L"┼\x1b[0m";
            } else {
                std::wcout << L"\x1b[32m " << symbol << L" \x1b[0m" << L"│";
            }
        } else if (is_dot) {
            if (dir_left) {
                std::wcout << L"\b\x1b[32m" << L'┼' << L" \x1b[0m" << symbol << L" " << L"│";
            } else if (dir_right) {
                std::wcout << L"\x1b[0m " << symbol << L" " << L"\x1b[32m┼\x1b[0m";
            } else {
                std::wcout << L" " << symbol << L" " << L"│";
            }
        } else {
            if (dir_left) {
                std::wcout << L"\b\x1b[32m" << L'┼' << L" \x1b[0m" << symbol << L" " << L"│";
            } else if (dir_right) {
                std::wcout << L"\x1b[0m " << symbol << L" " << L"\x1b[32m┼\x1b[0m";
            } else {
                std::wcout << L" " << symbol << L" " << L"│";
            }
        }
    }
    std::wcout << L'\n';
}


/* ---------------------------------------------------------------------[<]- 
 Function: print_row_separator
 Synopsis: Prints the separator between rows.
 ---------------------------------------------------------------------[>]-*/
void Field::print_row_separator(int y) const {
    std::wcout << L'├';
    for (int x = 0; x < get_width(); ++x) {
        const Cell& cell = cells[y][x];
        Direction in = cell.get_entry_dir();
        Direction out = cell.get_exit_dir();

        bool dir_up = (in == Direction::UP || out == Direction::UP);
        bool dir_down = (in == Direction::DOWN || out == Direction::DOWN);

        if (dir_up && dir_down) {
            std::wcout << L"\x1b[2A\x1b[3C\b\b\b─\x1b[32m┼\x1b[0m─\x1b[3D\x1b[2B";
            std::wcout << L"─\x1b[32m┼\x1b[0m─";
        } else if (dir_up) {
            std::wcout << L"\x1b[2A\x1b[3C\b\b\b─\x1b[32m┼\x1b[0m─\x1b[3D\x1b[2B";
            std::wcout << L"───";
        } else if (dir_down) {
            std::wcout << L"─\x1b[32m┼\x1b[0m─";
        } else {
            std::wcout << L"───";
        }


        if (x != get_width() - 1) {
            std::wcout << L'┼';
        }
    }
    std::wcout << L'┤' << std::endl;
}

/* ---------------------------------------------------------------------[<]- 
 Function: print_bottom_border
 Synopsis: Prints the bottom border of the field.
 ---------------------------------------------------------------------[>]-*/
void Field::print_bottom_border() const {
    std::wcout << L'└';
    for (int x = 0; x < get_width() - 1; ++x)
        std::wcout << L"───┴";
    std::wcout << L"───┘\n";
}
