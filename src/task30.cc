/* ----------------------------------------------------------------<Header>-
 Name: Test30.cc
 Title: Main program for Masyu puzzle solver
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-03
 Revised: 2025-05-06
 Description: Main program to test the Masyu puzzle solver functionality.
 ------------------------------------------------------------------</Header>-*/

#include <iostream>
#include <locale.h>
#include "core_headers/field.h"
#include "core_headers/cell.h"
#include "core_headers/direction.h"
#include "logic_headers/solver.h"
#include "utils/ui.h"

void create_field_from_user();
void print_all_fields();
void print_field_by_number();
void end_program();

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    ui::print_centered_title(L"Welcome to Masyu Puzzle Solver!");
    ui::sleep_for_seconds(2);

    while (true) {
        ui::print_menu();
        int choice = ui::get_user_choice(5);
        switch (choice) {
            case 1:
                print_all_fields();
                break;
            case 2:
                print_field_by_number();
                break;
            case 3:
                create_field_from_user();
                break;
            case 4:
                ui::show_rules();
                ui::sleep_for_seconds(5);
                break;
            case 5:
                end_program();
                break;
            default:
                std::wcout << "Invalid choice number of menu...";
                break;
        }        
        if (choice == 5) break;
    }

    return 0;
}

/* ----------------------------------------------------------------------[<]-
 Function:   create_field_from_user
 Synopsis:   User to create a field, add cells, and choose the type for each cell.
-------------------------------------------------------------------------[>]*/
void create_field_from_user() {
	Field user_field;
	int width = 5, height = 5;
	
	std::wcout << L"Enter the width and height of the field at least \"5 5\". ";
	std::pair<int, int> size = ui::get_user_coordinate(21, 21);
    if (size.first < 5 || size.second < 5) {
        std::wcout << "Your size was less than 5 5" << std::endl; 
    } else {
        width = size.first;
        height = size.second;
    }
	
	try {
		user_field.init(width, height);
	} catch (const std::invalid_argument& e) {
		std::wcerr << L"Error initializing the field: " << e.what() << std::endl;
		return;
	}

	int num_cells = 0;
	std::wcout << L"Enter the number of cells you want to set: ";
	num_cells = ui::get_user_choice((width * height) / 2);

	for (int i = 0; i < num_cells; ++i) {
		std::pair<int, int> coord = ui::get_user_coordinate(width, height);
		if (coord.first == -1 || coord.second == -1) {
			std::wcerr << L"Invalid coordinate input. Skipping cell.\n";
			continue;
		}

		std::wcout << L"Enter cell type for (" << coord.first << L", " << coord.second << L")\n";
		std::wcout << L"1. White\n2. Black\nYour choice: ";
		int cell_type = ui::get_user_choice(2);
		
        if (cell_type == 1) {
			user_field.set_cell(Cell(coord.first, coord.second, CellType::WHITE));
    	} else if (cell_type == 2) {
			user_field.set_cell(Cell(coord.first, coord.second, CellType::BLACK));
		} else {
			std::wcerr << L"Invalid choice. Please enter 1 for White or 2 for Black.\n";
		}
	}

	user_field.print_field();
    ui::sleep_for_seconds(2);

	try {
		if (user_field.is_initialized()) {
			Solver user_solver(user_field);
			if (user_solver.solve()) {
				ui::print_centered_title_half(L"Solution for your field is found:");
				user_field.print_field();
				ui::print_rules(user_field.get_height());
			} else {
				ui::print_centered_title(L"No solution found for your field");
			}
		}
	} catch (const std::exception& e) {
		std::wcerr << L"Error solving the field: " << e.what() << std::endl;
	}
    ui::sleep_for_seconds(2);
}

/* ----------------------------------------------------------------------[<]-
    Function: solve_field
    Synopsis: Solve field 1 and display solving.
-------------------------------------------------------------------------[>]*/
void solve_field(Field& field) {
    try {
        if (field.is_initialized()) {
            Solver solver(field);
            if (solver.solve()) {
                ui::print_centered_title_half(L"Solution for Field 1 is found:");
                field.print_field();
                ui::print_rules(field.get_height());
            } else {
                ui::print_centered_title(L"No solution found for Field 1");
            }
        }
    } catch (const std::exception& e) {
        std::wcerr << L"Error solving field 1: " << e.what() << std::endl;
    }
}

