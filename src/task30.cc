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
#include "utils/ui.h"

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    ui::print_centered(L"Welcome to Masyu Puzzle Solver!");
    ui::sleep_for_seconds(2);

/* ---------------------------------------------------------------------[<]- 
    Field 1:
    10x10 field with no initial cells set.
 ---------------------------------------------------------------------[>]-*/
    ui::print_centered(L"Field 1: Empty field");
    ui::sleep_for_seconds(2);

    Field field_1(10, 10);

    ui::print_field_with_rules([&]() { field_1.print_field(); });

    /*
    Solver solver_1(field);
    if (solver_1.solve()) {
        ui::print_centered(L"Solution for Field 1 is found:");
        ui::print_field_with_rules([&]() { field_1.print_field(); });
    } else {
        ui::print_centered(L"No solution found for Field 1");
    }
    */
   ui::sleep_for_seconds(3);


/* ---------------------------------------------------------------------[<]-
    Field 2 (Task from example):
    10x10 field with some initial cells set.
    The task is to find a solution for this field.
    7 black dots and 13 white dots are set.
 ---------------------------------------------------------------------[>]-*/
    ui::print_centered(L"Field 2 (Task from example)");
    ui::sleep_for_seconds(2);

    Field field_2(10, 10);


    field_2.set_cell(Cell(8, 1, CellType::BLACK));
    field_2.set_cell(Cell(7, 2, CellType::BLACK));
    field_2.set_cell(Cell(6, 3, CellType::BLACK));
    field_2.set_cell(Cell(2, 4, CellType::BLACK));
    field_2.set_cell(Cell(1, 5, CellType::BLACK));
    field_2.set_cell(Cell(2, 7, CellType::BLACK));
    field_2.set_cell(Cell(8, 7, CellType::BLACK));

    field_2.set_cell(Cell(1, 0, CellType::WHITE));
    field_2.set_cell(Cell(5, 1, CellType::WHITE));
    field_2.set_cell(Cell(1, 2, CellType::WHITE));
    field_2.set_cell(Cell(4, 2, CellType::WHITE));
    field_2.set_cell(Cell(7, 3, CellType::WHITE));
    field_2.set_cell(Cell(8, 4, CellType::WHITE));
    field_2.set_cell(Cell(7, 5, CellType::WHITE));
    field_2.set_cell(Cell(2, 6, CellType::WHITE));
    field_2.set_cell(Cell(3, 6, CellType::WHITE));
    field_2.set_cell(Cell(5, 7, CellType::WHITE));
    field_2.set_cell(Cell(1, 8, CellType::WHITE));
    field_2.set_cell(Cell(4, 8, CellType::WHITE));
    field_2.set_cell(Cell(8, 9, CellType::WHITE));

    ui::print_field_with_rules([&]() { field_2.print_field(); });

    /*
    Solver solver_2(field);
    if (solver_2.solve()) {
        ui::print_centered(L"Solution for Field 2 is found:");
        ui::print_field_with_rules([&]() { field_2.print_field(); });
    } else {
        ui::print_centered(L"No solution found for Field 2");
    }
    */

    ui::sleep_for_seconds(3);
