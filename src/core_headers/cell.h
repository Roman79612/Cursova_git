/* ----------------------------------------------------------------<Header>-
 Name: cell.h
 Title: Cell class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-05
 Description: Header for representing a cell in the puzzle grid.
 ------------------------------------------------------------------</Header>-*/

#ifndef CELL_H
#define CELL_H

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

    Direction entry_dir;
    Direction exit_dir;

    wchar_t line_symbol;

public:
    Cell();
    Cell(int x, int y);
    Cell(int x, int y, CellType type);

    int get_x() const;
    int get_y() const;
    CellType get_type() const;
    bool is_visited() const;

    void set_type(CellType new_type);
    void set_visited(bool state);

    void set_entry_dir(Direction dir);
    void set_exit_dir(Direction dir);
    Direction get_entry_dir() const;
    Direction get_exit_dir() const;

    void reset_dirs();
    void set_symbol();
    wchar_t get_symbol() const;
};

#endif // CELL_H
