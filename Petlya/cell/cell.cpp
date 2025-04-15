#include "cell.h"

Cell::Cell(int x, int y, CellType type) : x(x), y(y), type(type) {}

bool Cell::isPrivileged() const {
    return type == CellType::WhiteCircle || type == CellType::BlackCircle;
}
