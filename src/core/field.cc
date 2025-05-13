/* ----------------------------------------------------------------<Header>-
 Name: field.cpp
 Title: Field class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-29
 Revised: 2025-05-14
 Description: Implementation of the Field class for managing grid, access, validation.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/field.h"

/* ---------------------------------------------------------------------[<]- 
 Function: Field
 Synopsis: Default constructor initializes a field with no cells.
 ---------------------------------------------------------------------[>]-*/
Field::Field() {}

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
 Function: get_cell
 Synopsis: Returns the cell at (x, y).
 ---------------------------------------------------------------------[>]-*/
Cell& Field::get_cell(int x, int y) {
    if (!in_bounds(x, y)) {
        throw std::out_of_range("Coordinates out of bounds " + std::to_string(x) + ", " + std::to_string(y));
    }
    return cells[y][x];
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
 Function: get_neighbors
 Synopsis: Returns valid (x, y) coordinates of neighboring cells.
 ---------------------------------------------------------------------[>]-*/
std::vector<Cell*> Field::get_neighbors(Cell &cell) {
    std::vector<Cell*> neighbors;

    for (Direction dir : DirectionHelper::get_all_dirs()) {
        int nx = cell.get_x() + DirectionHelper::get_dx(dir);
        int ny = cell.get_y() + DirectionHelper::get_dy(dir);

        if (in_bounds(nx, ny)) {
            neighbors.push_back(&get_cell(nx, ny));
        }
    }

    return neighbors;
}

/* ---------------------------------------------------------------------[<]- 
 Function: available_directions
 Synopsis: Returns list of directions available from (x, y).
 ---------------------------------------------------------------------[>]-*/
std::vector<Direction> Field::get_available_directions(Cell &cell) {
    std::vector<Direction> available;

    for (Direction dir : DirectionHelper::get_all_dirs()) {
        if (!cell.is_forbidden_dir(dir)) {
            available.push_back(dir);
        }
    }

    return available;
}


/* ---------------------------------------------------------------------[<]- 
 Function: get_white_cells
 Synopsis: Returns coordinates of all white cells in the field.
 ---------------------------------------------------------------------[>]-*/
std::vector<Cell*> Field::get_white_cells() {
    std::vector<Cell*> white_cells;
    for (std::vector<Cell>& row : cells) {
        for (Cell& cell : row) {
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
    for (std::vector<Cell>& row : cells) {
        for (Cell& cell : row) {
            if (cell.get_type() == CellType::BLACK) {
                black_cells.push_back(&cell);
            }
        }
    }
    return black_cells;
}

/* ---------------------------------------------------------------------[<]- 
 Function: reset_all_dirs
 Synopsis: Resets directions of all cells in the field.
 ---------------------------------------------------------------------[>]-*/
void Field::reset_all_dirs() {
    for (std::vector<Cell>& row : cells) {
        for (Cell& cell : row) {
            cell.reset_dirs();
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
 Function: can_go_in_steps
 Synopsis: Checks if movement from (x, y) in direction is within bounds on N steps.
 ---------------------------------------------------------------------[>]-*/
bool Field::can_go_in_steps(int x, int y, Direction dir, int steps) const {
    int dx = DirectionHelper::get_dx(dir);
    int dy = DirectionHelper::get_dy(dir);

    for (int i = 1; i <= steps; ++i) {
        int nx = x + dx * i;
        int ny = y + dy * i;

        if (!in_bounds(nx, ny)) {
            return false;
        }
    }

    return true;
}

/* ---------------------------------------------------------------------[<]- 
 Function: has_white_cell
 Synopsis: Checks if there are any white cells in the field.
 ---------------------------------------------------------------------[>]-*/
bool Field::has_white_cell() {
    for (const std::vector<Cell>& row : cells) {
        for (const Cell& cell : row) {
            if (cell.get_type() == CellType::WHITE) {
                return true;
            }
        }
    }
    return false;
}

/* ---------------------------------------------------------------------[<]- 
 Function: has_black_cell
 Synopsis: Checks if there are any black cells in the field.
 ---------------------------------------------------------------------[>]-*/
bool Field::has_black_cell() {
    for (const std::vector<Cell>& row : cells) {
        for (const Cell& cell : row) {
            if (cell.get_type() == CellType::BLACK) {
                return true;
            }
        }
    }
    return false; 
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
    std::wcout << BOLD << L'┌';
    for (int x = 0; x < get_width() - 1; ++x)
        std::wcout << L"───┬";
    std::wcout << L"───┐" << RESET_COLOUR << std::endl;
}

/* ---------------------------------------------------------------------[<]- 
 Function: print_row_cells
 Synopsis: Prints the cells in a row with their symbols and borders.
 ---------------------------------------------------------------------[>]-*/
void Field::print_row_cells(int y) const {
    std::wcout << BOLD << L'│';
    int max_x = get_width();
    for (int x = 0; x < max_x; ++x) {
        const Cell& cell = cells[y][x];
        Direction in = cell.get_dir_from();
        Direction out = cell.get_dir_to();
        
        CellType type = cell.get_type();
        wchar_t symbol = cell.get_symbol();

        bool dir_left  = (in == Direction::LEFT || out == Direction::LEFT);
        bool dir_right = (in == Direction::RIGHT || out == Direction::RIGHT);
        bool is_dot = (type == CellType::WHITE || type == CellType::BLACK);

        if (type == CellType::LINE || (type == CellType::EMPTY && in != Direction::NONE && out != Direction::NONE)) {
            symbol = cell.get_line();
        }

        if (cell.is_line()) {
            if (dir_left) {
                ui::backspace(1);
                std::wcout << BOLD << GREEN << L'┼' << L" " << symbol << L" " << RESET_COLOUR << BOLD << L"│" << RESET_COLOUR;
            } else if (dir_right) {
                std::wcout << BOLD << GREEN << L" " << symbol << L" " << L"┼" << RESET_COLOUR;
            } else {
                std::wcout << BOLD << GREEN << L" " << symbol << L" " << RESET_COLOUR << BOLD << L"│" << RESET_COLOUR;
            }
        } else if (is_dot) {
            if (dir_left) {
                ui::backspace(1);
                std::wcout << BOLD << GREEN << L'┼' << L" " << RESET_COLOUR << symbol << L" " << L"│" << RESET_COLOUR;
            } else if (dir_right) {
                std::wcout << BOLD << RESET_COLOUR << L" " << symbol << L" " << GREEN << L"┼" << RESET_COLOUR;
            } else {
                std::wcout << BOLD << L" " << symbol << L" " << L"│" << RESET_COLOUR;
            }
        } else {
            if (dir_left) {
                ui::backspace(1);
                std::wcout << BOLD << GREEN << L'┼' << L" " << RESET_COLOUR << symbol << L" " << L"│" << RESET_COLOUR;
            } else if (dir_right) {
                std::wcout << BOLD << GREEN << L" " << symbol << L" " << L"┼" << RESET_COLOUR;
            } else {
                std::wcout << BOLD << GREEN << L" " << symbol << L" " << RESET_COLOUR << BOLD << L"│" << RESET_COLOUR;
            }
        }
    }
    std::wcout << RESET_COLOUR << std::endl;
}


/* ---------------------------------------------------------------------[<]- 
 Function: print_row_separator
 Synopsis: Prints the separator between rows.
 ---------------------------------------------------------------------[>]-*/
void Field::print_row_separator(int y) const {
    std::wcout << BOLD << L'├';
    for (int x = 0; x < get_width(); ++x) {
        const Cell& cell = cells[y][x];
        Direction in = cell.get_dir_from();
        Direction out = cell.get_dir_to();
        Direction forb_1 = cell.get_forb_dir1();
        Direction forb_2 = cell.get_forb_dir2();

        bool dir_up = (in == Direction::UP || out == Direction::UP);
        bool dir_down = (in == Direction::DOWN || out == Direction::DOWN);
        bool forb_up = (forb_1 == Direction::UP || forb_2 == Direction::UP);
        bool forb_down = (forb_2 == Direction::DOWN || forb_2 == Direction::DOWN);

        if (dir_up && dir_down && !forb_up && !forb_down) {
            ui::move_cursor_up(2);
            ui::move_cursor_right(3);
            ui::move_cursor_left(3);
            std::wcout << BOLD << L'─' << GREEN << L'┼' << RESET_COLOUR << BOLD << L'─' << RESET_COLOUR;
            ui::move_cursor_down(2);
            ui::move_cursor_left(3);
            std::wcout << BOLD << L'─' << GREEN << L'┼' << RESET_COLOUR << L'─' << RESET_COLOUR;
        } else if (dir_up && !forb_up) {
            ui::move_cursor_up(2);
            ui::move_cursor_right(3);
            ui::move_cursor_left(3);
            std::wcout << BOLD << L'─' << GREEN << L'┼' << RESET_COLOUR << L'─' << RESET_COLOUR;
            ui::move_cursor_down(2);
            ui::move_cursor_left(3);
            std::wcout << BOLD << L"───";
        } else if (dir_down && !forb_down) {
            std::wcout << BOLD << L'─' << GREEN << L'┼' << RESET_COLOUR << L'─' << RESET_COLOUR;
        } else {
            std::wcout << BOLD << L"───" << RESET_COLOUR;
        }

        if (x != get_width() - 1) {
            std::wcout << BOLD << L'┼' << RESET_COLOUR;
        }
    }
    std::wcout << BOLD << L'┤' << RESET_COLOUR << std::endl;
}

/* ---------------------------------------------------------------------[<]- 
 Function: print_bottom_border
 Synopsis: Prints the bottom border of the field.
 ---------------------------------------------------------------------[>]-*/
void Field::print_bottom_border() const {
    std::wcout << BOLD << L'└';
    for (int x = 0; x < get_width() - 1; ++x)
        std::wcout << L"───┴";
    std::wcout << L"───┘" << RESET_COLOUR << std::endl;
}
