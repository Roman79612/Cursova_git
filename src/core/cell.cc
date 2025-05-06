/* ----------------------------------------------------------------<Header>-
 Name: cell.cpp
 Title: Cell class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-05
 Description: Implementation of the Cell class for handling puzzle grid cells,
              including handling directions and cell states.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/cell.h"

/* ---------------------------------------------------------------------[<]- 
 Function: Cell
 Synopsis: Default constructor initializes a cell at (0, 0) with type EMPTY.
 ---------------------------------------------------------------------[>]-*/
Cell::Cell() {
    x = 0;
    y = 0;
    type = CellType::EMPTY;
    visited = false;
    entry_dir = Direction::NONE;
    exit_dir = Direction::NONE;
    line_symbol = get_symbol();
}

/* ----------------------------------------------------------------<Function>-
 Cell::Cell
 Constructor that initializes a cell at position (x, y) with a given type.
 ------------------------------------------------------------------ */
Cell::Cell(int x, int y) {
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Coordinates must be non-negative" + std::to_string(x) + ", " + std::to_string(y));
    } else {
        this->x = x;
        this->y = y;
        type = CellType::EMPTY;
        visited = false;
        entry_dir = Direction::NONE;
        exit_dir = Direction::NONE;
        line_symbol = get_symbol();
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: Cell
 Synopsis: Constructor to initialize the cell with coordinates and type.
 ---------------------------------------------------------------------[>]-*/
Cell::Cell(int x, int y, CellType type) {
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Coordinates must be non-negative" + std::to_string(x) + ", " + std::to_string(y));
    } else if (!is_valid_type(type)) {
        throw std::invalid_argument("Invalid cell type" + std::to_string(static_cast<int>(type)));
    } else {
        this->x = x;
        this->y = y;
        this->type = type;
        visited = false;
        entry_dir = Direction::NONE;
        exit_dir = Direction::NONE;
        line_symbol = get_symbol();
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_x
 Synopsis: Getter for the x-coordinate of the cell.
 ---------------------------------------------------------------------[>]-*/
int Cell::get_x() const {
    return x;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_y
 Synopsis: Getter for the y-coordinate of the cell.
 ---------------------------------------------------------------------[>]-*/
int Cell::get_y() const {
    return y;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_type
 Synopsis: Getter for the type of the cell.
 ---------------------------------------------------------------------[>]-*/
CellType Cell::get_type() const {
    return type;
}

/* ---------------------------------------------------------------------[<]- 
 Function: is_visited
 Synopsis: Check if the cell has been visited.
 ---------------------------------------------------------------------[>]-*/
bool Cell::is_visited() const {
    return visited;
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_type
 Synopsis: Set the type of the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::set_type(CellType new_type) {
    if (!is_valid_type(new_type)) {
        throw std::invalid_argument("Invalid cell type" + std::to_string(static_cast<int>(new_type)));
    } else {
        type = new_type;
        set_symbol();
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_visited
 Synopsis: Set the visited status of the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::set_visited(bool state) {
    visited = state;
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_entry_dir
 Synopsis: Set the entry direction for the line into the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::set_entry_dir(Direction dir) {
    if (DirectionHelper::is_valid_direction(dir)) {
        if (exit_dir == dir && dir != Direction::NONE) {
            entry_dir = Direction::NONE;
            exit_dir = Direction::NONE;
        }
        entry_dir = dir;
    } else {
        throw std::invalid_argument("Invalid direction for entry_dir" + std::to_string(static_cast<int>(dir)));
    }
    set_symbol();
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_exit_dir
 Synopsis: Set the exit direction for the line out of the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::set_exit_dir(Direction dir) {
    if (DirectionHelper::is_valid_direction(dir)) {
        if (entry_dir == dir && dir != Direction::NONE) {
            entry_dir = Direction::NONE;
            exit_dir = Direction::NONE;
        }
        exit_dir = dir;
    } else {
        throw std::invalid_argument("Invalid direction for exit_dir" + std::to_string(static_cast<int>(dir)));
    }
    set_symbol();
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_entry_dir
 Synopsis: Get the entry direction of the line into the cell.
 ---------------------------------------------------------------------[>]-*/
Direction Cell::get_entry_dir() const {
    return entry_dir;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_exit_dir
 Synopsis: Get the exit direction of the line out of the cell.
 ---------------------------------------------------------------------[>]-*/
Direction Cell::get_exit_dir() const {
    return exit_dir;
}

/* ---------------------------------------------------------------------[<]- 
 Function: reset_dirs
 Synopsis: Reset both directions (entry and exit) to the default (UP).
 ---------------------------------------------------------------------[>]-*/
void Cell::reset_dirs() {
    entry_dir = Direction::NONE;
    exit_dir = Direction::NONE;
}

/* ----------------------------------------------------------------<Function>-
 void Cell::set_line_symbol
 Sets the visual symbol for the line in this cell.
 ------------------------------------------------------------------ */
void Cell::set_symbol() {
    line_symbol = get_symbol();
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_line_symbol
 Synopsis: Set the line symbol based on the entry and exit directions.
 ---------------------------------------------------------------------[>]-*/
wchar_t Cell::get_symbol() const {
    if (type == CellType::LINE) {
        if ((entry_dir == Direction::UP && exit_dir == Direction::DOWN) ||
            (entry_dir == Direction::DOWN && exit_dir == Direction::UP) ||
            (entry_dir == Direction::NONE && exit_dir == Direction::DOWN) ||
            (entry_dir == Direction::DOWN && exit_dir == Direction::NONE) ||
            (entry_dir == Direction::UP && exit_dir == Direction::NONE) ||
            (entry_dir == Direction::NONE && exit_dir == Direction::UP)) {
            return L'│';
        }

        if ((entry_dir == Direction::LEFT && exit_dir == Direction::RIGHT) ||
            (entry_dir == Direction::RIGHT && exit_dir == Direction::LEFT) ||
            (entry_dir == Direction::NONE && exit_dir == Direction::RIGHT) ||
            (entry_dir == Direction::RIGHT && exit_dir == Direction::NONE) ||
            (entry_dir == Direction::LEFT && exit_dir == Direction::NONE) ||
            (entry_dir == Direction::NONE && exit_dir == Direction::LEFT)) {
            return L'─';
        }

        if ((entry_dir == Direction::UP && exit_dir == Direction::RIGHT) ||
            (entry_dir == Direction::RIGHT && exit_dir == Direction::UP)) {
            return L'┐';
        }

        if ((entry_dir == Direction::UP && exit_dir == Direction::LEFT) ||
            (entry_dir == Direction::LEFT && exit_dir == Direction::UP)) {
            return L'┌';
        }

        if ((entry_dir == Direction::DOWN && exit_dir == Direction::RIGHT) ||
            (entry_dir == Direction::RIGHT && exit_dir == Direction::DOWN)) {
            return L'┘';
        }

        if ((entry_dir == Direction::DOWN && exit_dir == Direction::LEFT) ||
            (entry_dir == Direction::LEFT && exit_dir == Direction::DOWN)) {
            return L'└';
        }
        return L'?';

    } else if (type == CellType::WHITE) {
        return L'●';
    } else if (type == CellType::BLACK) {
        return L'○';
    } else if (type == CellType::EMPTY) {
        return L' ';
    } else {
        return L'?';
    }
}

bool Cell::is_valid_type(CellType type) const {
    return type == CellType::EMPTY || type == CellType::BLACK || type == CellType::WHITE || type == CellType::LINE;
}
