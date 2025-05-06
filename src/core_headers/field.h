/* ----------------------------------------------------------------<Header>-
 Name: field.h
 Title: Field class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-05
 Description: Header file for managing the puzzle grid and its cells.
 ------------------------------------------------------------------</Header>-*/

#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <utility>
#include <vector>
#include <stdexcept>
#include <string>
#include "../core_headers/cell.h"
#include "../core_headers/direction.h"

class Field {
public:
    Field();
    void init(int width, int height);
    bool is_initialized() const;

    Cell& get_cell(int x, int y);
    int get_width() const;
    int get_height() const;

    void set_cell(const Cell& cell);
    void set_cell_type(const Cell& cell, CellType type);

    // Field-wide operations
    void reset_all_dirs();
    void reset_all_visited();
    void reset();
    Field clone() const;


    // Movement logic
    bool in_bounds(int x, int y) const; 
    bool can_go(int x, int y, Direction dir) const;
    std::vector<std::pair<int, int>> get_neighbors(int x, int y) const;
    std::vector<Direction> available_directions(int x, int y) const;

    // Display
    void print_field() const;

private:
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;
};

#endif // FIELD_H
