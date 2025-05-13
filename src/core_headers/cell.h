/* ----------------------------------------------------------------<Header>-
 Name: cell.h
 Title: Cell class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-29
 Revised: 2025-05-14
 Description: Header for representing a cell in the puzzle grid.
 ------------------------------------------------------------------</Header>-*/

#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <stdexcept>
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

    Direction dir_from;
    Direction dir_to;
    Direction forb_dir1;
    Direction forb_dir2;

    wchar_t symbol;

public:
    //constructors
    Cell();
    Cell(int x, int y);
    Cell(int x, int y, CellType type);

    //Setters
    void set_type(CellType new_type);
    void set_dir_from(Direction dir);
    void set_dir_to(Direction dir);
    void set_forbidden_dir(Direction dir);

    //Getters
    int get_x() const;
    int get_y() const;
    CellType get_type() const;
    wchar_t get_symbol() const;
    wchar_t get_line() const;
    Direction get_dir_from() const;
    Direction get_dir_to() const;
    Direction get_forb_dir1() const;
    Direction get_forb_dir2() const;

    //Methods
    void remove_forbidden_dir(Direction dir);
    void reset_dirs();

    //Validators
    bool is_valid_type(CellType type) const;
    bool is_black() const;
    bool is_white() const;
    bool is_line() const;
    bool is_empty() const;
    bool is_forbidden_dir(Direction dir) const;
};

#endif // CELL_H
