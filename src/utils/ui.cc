/* ----------------------------------------------------------------<Header>-
 Name: ui.cc
 Title: Implementation of utility functions for console output
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-05
 Revised: 2025-05-05
 Description: This file contains the implementation of functions for manipulating the console output, such as moving the cursor, clearing the console,
 and formatted text.
 ------------------------------------------------------------------</Header>-*/

#include "../utils/ui.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace ui {
	/* ----------------------------------------------------------------------[<]-
	Function: print_rules
	Synopsis: Prints the rules of the game in a formatted box.
	---------------------------------------------------------------------[>]*/
	void print_rules() {
		const std::vector<std::wstring> rules_box = {
			L"\x1b[32m╔════════════════════════════════════════════╗",
			L"\x1b[32m║ \x1b[31m                  RULES:                   \x1b[32m║",
			L"\x1b[32m║ \x1b[0m● Black circle: must turn 90° or 270°,     \x1b[32m║",
			L"\x1b[32m║   \x1b[0mand go straight before and after.        \x1b[32m║",
			L"\x1b[32m║ \x1b[0m○ White circle: must go straight through,  \x1b[32m║",
			L"\x1b[32m║   \x1b[0mand turn either before or after.         \x1b[32m║",
			L"\x1b[32m╚════════════════════════════════════════════╝\x1b[0m"
		};

		int field_lines = 20;
		int right_indent = 100;

		std::wcout << L"\x1b[" << field_lines << L"A";

		for (const auto& line : rules_box) {
			std::wcout << L"\x1b[" << right_indent << L"C" << line << std::endl;
		}

		int lines_after = field_lines - 7;
		std::wcout << L"\x1b[" << lines_after << L"B";
	}

	/* ----------------------------------------------------------------------[<]-
	Function: print_centered
	Synopsis: Prints a centered text line with a separator above and below.
	---------------------------------------------------------------------[>]*/
	void print_centered(const std::wstring& text) {
		std::wcout << "\n" <<std::endl;
		print_separator();

		const int total_width = 80;
		int padding = (total_width - static_cast<int>(text.size())) / 2;
		if (padding < 0) padding = 0;

		std::wcout << L"\x1b[31m" << std::wstring(padding, L' ') << text << L"\x1b[0m" << std::endl;

		print_separator();
	}

	/* ----------------------------------------------------------------------[<]-
	Function: print_separator
	Synopsis: Prints a horizontal separator line.
	---------------------------------------------------------------------[>]*/
	void print_separator() {
		const int total_width = 80;
		std::wcout << L"\x1b[32m" << std::wstring(total_width, L'═') << L"\x1b[0m" << std::endl;
	}

	/* ----------------------------------------------------------------------[<]-
	Function: sleep_for_seconds
	Synopsis: Sleeps for the specified number of seconds.
	---------------------------------------------------------------------[>]*/
	void sleep_for_seconds(int seconds) {
		std::this_thread::sleep_for(std::chrono::seconds(seconds));
	}
} // namespace ui
