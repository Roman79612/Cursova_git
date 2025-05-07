/* ----------------------------------------------------------------<Header>-
 Name: field.h
 Title: Field class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-06
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
#include "../utils/ui.h"

class Field {
public:
    Field();
    void init(int width, int height);
    bool is_initialized() const;

    Cell& get_cell(int x, int y);
    int get_width() const;
    int get_height() const;
    int get_white_count() const;
    int get_black_count() const;

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
    bool has_white_cell();
    bool has_black_cell();
    std::vector<std::pair<int, int>> get_neighbors(int x, int y) const;
    std::vector<Direction> available_directions(int x, int y) const;
    std::vector<Cell*> get_white_cells();
    std::vector<Cell*> get_black_cells();

    void print_field() const;

private:
    int width;
    int height;
    int white_count;
    int black_count;
    std::vector<std::vector<Cell>> cells;

    // Display
    void print_top_border() const;
    void print_bottom_border() const;
    void print_row_cells(int y) const;
    void print_row_separator(int y) const;
};

#endif // FIELD_H
