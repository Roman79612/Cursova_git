/* ----------------------------------------------------------------<Header>-
 Name: cell.h
 Title: Cell class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Header file for representing a single cell in the puzzle grid.
 ------------------------------------------------------------------</Header>-*/

#ifndef CELL_H
#define CELL_H

// Enum for cell types
enum class CellType {
    EMPTY,
    WHITE_DOT,
    BLACK_DOT,
    LINE
};

// Class representing a cell on the field
class Cell {
public:
    Cell();
    explicit Cell(CellType type);

    CellType get_type() const;
    void set_type(CellType new_type);
    wchar_t get_line_symbol() const;
    void set_line_symbol(wchar_t symbol);

    bool is_white_dot() const;
    bool is_black_dot() const;
    bool is_empty() const;
    bool is_circle() const;
    bool satisfy_circle_rule() const;
    bool has_line() const;
    bool is_filled() const;

private:
    CellType type;
    wchar_t line_symbol;
};

#endif // CELL_H
