#pragma once
#include <vector>
#include "cell.h"

using namespace std;
class Field {
private:
    int rows, cols;
    vector<vector<Cell>> grid;
public:
    Field(int rows, int cols);
    void placeCircle(int x, int y, CellType type);
    bool isInside(int x, int y) const;
    Cell& getCell(int x, int y);
    void print() const;
    bool isValidWhite(int x, int y) const;
    int getRows() const;
    int getCols() const;
    bool hasPrivilegedCells() const;
    bool hasOnlyWhiteCells() const;
    bool hasOnlyBlackCells() const;
};
