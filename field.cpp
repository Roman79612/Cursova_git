#include "field.h"
#include <iostream>

using namespace std;

Field::Field(int rows, int cols) : rows(rows), cols(cols), grid(rows, vector<Cell>(cols)) {
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            grid[y][x] = Cell(x, y);
}

void Field::placeCircle(int x, int y, CellType type) {
    if (isInside(x, y)) grid[y][x].type = type;
}

bool Field::isInside(int x, int y) const {
    return x >= 0 && x < cols && y >= 0 && y < rows;
}

Cell& Field::getCell(int x, int y) {
    return grid[y][x];
}

int Field::getRows() const { return rows; }
int Field::getCols() const { return cols; }

bool Field::isValidWhite(int x, int y) const {
    return !(x == 0 && y == 0) &&
           !(x == 0 && y == rows - 1) &&
           !(x == cols - 1 && y == 0) &&
           !(x == cols - 1 && y == rows - 1);
}

void Field::print() const {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            switch (grid[y][x].type) {
                case CellType::BlackCircle: cout << "B "; break;
                case CellType::WhiteCircle: cout << "W "; break;
                default: cout << ". "; break;
            }
        }
        cout << '\n';
    }
}

bool Field::hasPrivilegedCells() const {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            CellType type = grid[y][x].type;
            if (type == CellType::BlackCircle || type == CellType::WhiteCircle) {
                return true;
            }
        }
    }
    return false;
}
