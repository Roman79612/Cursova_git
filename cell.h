#pragma once

enum class CellType {
    Empty,
    BlackCircle,
    WhiteCircle
};

struct Cell {
    int x, y;
    CellType type = CellType::Empty;
    bool visited = false;
    bool linePassed = false;

    Cell(int x = 0, int y = 0, CellType type = CellType::Empty);
};
