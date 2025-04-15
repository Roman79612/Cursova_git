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
    vector<Position> getAllPrivilegedCells() const;
    bool isPrivilegedCell(int x, int y) const;
    bool isVisited(int x, int y) const;
    bool isLinePassed(int x, int y) const;
    void markVisited(int x, int y);
    void markLinePassed(int x, int y);
    void unmarkVisited(int x, int y);
    void unmarkLinePassed(int x, int y);
    bool isIsolated(int x, int y) const;
    bool isDeadEnd(int x, int y, Direction fromDir) const;
    bool canEnterWhite(int x, int y, Direction dir) const;
    bool canExitWhite(int x, int y, Direction dir) const;
    bool canTurnBlack(int x, int y, Direction inDir, Direction outDir) const;
    bool isMoveValid(Position current, Direction dir) const;
};
