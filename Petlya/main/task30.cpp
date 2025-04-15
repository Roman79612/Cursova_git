#include <iostream>
#include "field.h"
#include "solver.h"
#include "utils.h"

using namespace std;

int main() {
    // Створюємо поле 10x10
    Field field(10, 10);
    // Стартова позиція і напрям
    Position startPos = {0, 0};
    Direction startDir = Direction::Down;
    // Ініціалізація Solver
    Solver solver(field, startPos, startDir);

    // Додаємо чорні клітинки
    field.placeCircle(8, 1, CellType::BlackCircle);
    field.placeCircle(7, 2, CellType::BlackCircle);
    field.placeCircle(6, 3, CellType::BlackCircle);
    field.placeCircle(2, 4, CellType::BlackCircle);
    field.placeCircle(1, 5, CellType::BlackCircle);
    field.placeCircle(2, 7, CellType::BlackCircle);
    field.placeCircle(8, 7, CellType::BlackCircle);

    // Додаємо білі клітинки
    field.placeCircle(1, 0, CellType::WhiteCircle);
    field.placeCircle(5, 1, CellType::WhiteCircle);
    field.placeCircle(1, 2, CellType::WhiteCircle);
    field.placeCircle(4, 2, CellType::WhiteCircle);
    field.placeCircle(7, 3, CellType::WhiteCircle);
    field.placeCircle(8, 4, CellType::WhiteCircle);
    field.placeCircle(7, 5, CellType::WhiteCircle);
    field.placeCircle(2, 6, CellType::WhiteCircle);
    field.placeCircle(3, 6, CellType::WhiteCircle);
    field.placeCircle(5, 7, CellType::WhiteCircle);
    field.placeCircle(1, 8, CellType::WhiteCircle);
    field.placeCircle(4, 8, CellType::WhiteCircle);
    field.placeCircle(8, 9, CellType::WhiteCircle);

    // Вивід початкової умови
    cout << "=== Initial field ===" << endl;
    field.print();


    // Запуск пошуку
    if (solver.solve()) {
        cout << "\n=== Field is solved ===" << endl;
        solver.printResult();
    } else {
        cout << "\nSolution no found!\n";
    }

    return 0;
}