/* ---------------------------------------------------------------------[<]-
    Field 3 (Task 1):    
    11x11 field with some initial cells set.
    The task is to find a solution for this field.
    18 black dots and 10 white dots are set.
---------------------------------------------------------------------[>]-*/
    ui::print_centered(L"Field 3: Task 1");
    ui::sleep_for_seconds(2);

    Field field_3(11, 11);

    field_3.set_cell(Cell(4, 0, CellType::BLACK));
    field_3.set_cell(Cell(0, 2, CellType::BLACK));
    field_3.set_cell(Cell(2, 2, CellType::BLACK));
    field_3.set_cell(Cell(8, 2, CellType::BLACK));
    field_3.set_cell(Cell(10, 2, CellType::BLACK));
    field_3.set_cell(Cell(4, 4, CellType::BLACK));
    field_3.set_cell(Cell(6, 4, CellType::BLACK));
    field_3.set_cell(Cell(8, 4, CellType::BLACK));
    field_3.set_cell(Cell(0, 6, CellType::BLACK));
    field_3.set_cell(Cell(4, 6, CellType::BLACK));
    field_3.set_cell(Cell(8, 6, CellType::BLACK));
    field_3.set_cell(Cell(10, 6, CellType::BLACK));
    field_3.set_cell(Cell(0, 8, CellType::BLACK));
    field_3.set_cell(Cell(2, 8, CellType::BLACK));
    field_3.set_cell(Cell(6, 8, CellType::BLACK));
    field_3.set_cell(Cell(8, 8, CellType::BLACK));
    field_3.set_cell(Cell(4, 10, CellType::BLACK));
    field_3.set_cell(Cell(6, 10, CellType::BLACK));
    
    field_3.set_cell(Cell(6, 0, CellType::WHITE));
    field_3.set_cell(Cell(4, 2, CellType::WHITE));
    field_3.set_cell(Cell(6, 2, CellType::WHITE));
    field_3.set_cell(Cell(0, 4, CellType::WHITE));
    field_3.set_cell(Cell(2, 4, CellType::WHITE));
    field_3.set_cell(Cell(10, 4, CellType::WHITE));
    field_3.set_cell(Cell(2, 6, CellType::WHITE));
    field_3.set_cell(Cell(6, 6, CellType::WHITE));
    field_3.set_cell(Cell(4, 8, CellType::WHITE));
    field_3.set_cell(Cell(10, 8, CellType::WHITE));

    ui::print_field_with_rules([&]() { field_3.print_field(); });

    /*
    Solver solver_3(field);
    if (solver_3.solve()) {
        ui::print_centered(L"Solution for Field 3 is found:");
        ui::print_field_with_rules([&]() { field_3.print_field(); });
    } else {
        ui::print_centered(L"No solution found for Field 3");
    }
    */

    ui::sleep_for_seconds(3);

/* ---------------------------------------------------------------------[<]-
    Field 4 (Task 2):
    10x10 field with some initial cells set.
    The task is to find a solution for this field.
    9 black dots and 24 white dots are set.
---------------------------------------------------------------------[>]-*/
    ui::print_centered(L"Field 4: Task 2");
    ui::sleep_for_seconds(2);

    Field field_4(10, 10);

    field_4.set_cell(Cell(4, 2, CellType::BLACK));
    field_4.set_cell(Cell(5, 3, CellType::BLACK));
    field_4.set_cell(Cell(3, 4, CellType::BLACK));
    field_4.set_cell(Cell(2, 5, CellType::BLACK));
    field_4.set_cell(Cell(7, 5, CellType::BLACK));
    field_4.set_cell(Cell(3, 6, CellType::BLACK));
    field_4.set_cell(Cell(5, 6, CellType::BLACK));
    field_4.set_cell(Cell(6, 7, CellType::BLACK));
    field_4.set_cell(Cell(3, 9, CellType::BLACK));

    field_4.set_cell(Cell(2, 0, CellType::WHITE));
    field_4.set_cell(Cell(6, 0, CellType::WHITE));
    field_4.set_cell(Cell(8, 1, CellType::WHITE));
    field_4.set_cell(Cell(2, 2, CellType::WHITE));
    field_4.set_cell(Cell(3, 2, CellType::WHITE));
    field_4.set_cell(Cell(8, 2, CellType::WHITE));
    field_4.set_cell(Cell(4, 3, CellType::WHITE));
    field_4.set_cell(Cell(6, 3, CellType::WHITE));
    field_4.set_cell(Cell(7, 3, CellType::WHITE));
    field_4.set_cell(Cell(0, 4, CellType::WHITE));
    field_4.set_cell(Cell(2, 4, CellType::WHITE));
    field_4.set_cell(Cell(4, 4, CellType::WHITE));
    field_4.set_cell(Cell(5, 4, CellType::WHITE));
    field_4.set_cell(Cell(7, 4, CellType::WHITE));
    field_4.set_cell(Cell(5, 5, CellType::WHITE));

    field_4.set_cell(Cell(9, 5, CellType::WHITE));
    field_4.set_cell(Cell(2, 6, CellType::WHITE));
    field_4.set_cell(Cell(4, 6, CellType::WHITE));
    field_4.set_cell(Cell(7, 6, CellType::WHITE));
    field_4.set_cell(Cell(1, 7, CellType::WHITE));
    field_4.set_cell(Cell(5, 7, CellType::WHITE));
    field_4.set_cell(Cell(7, 7, CellType::WHITE));
    field_4.set_cell(Cell(1, 8, CellType::WHITE));
    field_4.set_cell(Cell(8, 9, CellType::WHITE));

    ui::print_field_with_rules([&]() { field_4.print_field(); });

    /*
    Solver solver_4(field_4);
    if (solver_4.solve()) {
        ui::print_centered(L"Solution for Field 4 is found:");
        ui::print_field_with_rules([&]() { field_4.print_field(); });
    } else {
        ui::print_centered(L"No solution found for Field 4");
    }
    */

    ui::sleep_for_seconds(3);

