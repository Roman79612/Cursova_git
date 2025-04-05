#include "solver.h"
#include <iostream>
#include <sstream>
#include <functional>


Solver::Solver(Field& field, Position start, Direction dir) : field(field), line(start, dir) {}

bool Solver::solve() {
    int width = field.getCols();
    int height = field.getRows();

    if (!field.hasPrivilegedCells()) {
        return solveDefaultLoop(); // базова петля без білих/чорних
    }

    // Перевірка на поле з тільки білими клітинками
    if (field.hasOnlyWhiteCells()) {
        if (width * height <= 100) {
            return solveWhiteCellsRecursive(); // для маленьких полів з білими клітинами
        } else {
            return solveWhiteCellsIterative(); // для великих полів з білими клітинами
        }
    }

    // Перевірка на поле з тільки чорними клітинками
    if (field.hasOnlyBlackCells()) {
        if (width * height <= 100) {
            return solveBlackCellsRecursive(); // для маленьких полів з чорними клітинами
        } else {
            return solveBlackCellsIterative(); // для великих полів з чорними клітинами
        }
    }

    // Якщо поле містить різні клітинки, вибираємо метод в залежності від розміру поля
    if (width * height <= 100) {
        return solveRecursive(); // для малих полів
    } else {
        return solveIterative(); // для більших
    }
}

bool Solver::solveDefaultLoop() {
    cout << "\nRunning default loop (no special cells)...\n";

    // Початкові клітинки не відвідані
    for (int y = 0; y < field.getRows(); ++y) {
        for (int x = 0; x < field.getCols(); ++x) {
            field.getCell(x, y).linePassed = false; // очищаємо статус лінії
        }
    }

    // Рух по краях поля
    function<bool(Position, Direction)> moveEdge = [&](Position current, Direction dir) {
        // Якщо поточна позиція на краю поля, рухаємо лінію по периметру
        if (current.x == 0 || current.x == field.getCols() - 1 || current.y == 0 || current.y == field.getRows() - 1) {
            // Переміщаємо лінію
            line.setDirection(dir);
            if (line.move(current)) {
                // Відзначаємо клітинку як пройдену
                field.getCell(current.x, current.y).linePassed = true;
                return true;
            }
        }
        return false;
    };

    // Рухаємо лінію по краях поля (зліва направо, зверху вниз і т.д.)
    for (int y = 0; y < field.getRows(); ++y) {
        for (int x = 0; x < field.getCols(); ++x) {
            Position current = {x, y};
            moveEdge(current, Direction::Right);
        }
    }

    // Повертаємо успіх, якщо лінія змогла пройти по краях
    return true;
}


bool Solver::solveRecursive() {
    cout << "\nRunning recursive (DFS-based) solver...\n";
    return true; // тимчасова заглушка
}

bool Solver::solveIterative() {
    cout << "\nRunning iterative (heuristic) solver...\n";
    return true; // тимчасова заглушка
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
    cout << "\n=== Result ===\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << display[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool Solver::solveWhiteCellsRecursive() {
    cout << "\nSolving for white cells (recursive)...\n";
    // Логіка для рекурсивного вирішення головоломки з тільки білими клітинками
    return true;
}

bool Solver::solveWhiteCellsIterative() {
    cout << "\nSolving for white cells (iterative)...\n";
    // Логіка для ітеративного вирішення головоломки з тільки білими клітинками
    return true;
}

bool Solver::solveBlackCellsRecursive() {
    cout << "\nSolving for black cells (recursive)...\n";
    // Логіка для рекурсивного вирішення головоломки з тільки чорними клітинками
    return true;
}

bool Solver::solveBlackCellsIterative() {
    cout << "\nSolving for black cells (iterative)...\n";
    // Логіка для ітеративного вирішення головоломки з тільки чорними клітинками
    return true;
}
