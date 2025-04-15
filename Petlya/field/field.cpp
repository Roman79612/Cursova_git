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
            if (type == CellType::WhiteCircle || type == CellType::BlackCircle) {
                return true;
            }
        }
    }
    return false;
}

bool Field::hasOnlyWhiteCells() const {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (grid[y][x].type != CellType::WhiteCircle) {
                return false;
            }
        }
    }
    return true;
}

bool Field::hasOnlyBlackCells() const {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (grid[y][x].type != CellType::BlackCircle) {
                return false;
            }
        }
    }
    return true;
}

bool Field::isVisited(int x, int y) const {
    return isInside(x, y) && grid[y][x].visited;
}

void Field::markVisited(int x, int y) {
    if (isInside(x, y)) grid[y][x].visited = true;
}

void Field::unmarkVisited(int x, int y) {
    if (isInside(x, y)) grid[y][x].visited = false;
}

bool Field::isLinePassed(int x, int y) const {
    return isInside(x, y) && grid[y][x].linePassed;
}

void Field::markLinePassed(int x, int y) {
    if (isInside(x, y)) grid[y][x].linePassed = true;
}

void Field::unmarkLinePassed(int x, int y) {
    if (isInside(x, y)) grid[y][x].linePassed = false;
}

bool Field::isPrivilegedCell(int x, int y) const {
    if (!isInside(x, y)) return false;
    CellType t = grid[y][x].type;
    return t == CellType::WhiteCircle || t == CellType::BlackCircle;
}

vector<Position> Field::getAllPrivilegedCells() const {
    vector<Position> result;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (isPrivilegedCell(x, y)) result.emplace_back(x, y);
        }
    }
    return result;
}

bool Field::isIsolated(int x, int y) const {
    for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}) {
        int dx = 0, dy = 0;
        switch (dir) {
            case Direction::UP:    dy = -1; break;
            case Direction::DOWN:  dy =  1; break;
            case Direction::LEFT:  dx = -1; break;
            case Direction::RIGHT: dx =  1; break;
        }
        if (isInside(x + dx, y + dy)) return false;
    }
    return true;
}

bool Field::isDeadEnd(int x, int y, Direction fromDir) const {
    int count = 0;
    for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}) {
        if (dir == fromDir) continue; // Не враховуємо вхід
        int dx = 0, dy = 0;
        switch (dir) {
            case Direction::UP:    dy = -1; break;
            case Direction::DOWN:  dy =  1; break;
            case Direction::LEFT:  dx = -1; break;
            case Direction::RIGHT: dx =  1; break;
        }
        if (isInside(x + dx, y + dy))
            count++;
    }
    return count == 0;
}

bool Field::canEnterWhite(int x, int y, Direction dir) const {
    if (!isInside(x, y) || grid[y][x].type != CellType::WhiteCircle) return false;
    // Вхід можливий у білому, якщо рух прямо
    return true; // Ми обмеження реалізуємо в логіці лінії
}

bool Field::canExitWhite(int x, int y, Direction dir) const {
    return canEnterWhite(x, y, dir); // Рух прямо
}

bool Field::canTurnBlack(int x, int y, Direction inDir, Direction outDir) const {
    if (!isInside(x, y) || grid[y][x].type != CellType::BlackCircle) return false;
    if (inDir == outDir) return false; // Не можна прямо
    // Дозволяємо поворот на 90°, 270°, або 180° (якщо вперся в край)
    return true;
}

bool Field::isMoveValid(Position current, Direction dir) const {
    int dx = 0, dy = 0;
    switch (dir) {
        case Direction::UP:    dy = -1; break;
        case Direction::DOWN:  dy =  1; break;
        case Direction::LEFT:  dx = -1; break;
        case Direction::RIGHT: dx =  1; break;
    }
    int x = current.x + dx;
    int y = current.y + dy;
    return isInside(x, y);
}