/* ----------------------------------------------------------------------[<]-
    Function: create_field_1
    Synopsis: Create field 1 from test 1.
-------------------------------------------------------------------------[>]*/
Field create_field_1() {
    Field field;

    try {
        field.init(11, 11);
    } catch (const std::invalid_argument& e) {
        std::wcerr << L"Error initialization field 1: " << e.what() << std::endl;
    }

    try {
        field.set_cell(Cell(4, 0, CellType::BLACK));
        field.set_cell(Cell(0, 2, CellType::BLACK));
        field.set_cell(Cell(2, 2, CellType::BLACK));
        field.set_cell(Cell(8, 2, CellType::BLACK));
        field.set_cell(Cell(10, 2, CellType::BLACK));
        field.set_cell(Cell(4, 4, CellType::BLACK));
        field.set_cell(Cell(6, 4, CellType::BLACK));
        field.set_cell(Cell(8, 4, CellType::BLACK));
        field.set_cell(Cell(0, 6, CellType::BLACK));
        field.set_cell(Cell(4, 6, CellType::BLACK));
        field.set_cell(Cell(8, 6, CellType::BLACK));
        field.set_cell(Cell(10, 6, CellType::BLACK));
        field.set_cell(Cell(0, 8, CellType::BLACK));
        field.set_cell(Cell(2, 8, CellType::BLACK));
        field.set_cell(Cell(6, 8, CellType::BLACK));
        field.set_cell(Cell(8, 8, CellType::BLACK));
        field.set_cell(Cell(4, 10, CellType::BLACK));
        field.set_cell(Cell(6, 10, CellType::BLACK));

        field.set_cell(Cell(6, 0, CellType::WHITE));
        field.set_cell(Cell(4, 2, CellType::WHITE));
        field.set_cell(Cell(6, 2, CellType::WHITE));
        field.set_cell(Cell(0, 4, CellType::WHITE));
        field.set_cell(Cell(2, 4, CellType::WHITE));
        field.set_cell(Cell(10, 4, CellType::WHITE));
        field.set_cell(Cell(2, 6, CellType::WHITE));
        field.set_cell(Cell(6, 6, CellType::WHITE));
        field.set_cell(Cell(4, 8, CellType::WHITE));
        field.set_cell(Cell(10, 8, CellType::WHITE));
    } catch (const std::invalid_argument& e) {
        std::wcerr << L"Error setting cell in field 1: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::wcerr << L"Error setting coordinates field 1: " << e.what() << std::endl;
    }

    return field;
}

/* ----------------------------------------------------------------------[<]-
    Function: print_field_1
    Synopsis: Print field 1.
-------------------------------------------------------------------------[>]*/
void print_field_1() {
    ui::print_centered_title_half(L"Field 1: Test 1");

    Field field = create_field_1();

    field.print_field();
    ui::print_rules(field.get_height());
    ui::sleep_for_seconds(2);

    solve_field(field);

    ui::sleep_for_seconds(4);
}

