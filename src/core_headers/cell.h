/* ----------------------------------------------------------------<Header>-
 Name: cell.h
 Title: Cell class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-06
 Description: Header for representing a cell in the puzzle grid.
 ------------------------------------------------------------------</Header>-*/

#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <stdexcept>
#include <set>
#include <string>
#include "direction.h"

// Cell types
enum class CellType {
    EMPTY,
    BLACK,
    WHITE,
    LINE
};

// Represents a cell on the puzzle field
class Cell {
private:
    int x;
    int y;
    CellType type;
    bool visited;

    Direction dir_from;
    Direction dir_to;
    std::set<Direction> forbidden_dirs;

    wchar_t line_symbol;

public:
    Cell();
    Cell(int x, int y);
    Cell(int x, int y, CellType type);

    void set_symbol();
    void set_type(CellType new_type);
    void set_visited(bool state);
    void set_dir_from(Direction dir);
    void set_dir_to(Direction dir);
    void set_forbidden_dir(Direction dir);

    int get_x() const;
    int get_y() const;
    CellType get_type() const;
    wchar_t get_symbol() const;
    Direction get_dir_from() const;
    Direction get_dir_to() const;
    std::set<Direction> get_forbidden_dirs();

    void remove_forbidden_dir(Direction dir);
    void reset_dirs();

    bool is_valid_type(CellType type) const;
    bool is_black() const;
    bool is_white() const;
    bool is_line() const;
    bool is_empty() const;
    bool is_visited() const;
    bool is_forbidden_dir(Direction dir) const;
    bool is_forbid_overflow() const;
};

#endif // CELL_H