/* ---------------------------------------------------------------------[<]-
    Field 5 (Task 3):
    12x9 field with some initial cells set.
    The task is to find a solution for this field.
    8 black dots and 20 white dots are set.
---------------------------------------------------------------------[>]-*/
    ui::print_centered(L"Field 5: Task 3");
    ui::sleep_for_seconds(2);    

    Field field_5(12, 9);

    field_5.set_cell(Cell(1, 3, CellType::BLACK));
    field_5.set_cell(Cell(7, 3, CellType::BLACK));
    field_5.set_cell(Cell(10, 3, CellType::BLACK));
    field_5.set_cell(Cell(10, 4, CellType::BLACK));
    field_5.set_cell(Cell(1, 6, CellType::BLACK));
    field_5.set_cell(Cell(4, 6, CellType::BLACK));
    field_5.set_cell(Cell(7, 6, CellType::BLACK));
    field_5.set_cell(Cell(10, 6, CellType::BLACK));

    field_5.set_cell(Cell(5, 0, CellType::WHITE));
    field_5.set_cell(Cell(2, 1, CellType::WHITE));
    field_5.set_cell(Cell(3, 1, CellType::WHITE));
    field_5.set_cell(Cell(8, 1, CellType::WHITE));
    field_5.set_cell(Cell(9, 1, CellType::WHITE));
    field_5.set_cell(Cell(1, 2, CellType::WHITE));
    field_5.set_cell(Cell(4, 2, CellType::WHITE));
    field_5.set_cell(Cell(7, 2, CellType::WHITE));
    field_5.set_cell(Cell(10, 2, CellType::WHITE));
    field_5.set_cell(Cell(1, 4, CellType::WHITE));
    field_5.set_cell(Cell(1, 5, CellType::WHITE));
    field_5.set_cell(Cell(3, 5, CellType::WHITE));
    field_5.set_cell(Cell(4, 5, CellType::WHITE));
    field_5.set_cell(Cell(7, 5, CellType::WHITE));
    field_5.set_cell(Cell(10, 5, CellType::WHITE));
    field_5.set_cell(Cell(2, 7, CellType::WHITE));
    field_5.set_cell(Cell(3, 7, CellType::WHITE));
    field_5.set_cell(Cell(8, 7, CellType::WHITE));
    field_5.set_cell(Cell(9, 7, CellType::WHITE));
    field_5.set_cell(Cell(6, 8, CellType::WHITE));

    ui::print_field_with_rules([&]() { field_5.print_field(); });

    /*
    Solver solver_5(field_5);
    if (solver_5.solve()) {
        ui::print_centered(L"Solution for Field 5 is found:");
        ui::print_field_with_rules([&]() { field_5.print_field(); });
    } else {
        ui::print_centered(L"No solution found for Field 5");
    }
    */

    ui::sleep_for_seconds(3);