/* ----------------------------------------------------------------------[<]-
    Function: create_field_2
    Synopsis: Create field 2 from test 2.
-------------------------------------------------------------------------[>]*/
Field create_field_2() {
    Field field;

    try {
        field.init(10, 10);
    } catch (const std::invalid_argument& e) {
        std::wcerr << L"Error initialization field 2: " << e.what() << std::endl;
    }

    try {
        field.set_cell(Cell(4, 2, CellType::BLACK));
        field.set_cell(Cell(5, 3, CellType::BLACK));
        field.set_cell(Cell(3, 4, CellType::BLACK));
        field.set_cell(Cell(2, 5, CellType::BLACK));
        field.set_cell(Cell(7, 5, CellType::BLACK));
        field.set_cell(Cell(3, 6, CellType::BLACK));
        field.set_cell(Cell(5, 6, CellType::BLACK));
        field.set_cell(Cell(6, 7, CellType::BLACK));
        field.set_cell(Cell(3, 9, CellType::BLACK));

        field.set_cell(Cell(2, 0, CellType::WHITE));
        field.set_cell(Cell(6, 0, CellType::WHITE));
        field.set_cell(Cell(8, 1, CellType::WHITE));
        field.set_cell(Cell(2, 2, CellType::WHITE));
        field.set_cell(Cell(3, 2, CellType::WHITE));
        field.set_cell(Cell(8, 2, CellType::WHITE));
        field.set_cell(Cell(4, 3, CellType::WHITE));
        field.set_cell(Cell(6, 3, CellType::WHITE));
        field.set_cell(Cell(7, 3, CellType::WHITE));
        field.set_cell(Cell(0, 4, CellType::WHITE));
        field.set_cell(Cell(2, 4, CellType::WHITE));
        field.set_cell(Cell(4, 4, CellType::WHITE));
        field.set_cell(Cell(5, 4, CellType::WHITE));
        field.set_cell(Cell(7, 4, CellType::WHITE));
        field.set_cell(Cell(5, 5, CellType::WHITE));
        field.set_cell(Cell(9, 5, CellType::WHITE));
        field.set_cell(Cell(2, 6, CellType::WHITE));
        field.set_cell(Cell(4, 6, CellType::WHITE));
        field.set_cell(Cell(7, 6, CellType::WHITE));
        field.set_cell(Cell(1, 7, CellType::WHITE));
        field.set_cell(Cell(5, 7, CellType::WHITE));
        field.set_cell(Cell(7, 7, CellType::WHITE));
        field.set_cell(Cell(1, 8, CellType::WHITE));
        field.set_cell(Cell(8, 9, CellType::WHITE));
    } catch (const std::invalid_argument& e) {
        std::wcerr << L"Error setting cell in field 2: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::wcerr << L"Error setting coordinates field 2: " << e.what() << std::endl;
    }

    return field;
}

/* ----------------------------------------------------------------------[<]-
    Function: print_field_2
    Synopsis: Print field and solve field 2.
-------------------------------------------------------------------------[>]*/
void print_field_2() {
    ui::print_centered_title_half(L"Field 2: Test 2");

    Field field = create_field_2();

    field.print_field();
    ui::print_rules(field.get_height());
    ui::sleep_for_seconds(2);

    solve_field(field);

    ui::sleep_for_seconds(4);
}

/* ----------------------------------------------------------------------[<]-
    Function: create_field_3
    Synopsis: Create field 3 from test 3.
-------------------------------------------------------------------------[>]*/
Field create_field_3() {
    Field field;
    
    try {
        field.init(12, 9);
    } catch (const std::invalid_argument& e) {
        std::wcerr << L"Error initialization field 3: " << e.what() << std::endl;
    }

    try {
        field.set_cell(Cell(1, 3, CellType::BLACK));
        field.set_cell(Cell(7, 3, CellType::BLACK));
        field.set_cell(Cell(10, 3, CellType::BLACK));
        field.set_cell(Cell(10, 4, CellType::BLACK));
        field.set_cell(Cell(1, 6, CellType::BLACK));
        field.set_cell(Cell(4, 6, CellType::BLACK));
        field.set_cell(Cell(7, 6, CellType::BLACK));
        field.set_cell(Cell(10, 6, CellType::BLACK));

        field.set_cell(Cell(5, 0, CellType::WHITE));
        field.set_cell(Cell(2, 1, CellType::WHITE));
        field.set_cell(Cell(3, 1, CellType::WHITE));
        field.set_cell(Cell(8, 1, CellType::WHITE));
        field.set_cell(Cell(9, 1, CellType::WHITE));
        field.set_cell(Cell(1, 2, CellType::WHITE));
        field.set_cell(Cell(4, 2, CellType::WHITE));
        field.set_cell(Cell(7, 2, CellType::WHITE));
        field.set_cell(Cell(10, 2, CellType::WHITE));
        field.set_cell(Cell(1, 4, CellType::WHITE));
        field.set_cell(Cell(1, 5, CellType::WHITE));
        field.set_cell(Cell(3, 5, CellType::WHITE));
        field.set_cell(Cell(4, 5, CellType::WHITE));
        field.set_cell(Cell(7, 5, CellType::WHITE));
        field.set_cell(Cell(10, 5, CellType::WHITE));
        field.set_cell(Cell(2, 7, CellType::WHITE));
        field.set_cell(Cell(3, 7, CellType::WHITE));
        field.set_cell(Cell(8, 7, CellType::WHITE));
        field.set_cell(Cell(9, 7, CellType::WHITE));
        field.set_cell(Cell(6, 8, CellType::WHITE));
    } catch (const std::invalid_argument& e) {
        std::wcerr << L"Error setting cell in field 3: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::wcerr << L"Error setting coordinates field 3: " << e.what() << std::endl;
    }

    return field;
}

