#include "solver.h"
#include <iostream>
#include <sstream>

Solver::Solver(Field& field, Position start, Direction dir) : field(field), line(start, dir) {}

    bool Solver::solve() {
    int width = field.getCols();
    int height = field.getRows();

    if (!field.hasPrivilegedCells()) {
        return solveDefaultLoop(); // базова петля без білих/чорних
    }

    if (width * height <= 100) {
        return solveRecursive(); // для малих полів
    } else {
        return solveIterative(); // для більших
    }
}

bool Solver::solveDefaultLoop() {
    cout << "Running default loop (no special cells)...\n";
    return true; // тимчасова заглушка
}

bool Solver::solveRecursive() {
    cout << "Running recursive (DFS-based) solver...\n";
    return false; // тимчасова заглушка
}

bool Solver::solveIterative() {
    cout << "Running iterative (heuristic) solver...\n";
    return false; // тимчасова заглушка
}

void Solver::printResult() const {
    int rows = field.getRows();
    int cols = field.getCols();

    // Створюємо копію поля для відображення результату
    vector<vector<char>> display(rows, vector<char>(cols, ' '));

    // Заповнюємо типи клітинок (білі/чорні)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Cell cell = field.getCell(i, j);
            switch (cell.type) {
                case CellType::BlackCircle: display[i][j] = 'B'; break;
                case CellType::WhiteCircle: display[i][j] = 'W'; break;
                case CellType::Empty: display[i][j] = '.'; break;
            }
        }
    }

    // Накладаємо шлях лінії зірочками
    for (const Position& pos : line.getPath()) {
        if (field.isInside(pos.x, pos.y)) {
            display[pos.x][pos.y] = '*';
        }
    }
    // Виводимо результат
    cout << "=== Result ===\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << display[i][j] << ' ';
        }
        cout << '\n';
    }
}

