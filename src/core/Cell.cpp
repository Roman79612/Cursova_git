#include "cell.hpp"

Cell::Cell(int x, int y, CellType type)
    : x_(x), y_(y), type_(type), visited_(false) {}

int Cell::get_x() const {
    return x_;
}

int Cell::get_y() const {
    return y_;
}

CellType Cell::get_type() const {
    return type_;
}

void Cell::set_type(CellType new_type) {
    type_ = new_type;
}

void Cell::mark_visited() {
    visited_ = true;
}

bool Cell::is_visited() const {
    return visited_;
}

void Cell::add_direction(Direction dir) {
    directions_.insert(dir);
}

const std::set<Direction> &Cell::get_directions() const {
    return directions_;
}