/* ----------------------------------------------------------------------[<]-
    Function: print_field_3
    Synopsis: Print field and solve field 3.
-------------------------------------------------------------------------[>]*/
void print_field_3() {
    ui::print_centered_title_half(L"Field 3: Test 3");

    Field field = create_field_3();

    field.print_field();
    ui::print_rules(field.get_height());
    ui::sleep_for_seconds(2);

    solve_field(field);

    ui::sleep_for_seconds(4);
}

/* ----------------------------------------------------------------------[<]-
    Function: create_field_4
    Synopsis: Create field 4 from test 4.
-------------------------------------------------------------------------[>]*/
Field create_field_4() {
    Field field;
    
    try {
        field.init(13, 13);
    } catch (const std::invalid_argument& e) {
        std::wcerr << L"Error initialization field 4: " << e.what() << std::endl;
    }

    try {
        field.set_cell(Cell(0, 0, CellType::BLACK));
        field.set_cell(Cell(3, 0, CellType::BLACK));
        field.set_cell(Cell(5, 2, CellType::BLACK));
        field.set_cell(Cell(9, 3, CellType::BLACK));
        field.set_cell(Cell(10, 4, CellType::BLACK));
        field.set_cell(Cell(11, 5, CellType::BLACK));
        field.set_cell(Cell(6, 7, CellType::BLACK));
        field.set_cell(Cell(8, 7, CellType::BLACK));
        field.set_cell(Cell(7, 8, CellType::BLACK));
        field.set_cell(Cell(3, 8, CellType::BLACK));
        field.set_cell(Cell(1, 8, CellType::BLACK));
        field.set_cell(Cell(6, 9, CellType::BLACK));
        field.set_cell(Cell(8, 9, CellType::BLACK));
        field.set_cell(Cell(1, 10, CellType::BLACK));
        field.set_cell(Cell(3, 10, CellType::BLACK));

        field.set_cell(Cell(8, 0, CellType::WHITE));
        field.set_cell(Cell(9, 0, CellType::WHITE));
        field.set_cell(Cell(12, 1, CellType::WHITE));
        field.set_cell(Cell(7, 2, CellType::WHITE));
        field.set_cell(Cell(8, 2, CellType::WHITE));
        field.set_cell(Cell(11, 2, CellType::WHITE));
        field.set_cell(Cell(2, 3, CellType::WHITE));
        field.set_cell(Cell(4, 3, CellType::WHITE));
        field.set_cell(Cell(5, 4, CellType::WHITE));
        field.set_cell(Cell(0, 5, CellType::WHITE));
        field.set_cell(Cell(1, 5, CellType::WHITE));
        field.set_cell(Cell(2, 5, CellType::WHITE));
        field.set_cell(Cell(5, 5, CellType::WHITE));
        field.set_cell(Cell(4, 5, CellType::WHITE));
        field.set_cell(Cell(8, 5, CellType::WHITE));
        field.set_cell(Cell(9, 6, CellType::WHITE));
        field.set_cell(Cell(12, 7, CellType::WHITE));
        field.set_cell(Cell(11, 9, CellType::WHITE));
        field.set_cell(Cell(9, 9, CellType::WHITE));
        field.set_cell(Cell(9, 10, CellType::WHITE));
        field.set_cell(Cell(11, 10, CellType::WHITE));
        field.set_cell(Cell(11, 11, CellType::WHITE));
        field.set_cell(Cell(0, 11, CellType::WHITE));
        field.set_cell(Cell(1, 11, CellType::WHITE));
        field.set_cell(Cell(5, 11, CellType::WHITE));
        field.set_cell(Cell(9, 11, CellType::WHITE));
        field.set_cell(Cell(7, 12, CellType::WHITE));
    } catch (const std::invalid_argument& e) {
        std::wcerr << L"Error setting cell in field 4: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::wcerr << L"Error setting coordinates field 4: " << e.what() << std::endl;
    }

    return field;
}

