/* ----------------------------------------------------------------<Header>-
 Name: cell.cc
 Title: Cell class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Source file implementing the constructor for Cell.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/cell.h"

/* ---------------------------------------------------------------------[<]-
 Function: Cell::Cell
 Synopsis: Default constructor for an empty cell.
 ---------------------------------------------------------------------[>]-*/
Cell::Cell()
    : type(CellType::EMPTY)
{}

/* ---------------------------------------------------------------------[<]-
 Function: Cell::Cell
 Synopsis: Constructor with specific cell type.
 ---------------------------------------------------------------------[>]-*/
Cell::Cell(CellType type)
    : type(type)
{}

/* ---------------------------------------------------------------------[<]-
 Function: Cell::get_type
 Synopsis: Returns the current type of the cell.
 ---------------------------------------------------------------------[>]-*/
CellType Cell::get_type() const {
    return type;
}

/* ---------------------------------------------------------------------[<]-
 Function: Cell::set_type
 Synopsis: Sets the type of the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::set_type(CellType new_type) {
    type = new_type;
}

/* ---------------------------------------------------------------------[<]-
 Function: Cell::get_line_symbol
 Synopsis: Returns the Unicode symbol used for representing a line in the cell.
 ---------------------------------------------------------------------[>]-*/
wchar_t Cell::get_line_symbol() const {
    return line_symbol;
}

/* ---------------------------------------------------------------------[<]-
 Function: Cell::set_line_symbol
 Synopsis: Sets the Unicode symbol used for representing a line in the cell.
 ---------------------------------------------------------------------[>]-*/
void Cell::set_line_symbol(wchar_t symbol) {
    type = CellType::LINE;
    line_symbol = symbol;
}

/* ---------------------------------------------------------------------[<]-
 Function: Cell::is_white_dot
 Synopsis: Returns true if the cell contains a white dot.
 ---------------------------------------------------------------------[>]-*/
bool Cell::is_white_dot() const {
    return type == CellType::WHITE_DOT;
}

/* ---------------------------------------------------------------------[<]-
 Function: Cell::is_black_dot
 Synopsis: Returns true if the cell contains a black dot.
 ---------------------------------------------------------------------[>]-*/
bool Cell::is_black_dot() const {
    return type == CellType::BLACK_DOT;
}

/* ---------------------------------------------------------------------[<]-
 Function: Cell::is_empty
 Synopsis: Returns true if the cell is empty.
 ---------------------------------------------------------------------[>]-*/
bool Cell::is_empty() const {
    return type == CellType::EMPTY;
}

/* ----------------------------------------------------------------<Header>-
 Function: is_circle
 Synopsis: Checks if the cell represents a circle (white or black dot).
 Description: Returns true if the cell is a white or black dot, indicating it is a circle.
 ------------------------------------------------------------------</Header>-*/
bool Cell::is_circle() const {
    return type == CellType::WHITE_DOT || type == CellType::BLACK_DOT;
}

/* ---------------------------------------------------------------------[<]-
 Function: Cell::has_line
 Synopsis: Returns true if the cell contains a line.
 ---------------------------------------------------------------------[>]-*/
bool Cell::has_line() const {
    return type == CellType::LINE;
}

/* ----------------------------------------------------------------<Header>-
 Function: satisfy_circle_rule
 Synopsis: Checks if the cell satisfies the Masyu circle rule.
 Description: The circle rule in Masyu requires that a circle cell must either:
              1. Have a line passing through it.
              2. Have the line bent at the circle.
              If the circle cell violates any of these conditions, the rule is not satisfied.
 ------------------------------------------------------------------</Header>-*/
bool Cell::satisfy_circle_rule() const {
    // Example logic for circle rule:
    if (type == CellType::WHITE_DOT) {
        // White dot rule: Must have an unbroken line passing through it.
        // For simplicity, we assume a basic check for now
        return true; // Replace with your actual rule logic
    }
    if (type == CellType::BLACK_DOT) {
        // Black dot rule: Must have a line that bends at the dot.
        return true; // Replace with your actual rule logic
    }
    return false;
}

/* ----------------------------------------------------------------<Header>-
 Function: is_filled
 Synopsis: Checks if the cell is filled.
 Description: A filled cell is one that is not empty. For Masyu, a cell that is either a dot
              or contains a line symbol is considered filled.
 ------------------------------------------------------------------</Header>-*/
bool Cell::is_filled() const {
    // A cell is filled if it is not empty
    return type != CellType::EMPTY;
}
