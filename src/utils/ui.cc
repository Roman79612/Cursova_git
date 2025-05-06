/* ----------------------------------------------------------------<Header>-
 Name: ui.cc
 Title: Implementation of utility functions for console output
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-05
 Revised: 2025-05-06
 Description: This file contains the implementation of functions for manipulating the console output, such as moving the cursor, clearing the console,
 and formatted text.
 ------------------------------------------------------------------</Header>-*/

#include "../utils/ui.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/* ----------------------------------------------------------------------[<]-
    Function: print_rules
    Synopsis: Prints the rules of the game in a formatted box.
-------------------------------------------------------------------------[>]*/
void ui::print_rules(int field_lines) {
    const std::vector<std::wstring> rules_box = {
        L"\x1b[32m╔════════════════════════════════════════════════════════╗",
        L"\x1b[32m║ \x1b[31m                     MASYU RULES:                      \x1b[32m║",
        L"\x1b[32m║   \x1b[0m1. Draw a single loop through cell centers.          \x1b[32m║",
        L"\x1b[32m║   \x1b[0m2. The loop must not cross or overlap itself.        \x1b[32m║",
        L"\x1b[32m║   \x1b[0m3. The loop cannot reverse direction.                \x1b[32m║",
        L"\x1b[32m║   \x1b[0m4. ● Must turn and go straight before & after.       \x1b[32m║",
        L"\x1b[32m║   \x1b[0m5. ○ Must go straight and turn before or after.      \x1b[32m║",
        L"\x1b[32m║   \x1b[0m6. The loop must pass through all circles.           \x1b[32m║",
        L"\x1b[32m║   \x1b[0m7. The loop must form a closed cycle.                \x1b[32m║",
        L"\x1b[32m╚════════════════════════════════════════════════════════╝\x1b[0m"
    };

    int top_indent = (field_lines + 2) * 2;
    int right_indent = ui::get_terminal_width() - 58;

    std::wcout << L"\x1b[" << top_indent << L"A";

    for (const auto& line : rules_box) {
        std::wcout << L"\x1b[" << right_indent << L"C" << line << std::endl;
    }

    int bottom_indent = top_indent - 10;
    std::wcout << L"\x1b[" << bottom_indent << L"B";
}

/* ----------------------------------------------------------------------[<]-
    Function: print_centered
    Synopsis: Prints a centered text in the terminal. (half-width)
-------------------------------------------------------------------------[>]*/
void ui::print_centered(const std::wstring& text) {
    int terminal_height = ui::get_terminal_height();
    for (int i = 0; i < terminal_height; ++i) {
        std::wcout << std::endl;
    }

    std::wcout << L"\x1b[" << terminal_height << L"A";
    ui::print_separator_half();

    int terminal_width = ui::get_terminal_width();
    const int total_width = terminal_width / 2;
    int padding = (total_width - static_cast<int>(text.size())) / 2;
    if (padding < 0) padding = 0;

    std::wcout << L"\x1b[31m" << std::wstring(padding, L' ') << text << L"\x1b[0m" << std::endl;

    ui::print_separator_half();
}

/* ----------------------------------------------------------------------[<]-
    Function: print_centered_title
    Synopsis: Prints a centered title in the terminal. (full-width)
-------------------------------------------------------------------------[>]*/
void ui::print_centered_title(const std::wstring& text) {
    int terminal_height = ui::get_terminal_height();
    for (int i = 0; i < terminal_height; ++i) {
        std::wcout << std::endl;
    }

    std::wcout << L"\x1b[" << terminal_height << L"A";
    ui::print_separator_full();

    int terminal_width = ui::get_terminal_width();
    const int total_width = terminal_width;
    int padding = (total_width - static_cast<int>(text.size())) / 2;
    if (padding < 0) padding = 0;

    std::wcout << L"\x1b[31m" << std::wstring(padding, L' ') << text << L"\x1b[0m" << std::endl;

    ui::print_separator_full();
}

/* ----------------------------------------------------------------------[<]-
    Function: print_separator_half
    Synopsis: Prints a half-width horizontal separator line.
-------------------------------------------------------------------------[>]*/
void ui::print_separator_half() {
    int terminal_width = ui::get_terminal_width();
    const int total_width = terminal_width / 2;
    std::wcout << L"\x1b[32m" << std::wstring(total_width, L'═') << L"\x1b[0m" << std::endl;
}

/* ----------------------------------------------------------------------[<]-
    Function: print_separator_full
    Synopsis: Prints a full-width horizontal separator line.
-------------------------------------------------------------------------[>]*/
void ui::print_separator_full() {
    int terminal_width = ui::get_terminal_width();
    const int total_width = terminal_width;
    std::wcout << L"\x1b[32m" << std::wstring(total_width, L'═') << L"\x1b[0m" << std::endl;
}

/* ----------------------------------------------------------------------[<]-
    Function: sleep_for_seconds
    Synopsis: Sleeps for the specified number of seconds.
-------------------------------------------------------------------------[>]*/
void ui::sleep_for_seconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

/* ----------------------------------------------------------------------[<]-
    Function: get_terminal_width
    Synopsis: Returns the width of the terminal in characters.
-------------------------------------------------------------------------[>]*/
int ui::get_terminal_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

/* ----------------------------------------------------------------------[<]-
    Function: get_terminal_height
    Synopsis: Returns the height of the terminal in characters.
-------------------------------------------------------------------------[>]*/
int ui::get_terminal_height() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}