/* ----------------------------------------------------------------------[<]-
    Function: print_field_4
    Synopsis: Print field and solve field 4.
-------------------------------------------------------------------------[>]*/
void print_field_4() {
    ui::print_centered_title_half(L"Field 4: Test 4");

    Field field = create_field_4();

    field.print_field();
    ui::print_rules(field.get_height());
    ui::sleep_for_seconds(2);

    solve_field(field);

    ui::sleep_for_seconds(2);
}

/* ----------------------------------------------------------------------[<]-
    Function: create_field_5
    Synopsis: Create field 5 from test 5.
-------------------------------------------------------------------------[>]*/
Field create_field_5() {
    Field field;
    
    try {
        field.init(17, 17);
    } catch (const std::invalid_argument& e) {
        std::wcerr << L"Error initialization field 5: " << e.what() << std::endl;
    }

    try {
        field.set_cell(Cell(1, 0, CellType::BLACK));
        field.set_cell(Cell(7, 0, CellType::BLACK));
        field.set_cell(Cell(13, 0, CellType::BLACK));
        field.set_cell(Cell(14, 0, CellType::BLACK));
        field.set_cell(Cell(4, 1, CellType::BLACK));
        field.set_cell(Cell(6, 1, CellType::BLACK));
        field.set_cell(Cell(10, 1, CellType::BLACK));
        field.set_cell(Cell(7, 2, CellType::BLACK));
        field.set_cell(Cell(11, 2, CellType::BLACK));
        field.set_cell(Cell(13, 2, CellType::BLACK));
        field.set_cell(Cell(2, 4, CellType::BLACK));
        field.set_cell(Cell(0, 5, CellType::BLACK));
        field.set_cell(Cell(3, 5, CellType::BLACK));
        field.set_cell(Cell(9, 5, CellType::BLACK));
        field.set_cell(Cell(10, 6, CellType::BLACK));
        field.set_cell(Cell(12, 6, CellType::BLACK));
        field.set_cell(Cell(16, 6, CellType::BLACK));
        field.set_cell(Cell(3, 7, CellType::BLACK));
        field.set_cell(Cell(6, 7, CellType::BLACK));
        field.set_cell(Cell(7, 7, CellType::BLACK));
        field.set_cell(Cell(9, 7, CellType::BLACK));
        field.set_cell(Cell(5, 8, CellType::BLACK));
        field.set_cell(Cell(14, 8, CellType::BLACK));
        field.set_cell(Cell(15, 9, CellType::BLACK));
        field.set_cell(Cell(1, 11, CellType::BLACK));
        field.set_cell(Cell(3, 11, CellType::BLACK));
        field.set_cell(Cell(10, 11, CellType::BLACK));
        field.set_cell(Cell(12, 11, CellType::BLACK));
        field.set_cell(Cell(4, 12, CellType::BLACK));
        field.set_cell(Cell(6, 13, CellType::BLACK));
        field.set_cell(Cell(8, 13, CellType::BLACK));
        field.set_cell(Cell(16, 13, CellType::BLACK));
        field.set_cell(Cell(0, 14, CellType::BLACK));
        field.set_cell(Cell(2, 14, CellType::BLACK));
        field.set_cell(Cell(14, 14, CellType::BLACK));
        field.set_cell(Cell(7, 16, CellType::BLACK));

        field.set_cell(Cell(9, 0, CellType::WHITE));
        field.set_cell(Cell(2, 2, CellType::WHITE));
        field.set_cell(Cell(14, 2, CellType::WHITE));
        field.set_cell(Cell(16, 2, CellType::WHITE));
        field.set_cell(Cell(0, 3, CellType::WHITE));
        field.set_cell(Cell(8, 3, CellType::WHITE));
        field.set_cell(Cell(10, 3, CellType::WHITE));
        field.set_cell(Cell(11, 4, CellType::WHITE));
        field.set_cell(Cell(4, 5, CellType::WHITE));
        field.set_cell(Cell(6, 5, CellType::WHITE));
        field.set_cell(Cell(13, 5, CellType::WHITE));
        field.set_cell(Cell(15, 5, CellType::WHITE));
        field.set_cell(Cell(1, 7, CellType::WHITE));
        field.set_cell(Cell(2, 8, CellType::WHITE));
        field.set_cell(Cell(11, 8, CellType::WHITE));
        field.set_cell(Cell(7, 9, CellType::WHITE));
        field.set_cell(Cell(9, 9, CellType::WHITE));
        field.set_cell(Cell(10, 9, CellType::WHITE));
        field.set_cell(Cell(13, 9, CellType::WHITE));
        field.set_cell(Cell(0, 10, CellType::WHITE));
        field.set_cell(Cell(4, 10, CellType::WHITE));
        field.set_cell(Cell(6, 10, CellType::WHITE));
        field.set_cell(Cell(7, 11, CellType::WHITE));
        field.set_cell(Cell(13, 11, CellType::WHITE));
        field.set_cell(Cell(16, 11, CellType::WHITE));
        field.set_cell(Cell(14, 12, CellType::WHITE));
        field.set_cell(Cell(3, 14, CellType::WHITE));
        field.set_cell(Cell(5, 14, CellType::WHITE));
        field.set_cell(Cell(9, 14, CellType::WHITE));
        field.set_cell(Cell(6, 15, CellType::WHITE));
        field.set_cell(Cell(10, 15, CellType::WHITE));
        field.set_cell(Cell(12, 15, CellType::WHITE));
        field.set_cell(Cell(2, 16, CellType::WHITE));
        field.set_cell(Cell(3, 16, CellType::WHITE));
        field.set_cell(Cell(9, 16, CellType::WHITE));
        field.set_cell(Cell(15, 16, CellType::WHITE));
    } catch (const std::invalid_argument& e) {
        std::wcerr << L"Error setting cell in field 5: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::wcerr << L"Error setting coordinates field 5: " << e.what() << std::endl;
    }

    return field;
}