/* ---------------------------------------------------------------------[<]-
    Field 6:
    13x13 field with some initial cells set.
    The task is to find a solution for this field.
    15 black dots and 27 white dots are set.
---------------------------------------------------------------------[>]-*/
    ui::print_centered(L"Field 6: Task 4");
    ui::sleep_for_seconds(2);

    Field field_6(13, 13);

    field_6.set_cell(Cell(0, 0, CellType::BLACK));
    field_6.set_cell(Cell(3, 0, CellType::BLACK));
    field_6.set_cell(Cell(5, 2, CellType::BLACK));
    field_6.set_cell(Cell(9, 3, CellType::BLACK));
    field_6.set_cell(Cell(10, 4, CellType::BLACK));
    field_6.set_cell(Cell(11, 5, CellType::BLACK));
    field_6.set_cell(Cell(6, 7, CellType::BLACK));
    field_6.set_cell(Cell(8, 7, CellType::BLACK));
    field_6.set_cell(Cell(7, 8, CellType::BLACK));
    field_6.set_cell(Cell(3, 8, CellType::BLACK));
    field_6.set_cell(Cell(1, 8, CellType::BLACK));
    field_6.set_cell(Cell(6, 9, CellType::BLACK));
    field_6.set_cell(Cell(8, 9, CellType::BLACK));
    field_6.set_cell(Cell(1, 10, CellType::BLACK));
    field_6.set_cell(Cell(3, 10, CellType::BLACK));

    field_6.set_cell(Cell(8, 0, CellType::WHITE));
    field_6.set_cell(Cell(9, 0, CellType::WHITE));
    field_6.set_cell(Cell(12, 1, CellType::WHITE));
    field_6.set_cell(Cell(7, 2, CellType::WHITE));
    field_6.set_cell(Cell(8, 2, CellType::WHITE));
    field_6.set_cell(Cell(11, 2, CellType::WHITE));
    field_6.set_cell(Cell(2, 3, CellType::WHITE));
    field_6.set_cell(Cell(4, 3, CellType::WHITE));
    field_6.set_cell(Cell(5, 4, CellType::WHITE));
    field_6.set_cell(Cell(0, 5, CellType::WHITE));
    field_6.set_cell(Cell(1, 5, CellType::WHITE));
    field_6.set_cell(Cell(2, 5, CellType::WHITE));
    field_6.set_cell(Cell(5, 5, CellType::WHITE));
    field_6.set_cell(Cell(4, 5, CellType::WHITE));
    field_6.set_cell(Cell(8, 5, CellType::WHITE));
    field_6.set_cell(Cell(9, 6, CellType::WHITE));
    field_6.set_cell(Cell(12, 7, CellType::WHITE));
    field_6.set_cell(Cell(11, 9, CellType::WHITE));
    field_6.set_cell(Cell(9, 9, CellType::WHITE));
    field_6.set_cell(Cell(9, 10, CellType::WHITE));
    field_6.set_cell(Cell(11, 10, CellType::WHITE));
    field_6.set_cell(Cell(11, 11, CellType::WHITE));
    field_6.set_cell(Cell(0, 11, CellType::WHITE));
    field_6.set_cell(Cell(1, 11, CellType::WHITE));
    field_6.set_cell(Cell(5, 11, CellType::WHITE));
    field_6.set_cell(Cell(9, 11, CellType::WHITE));
    field_6.set_cell(Cell(7, 12, CellType::WHITE));

    ui::print_field_with_rules([&]() { field_6.print_field(); });

    /*
    Solver solver_6(field_6);
    if (solver_6.solve()) {
        ui::print_centered(L"Solution for Field 6 is found:");
        ui::print_field_with_rules([&]() { field_6.print_field(); });
    } else {
        ui::print_centered(L"No solution found for Field 6");
    }
    */

    ui::sleep_for_seconds(3);

