/* ----------------------------------------------------------------<Header>-
 Name: field.h
 Title: Field class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Header file for managing the puzzle grid and its cells.
 ------------------------------------------------------------------</Header>-*/

#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <ostream>
#include <vector>
#include "../core_headers/cell.h"
#include "../core_headers/direction.h"

class Field {
public:
    Field(int width, int height);

    Cell get_cell(int x, int y) const;
    void set_cell(int x, int y, Cell cell);

    bool in_bounds(int x, int y) const;

    int get_width() const;
    int get_height() const;
    void print_initial_state() const;
    void print_final_state() const;
    void reset();

    Field clone() const;

    std::vector<std::pair<int, int>> get_neighbors(int x, int y) const;

private:
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;
};

#endif // FIELD_H
