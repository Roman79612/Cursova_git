/* ----------------------------------------------------------------<Header>-
 Name: cell.cpp
 Title: Cell class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-29
 Revised: 2025-05-14
 Description: Implementation of the Cell class for handling puzzle grid cells, handling directions.
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
    dir_from = Direction::NONE;
    dir_to = Direction::NONE;
    forb_dir1 = Direction::NONE;
    forb_dir2 = Direction::NONE;
    symbol = get_symbol();
}

/* ----------------------------------------------------------------<Function>-
 Cell::Cell
 Constructor that initializes a cell at position (x, y) with a given type.
 ------------------------------------------------------------------ */
Cell::Cell(int x, int y) {
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Coordinates must be non-negative" + std::to_string(x) + ", " + std::to_string(y));
    }
    this->x = x;
    this->y = y;
    type = CellType::EMPTY;
    dir_from = Direction::NONE;
    dir_to = Direction::NONE;
    forb_dir1 = Direction::NONE;
    forb_dir2 = Direction::NONE;
    symbol = get_symbol();
}

/* ---------------------------------------------------------------------[<]- 
 Function: Cell
 Synopsis: Constructor to initialize the cell with coordinates and type.
 ---------------------------------------------------------------------[>]-*/
Cell::Cell(int x, int y, CellType type) {
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Coordinates must be non-negative" + std::to_string(x) + ", " + std::to_string(y));
    } 
    if (!is_valid_type(type)) {
        throw std::invalid_argument("Invalid cell type" + std::to_string(static_cast<int>(type)));
    }
    this->x = x;
    this->y = y;
    this->type = type;
    dir_from = Direction::NONE;
    dir_to = Direction::NONE;
    forb_dir1 = Direction::NONE;
    forb_dir2 = Direction::NONE;
    symbol = get_symbol();
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_type
 Synopsis: Set the type of the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::set_type(CellType new_type) {
    if (!is_valid_type(new_type)) {
        throw std::invalid_argument("Invalid cell type" + std::to_string(static_cast<int>(new_type)));
    }
    if (type == CellType::EMPTY) {
        type = new_type;
        symbol = get_symbol();
    } 
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_dir_from
 Synopsis: Set the entry direction for the line into the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::set_dir_from(Direction dir) {
    if (!DirectionHelper::is_valid_direction(dir)) {
        throw std::invalid_argument("Invalid direction for dir_from: " + std::to_string(static_cast<int>(dir)));
    }

    dir_from = dir;
    if (type == CellType::EMPTY && dir_from != Direction::NONE && dir_to != Direction::NONE) {
        type = CellType::LINE;
    }
    symbol = get_symbol();
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_dir_to
 Synopsis: Set the exit direction for the line out of the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::set_dir_to(Direction dir) {
    if (!DirectionHelper::is_valid_direction(dir)) {
        throw std::invalid_argument("Invalid direction for dir_to: " + std::to_string(static_cast<int>(dir)));
    }
    
    dir_to = dir;
    if (type == CellType::EMPTY && dir_from != Direction::NONE && dir_to != Direction::NONE) {
        type = CellType::LINE;
    }
    symbol = get_symbol();
}

/* ---------------------------------------------------------------------[<]- 
 Function: set_forbidden_dir
 Synopsis: Set a directions as forbidden for the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::set_forbidden_dir(Direction dir) {
    if (forb_dir1 == Direction::NONE) {
        forb_dir1 = dir;
    } else {
        forb_dir2 = dir;
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
    if (type == CellType::EMPTY && dir_from != Direction::NONE && dir_to != Direction::NONE) {
        return CellType::LINE;
    }
    return type;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_symbol
 Synopsis: Get the line symbol based on the entry and exit directions.
 ---------------------------------------------------------------------[>]-*/
wchar_t Cell::get_symbol() const {
    if (type == CellType::LINE) {
        return get_line();
    } else if (type == CellType::WHITE) {
        return L'●';
    } else if (type == CellType::BLACK) {
        return L'○';
    } else if (type == CellType::EMPTY && (dir_from == Direction::NONE || dir_to == Direction::NONE)) {
        return L' ';
    } else if (type == CellType::EMPTY && dir_from != Direction::NONE && dir_to != Direction::NONE) {
        return get_line();
    } else {
        return L'?';
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_line
 Synopsis: Get the line symbol based on the entry and exit directions.
 ---------------------------------------------------------------------[>]-*/
 wchar_t Cell::get_line() const {
    if ((dir_from == Direction::UP && dir_to == Direction::DOWN) ||
            (dir_from == Direction::DOWN && dir_to == Direction::UP)) {
            return L'│';
        }

        if ((dir_from == Direction::LEFT && dir_to == Direction::RIGHT) ||
            (dir_from == Direction::RIGHT && dir_to == Direction::LEFT)) {
            return L'─';
        }

        if ((dir_from == Direction::UP && dir_to == Direction::RIGHT) ||
            (dir_from == Direction::RIGHT && dir_to == Direction::UP)) {
            return L'└';
        }

        if ((dir_from == Direction::UP && dir_to == Direction::LEFT) ||
            (dir_from == Direction::LEFT && dir_to == Direction::UP)) {
            return L'┘';
        }

        if ((dir_from == Direction::DOWN && dir_to == Direction::RIGHT) ||
            (dir_from == Direction::RIGHT && dir_to == Direction::DOWN)) {
            return L'┌';
        }

        if ((dir_from == Direction::DOWN && dir_to == Direction::LEFT) ||
            (dir_from == Direction::LEFT && dir_to == Direction::DOWN)) {
            return L'┐';
        }
        return L'?';
 }

/* ---------------------------------------------------------------------[<]- 
 Function: get_dir_from
 Synopsis: Get the entry direction of the line into the cell.
 ---------------------------------------------------------------------[>]-*/
Direction Cell::get_dir_from() const{
    return dir_from;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_dir_to
 Synopsis: Get the exit direction of the line out of the cell.
 ---------------------------------------------------------------------[>]-*/
Direction Cell::get_dir_to() const{
    return dir_to;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_forb_dir1
 Synopsis: Get the forbidden direction of the cell.
 ---------------------------------------------------------------------[>]-*/
Direction Cell::get_forb_dir1() const{
    return forb_dir1;
}

/* ---------------------------------------------------------------------[<]- 
 Function: get_forb_dir2
 Synopsis: Get the forbidden direction of the cell.
 ---------------------------------------------------------------------[>]-*/
Direction Cell::get_forb_dir2() const{
    return forb_dir2;
}

/* ---------------------------------------------------------------------[<]- 
 Function: reset_dirs
 Synopsis: Reset both directions (entry and exit) to the default (UP).
 ---------------------------------------------------------------------[>]-*/
void Cell::reset_dirs() {
    dir_from = Direction::NONE;
    dir_to = Direction::NONE;
    forb_dir1 = Direction::NONE;
    forb_dir2 = Direction::NONE;
}

/* ---------------------------------------------------------------------[<]- 
 Function: remove_forbidden_dir
 Synopsis: Remove a direction from the forbidden list for the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::remove_forbidden_dir(Direction dir) {
    if (forb_dir1 == dir) {
        forb_dir1 = Direction::NONE;
    } else if (forb_dir2 == dir) {
        forb_dir2 = Direction::NONE;
    } else {
        return;
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: is_valid_type
 Synopsis: Check if the cell type is valid.
 ---------------------------------------------------------------------[>]-*/
bool Cell::is_valid_type(CellType type) const {
    return type == CellType::EMPTY || type == CellType::BLACK || type == CellType::WHITE || type == CellType::LINE;
}

/* ---------------------------------------------------------------------[<]- 
 Function: is_black
 Synopsis: Check if the cell is black.
 ---------------------------------------------------------------------[>]-*/
bool Cell::is_black() const {
    return type == CellType::BLACK;
}

/* ---------------------------------------------------------------------[<]- 
 Function: is_white
 Synopsis: Check if the cell is white.
 ---------------------------------------------------------------------[>]-*/
bool Cell::is_white() const {
    return type == CellType::WHITE;
}

/* ---------------------------------------------------------------------[<]- 
 Function: is_line
 Synopsis: Check if the cell is a line.
 ---------------------------------------------------------------------[>]-*/
 bool Cell::is_line() const {
    return (type == CellType::LINE || (type == CellType::EMPTY && dir_from != Direction::NONE && dir_to != Direction::NONE));
}

/* ---------------------------------------------------------------------[<]- 
 Function: is_empty
 Synopsis: Check if the cell is empty.
 ---------------------------------------------------------------------[>]-*/
bool Cell::is_empty() const {
    return type == CellType::EMPTY;
}

/* ---------------------------------------------------------------------[<]- 
 Function: is_dir_forbidden
 Synopsis: Check if a direction is forbidden for the cell.
 ---------------------------------------------------------------------[>]-*/
bool Cell::is_forbidden_dir(Direction dir) const {
    return forb_dir1 == dir || forb_dir2 == dir;
}