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
void ui::print_rules(int field_height) {
    const std::vector<std::wstring> rules_box = {
        GREEN     L"╔════════════════════════════════════════════════════════╗",
        GREEN     L"║                         " RED BOLD L"MASYU RULES" RESET_COLOUR GREEN L"                    ║",
        GREEN     L"║   " RESET_COLOUR L"1. Draw a single loop through cell centers.          " GREEN L"║",
        GREEN     L"║   " RESET_COLOUR L"2. The loop must not cross or overlap itself.        " GREEN L"║",
        GREEN     L"║   " RESET_COLOUR L"3. The loop cannot reverse direction.                " GREEN L"║",
        GREEN     L"║   " RESET_COLOUR L"4. ● Must turn and go straight before & after.       " GREEN L"║",
        GREEN     L"║   " RESET_COLOUR L"5. ○ Must go straight and turn before or after.      " GREEN L"║",
        GREEN     L"║   " RESET_COLOUR L"6. The loop must pass through all circles.           " GREEN L"║",
        GREEN     L"║   " RESET_COLOUR L"7. The loop must form a closed cycle.                " GREEN L"║",
        GREEN     L"╚════════════════════════════════════════════════════════╝" RESET_COLOUR
    };

    int top_indent = field_height * 2 + HEIGHT_TITLE;
    int right_indent = ui::get_terminal_width() - WIDTH_RULES_BOX;
    int bottom_indent = top_indent - HEIGHT_RULES_BOX;

    ui::move_cursor_up(top_indent);

    for (const auto& line : rules_box) {
        ui::move_cursor_right(right_indent);
        std::wcout << line << std::endl;
    }

    ui::move_cursor_down(bottom_indent);
}

/* ----------------------------------------------------------------------[<]-
    Function: print_centered
    Synopsis: Prints a centered text in the terminal. (half-width)
-------------------------------------------------------------------------[>]*/
void ui::print_centered_title_half(const std::wstring& text) {
    int terminal_height = ui::get_terminal_height();
    int terminal_width = ui::get_terminal_width();
    int total_width = terminal_width / 2;
    int padding = (total_width - static_cast<int>(text.size())) / 2;
    if (padding < 0) padding = 0;

    ui::print_new_line(terminal_height);
    ui::move_cursor_up(terminal_height);
    ui::print_separator_half();
    std::wcout << std::wstring(padding, L' ') << RED << text << RESET_COLOUR << std::endl;
    ui::print_separator_half();
}

/* ----------------------------------------------------------------------[<]-
    Function: print_centered_title
    Synopsis: Prints a centered title in the terminal. (full-width)
-------------------------------------------------------------------------[>]*/
void ui::print_centered_title(const std::wstring& text) {
    int terminal_height = ui::get_terminal_height();
    int terminal_width = ui::get_terminal_width();
    int total_width = terminal_width;
    int padding = (total_width - static_cast<int>(text.size())) / 2;
    if (padding < 0) padding = 0;

    ui::print_new_line(terminal_height);
    ui::move_cursor_up(terminal_height);
    ui::print_separator_full();
    std::wcout << std::wstring(padding, L' ') << RED << text << RESET_COLOUR << std::endl;
    ui::print_separator_full();
}

/* ----------------------------------------------------------------------[<]-
    Function: print_separator_half
    Synopsis: Prints a half-width horizontal separator line.
-------------------------------------------------------------------------[>]*/
void ui::print_separator_half() {
    int terminal_width = ui::get_terminal_width();
    int total_width = terminal_width / 2;
    std::wcout << GREEN << std::wstring(total_width, L'═') << RESET_COLOUR << std::endl;
}

/* ----------------------------------------------------------------------[<]-
    Function: print_separator_full
    Synopsis: Prints a full-width horizontal separator line.
-------------------------------------------------------------------------[>]*/
void ui::print_separator_full() {
    int terminal_width = ui::get_terminal_width();
    const int total_width = terminal_width;
    std::wcout << GREEN << std::wstring(total_width, L'═') << RESET_COLOUR << std::endl;
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

/* ----------------------------------------------------------------------[<]-
    Function: move_cursor_up
    Synopsis: Moves the cursor up by the specified number of lines.
-------------------------------------------------------------------------[>]*/
void ui::move_cursor_up(int lines) {
    std::wcout << "\x1b[" << lines << "A";
}

/* ----------------------------------------------------------------------[<]-
    Function: move_cursor_down
    Synopsis: Moves the cursor down by the specified number of lines.
-------------------------------------------------------------------------[>]*/
void ui::move_cursor_down(int lines) {
    std::wcout << "\x1b[" << lines << "B";
}

/* ----------------------------------------------------------------------[<]-
    Function: move_cursor_left
    Synopsis: Moves the cursor left by the specified number of columns.
-------------------------------------------------------------------------[>]*/
void ui::move_cursor_left(int cols) {
    std::wcout << "\x1b[" << cols << "D";
}

/* ----------------------------------------------------------------------[<]-
    Function: move_cursor_right
    Synopsis: Moves the cursor right by the specified number of columns.
-------------------------------------------------------------------------[>]*/
void ui::move_cursor_right(int cols) {
    std::wcout << "\x1b[" << cols << "C";
}

/* ----------------------------------------------------------------------[<]-
    Function: move_cursor_home
    Synopsis: Moves the cursor to the home position (top-left corner).
-------------------------------------------------------------------------[>]*/
void ui::move_cursor_end() {
    std::wcout << "\x1b[999C";
}

/* ----------------------------------------------------------------------[<]-
    Function: print_new_line
    Synopsis: Prints the specified number of new lines.
-------------------------------------------------------------------------[>]*/
void ui::print_new_line(int lines) {
    for (int i = 0; i < lines; ++i) {
        std::wcout << std::endl;
    }
}

/* ----------------------------------------------------------------------[<]-
    Function: backspace
    Synopsis: Moves the cursor back by the specified number of lines.
-------------------------------------------------------------------------[>]*/
void ui::backspace(int lines) {
    for (int i = 0; i < lines; ++i) {
        std::wcout << L"\x1b[1D" << L' ' << L"\x1b[1D";
    }
    std::wcout.flush();
}