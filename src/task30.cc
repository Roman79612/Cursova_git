/* ----------------------------------------------------------------<Header>-
 Name: task30.cc
 Title: Main program for Masyu puzzle solver
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-03
 Revised: 2025-05-03
 Description: Main program to test the Masyu puzzle solver functionality.
 ------------------------------------------------------------------</Header>-*/

#include <iostream>
#include "core_headers/field.h"
#include "core_headers/cell.h"
#include "core_headers/direction.h"
#include "logic_headers/solver.h"
#include "utils/config.h"

int main() {
    // Створення поля розміром 10x10
    Field field(10, 10);

    // Додаємо чорні клітинки
    field.set_cell(8, 1, Cell(CellType::BLACK_DOT));
    field.set_cell(7, 2, Cell(CellType::BLACK_DOT));
    field.set_cell(6, 3, Cell(CellType::BLACK_DOT));
    field.set_cell(2, 4, Cell(CellType::BLACK_DOT));
    field.set_cell(1, 5, Cell(CellType::BLACK_DOT));
    field.set_cell(2, 7, Cell(CellType::BLACK_DOT));
    field.set_cell(8, 7, Cell(CellType::BLACK_DOT));

    // Додаємо білі клітинки
    field.set_cell(1, 0, Cell(CellType::WHITE_DOT));
    field.set_cell(5, 1, Cell(CellType::WHITE_DOT));
    field.set_cell(1, 2, Cell(CellType::WHITE_DOT));
    field.set_cell(4, 2, Cell(CellType::WHITE_DOT));
    field.set_cell(7, 3, Cell(CellType::WHITE_DOT));
    field.set_cell(8, 4, Cell(CellType::WHITE_DOT));
    field.set_cell(7, 5, Cell(CellType::WHITE_DOT));
    field.set_cell(2, 6, Cell(CellType::WHITE_DOT));
    field.set_cell(3, 6, Cell(CellType::WHITE_DOT));
    field.set_cell(5, 7, Cell(CellType::WHITE_DOT));
    field.set_cell(1, 8, Cell(CellType::WHITE_DOT));
    field.set_cell(4, 8, Cell(CellType::WHITE_DOT));
    field.set_cell(8, 9, Cell(CellType::WHITE_DOT));

    // Виведення початкового стану поля
    std::cout << "Initial field state:\n";
    field.print_initial_state();

    // Створення і виклик розв'язувача
    Solver solver(field);
    if (solver.solve()) {
        std::cout << "Solution found:\n";
        field.print_final_state();
    } else {
        std::cout << "No solution found.\n";
    }

    return 0;
}