/* ----------------------------------------------------------------------[<]-
    Function: print_field_5
    Synopsis: Print field and solve field 5.
-------------------------------------------------------------------------[>]*/
void print_field_5() {
    ui::print_centered_title_half(L"Field 5: Test 5");

    Field field = create_field_5();

    field.print_field();
    ui::print_rules(field.get_height());
    ui::sleep_for_seconds(2);

    solve_field(field);

    ui::sleep_for_seconds(4);
}

/* ----------------------------------------------------------------------[<]-
    Function: print_all_fields
    Synopsis: Display all of fields.
-------------------------------------------------------------------------[>]*/
void print_all_fields() {
    print_field_1();
    print_field_2();
    print_field_3();
    print_field_4();
    print_field_5();
}

/* ----------------------------------------------------------------------[<]-
    Function: print_field_by_number
    Synopsis: Prints the field by number.
-------------------------------------------------------------------------[>]*/
void print_field_by_number() {
    int number = ui::get_user_choice(5);
    switch(number) {
        case 1:
            print_field_1();
            break;
        case 2:
            print_field_2();
            break;
        case 3:
            print_field_3();
            break;
        case 4:
            print_field_4();
            break;
        case 5:
            print_field_5();
            break;
        default:
            std::wcout << L"Invalid field number. Please choose from 1 to 5.\n";
            break;
    }
}

/* ---------------------------------------------------------------------[<]- 
    End of program:
    Print exit message and wait for a few seconds before exiting.   
---------------------------------------------------------------------[>]-*/
void end_program() {
    ui::print_centered_title(L"End of Masyu Puzzle Solver");
    ui::sleep_for_seconds(2);
    ui::print_centered_title(L"Exiting...");
    ui::sleep_for_seconds(1);
}