/* ---------------------------------------------------------------------[<]-
    Field 7:
    17x17 field with some initial cells set.
    The task is to find a solution for this field.
    36 black dots and 36 white dots are set.
---------------------------------------------------------------------[>]-*/
    ui::print_centered(L"Field 7: Task 5");
    ui::sleep_for_seconds(2);

    Field field_7(17, 17);

    field_7.set_cell(Cell(1, 0, CellType::BLACK));
    field_7.set_cell(Cell(7, 0, CellType::BLACK));
    field_7.set_cell(Cell(13, 0, CellType::BLACK));
    field_7.set_cell(Cell(14, 0, CellType::BLACK));
    field_7.set_cell(Cell(4, 1, CellType::BLACK));
    field_7.set_cell(Cell(6, 1, CellType::BLACK));
    field_7.set_cell(Cell(10, 1, CellType::BLACK));
    field_7.set_cell(Cell(7, 2, CellType::BLACK));
    field_7.set_cell(Cell(11, 2, CellType::BLACK));
    field_7.set_cell(Cell(13, 2, CellType::BLACK));
    field_7.set_cell(Cell(2, 4, CellType::BLACK));
    field_7.set_cell(Cell(0, 5, CellType::BLACK));
    field_7.set_cell(Cell(3, 5, CellType::BLACK));
    field_7.set_cell(Cell(9, 5, CellType::BLACK));
    field_7.set_cell(Cell(10, 6, CellType::BLACK));
    field_7.set_cell(Cell(12, 6, CellType::BLACK));
    field_7.set_cell(Cell(16, 6, CellType::BLACK));
    field_7.set_cell(Cell(3, 7, CellType::BLACK));
    field_7.set_cell(Cell(6, 7, CellType::BLACK));
    field_7.set_cell(Cell(7, 7, CellType::BLACK));
    field_7.set_cell(Cell(9, 7, CellType::BLACK));
    field_7.set_cell(Cell(5, 8, CellType::BLACK));
    field_7.set_cell(Cell(14, 8, CellType::BLACK));
    field_7.set_cell(Cell(15, 9, CellType::BLACK));
    field_7.set_cell(Cell(1, 11, CellType::BLACK));
    field_7.set_cell(Cell(3, 11, CellType::BLACK));
    field_7.set_cell(Cell(10, 11, CellType::BLACK));
    field_7.set_cell(Cell(12, 11, CellType::BLACK));
    field_7.set_cell(Cell(4, 12, CellType::BLACK));
    field_7.set_cell(Cell(6, 13, CellType::BLACK));
    field_7.set_cell(Cell(8, 13, CellType::BLACK));
    field_7.set_cell(Cell(16, 13, CellType::BLACK));
    field_7.set_cell(Cell(0, 14, CellType::BLACK));
    field_7.set_cell(Cell(2, 14, CellType::BLACK));
    field_7.set_cell(Cell(14, 14, CellType::BLACK));
    field_7.set_cell(Cell(7, 16, CellType::BLACK));

    field_7.set_cell(Cell(9, 0, CellType::WHITE));
    field_7.set_cell(Cell(2, 2, CellType::WHITE));
    field_7.set_cell(Cell(14, 2, CellType::WHITE));
    field_7.set_cell(Cell(16, 2, CellType::WHITE));
    field_7.set_cell(Cell(0, 3, CellType::WHITE));
    field_7.set_cell(Cell(8, 3, CellType::WHITE));
    field_7.set_cell(Cell(10, 3, CellType::WHITE));
    field_7.set_cell(Cell(11, 4, CellType::WHITE));
    field_7.set_cell(Cell(4, 5, CellType::WHITE));
    field_7.set_cell(Cell(6, 5, CellType::WHITE));
    field_7.set_cell(Cell(13, 5, CellType::WHITE));
    field_7.set_cell(Cell(15, 5, CellType::WHITE));
    field_7.set_cell(Cell(1, 7, CellType::WHITE));
    field_7.set_cell(Cell(2, 8, CellType::WHITE));
    field_7.set_cell(Cell(11, 8, CellType::WHITE));
    field_7.set_cell(Cell(7, 9, CellType::WHITE));
    field_7.set_cell(Cell(9, 9, CellType::WHITE));
    field_7.set_cell(Cell(10, 9, CellType::WHITE));
    field_7.set_cell(Cell(13, 9, CellType::WHITE));
    field_7.set_cell(Cell(0, 10, CellType::WHITE));
    field_7.set_cell(Cell(4, 10, CellType::WHITE));
    field_7.set_cell(Cell(6, 10, CellType::WHITE));
    field_7.set_cell(Cell(7, 11, CellType::WHITE));
    field_7.set_cell(Cell(13, 11, CellType::WHITE));
    field_7.set_cell(Cell(16, 11, CellType::WHITE));
    field_7.set_cell(Cell(14, 12, CellType::WHITE));
    field_7.set_cell(Cell(3, 14, CellType::WHITE));
    field_7.set_cell(Cell(5, 14, CellType::WHITE));
    field_7.set_cell(Cell(9, 14, CellType::WHITE));
    field_7.set_cell(Cell(6, 15, CellType::WHITE));
    field_7.set_cell(Cell(10, 15, CellType::WHITE));
    field_7.set_cell(Cell(12, 15, CellType::WHITE));
    field_7.set_cell(Cell(2, 16, CellType::WHITE));
    field_7.set_cell(Cell(3, 16, CellType::WHITE));
    field_7.set_cell(Cell(9, 16, CellType::WHITE));
    field_7.set_cell(Cell(15, 16, CellType::WHITE));

    ui::print_field_with_rules([&]() { field_7.print_field(); });

    /*
    Solver solver_7(field_7);
    if (solver_7.solve()) {
        ui::print_centered(L"Solution for Field 7 is found:");
        ui::print_field_with_rules([&]() { field_7.print_field(); });
    } else {
        ui::print_centered(L"No solution found for Field 7");
    }
    */

    ui::sleep_for_seconds(3);
    ui::print_centered(L"End of Masyu Puzzle Solver");
    ui::print_centered(L"Exiting...");
    ui::sleep_for_seconds(2);

    return 0;
}
