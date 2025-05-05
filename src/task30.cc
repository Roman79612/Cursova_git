/* ----------------------------------------------------------------<Header>-
 Name: task30.cc
 Title: Main program for Masyu puzzle solver
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-03
 Revised: 2025-05-05
 Description: Main program to test the Masyu puzzle solver functionality.
 ------------------------------------------------------------------</Header>-*/

#include <iostream>
#include <locale.h>
#include "core_headers/field.h"
#include "core_headers/cell.h"
#include "core_headers/direction.h"
#include "logic_headers/solver.h"

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    std::wcout << L"┌───┬───┬───┐" << std::endl;
    std::wcout << L"● o o ●" << std::endl;
    std::wcout << "\n\n======================" << std::endl;
    std::wcout << "Masyu Puzzle Solver" << std::endl;
    std::wcout << "======================\n\n";

    Field field(10, 10);

    field.set_cell(Cell(8, 1, CellType::BLACK));
    field.set_cell(Cell(7, 2, CellType::BLACK));
    field.set_cell(Cell(6, 3, CellType::BLACK));
    field.set_cell(Cell(2, 4, CellType::BLACK));
    field.set_cell(Cell(1, 5, CellType::BLACK));
    field.set_cell(Cell(2, 7, CellType::BLACK));
    field.set_cell(Cell(8, 7, CellType::BLACK));

    field.set_cell(Cell(1, 0, CellType::WHITE));
    field.set_cell(Cell(5, 1, CellType::WHITE));
    field.set_cell(Cell(1, 2, CellType::WHITE));
    field.set_cell(Cell(4, 2, CellType::WHITE));
    field.set_cell(Cell(7, 3, CellType::WHITE));
    field.set_cell(Cell(8, 4, CellType::WHITE));
    field.set_cell(Cell(7, 5, CellType::WHITE));
    field.set_cell(Cell(2, 6, CellType::WHITE));
    field.set_cell(Cell(3, 6, CellType::WHITE));
    field.set_cell(Cell(5, 7, CellType::WHITE));
    field.set_cell(Cell(1, 8, CellType::WHITE));
    field.set_cell(Cell(4, 8, CellType::WHITE));
    field.set_cell(Cell(8, 9, CellType::WHITE));

    std::cout << "Initial field state:\n";
    field.print_field();

    /*Solver solver(field);
    if (solver.solve()) {
        std::cout << "Solution found:\n";
        field.print_field();
    } else {
        std::cout << "No solution found.\n";
    }*/

    return 0;
}
