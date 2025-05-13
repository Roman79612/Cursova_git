/* ----------------------------------------------------------------<Header>-
 Name: ui.cc
 Title: Implementation of utility functions for console output
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-05
 Revised: 2025-05-14
 Description: This file contains the implementation of functions for manipulating the console output, such as moving the cursor, clearing the console,
 and formatted text.
 ------------------------------------------------------------------</Header>-*/

#include "../utils/ui.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

const std::vector<std::wstring> g_welcome_box = {
    GREEN BOLD L"╔══════════════════════════════════════════════════════════════════════╗",
    GREEN BOLD L"║                                                                      ║",
    GREEN BOLD L"║     " YELLOW BOLD L"██╗    ██╗███████╗██╗     ██████╗  ██████╗ ███╗   ███╗███████╗"  GREEN BOLD L"   ║",
    GREEN BOLD L"║     " YELLOW BOLD L"██║    ██║██╔════╝██║     ██╔═══╝ ██╔═══██╗████╗ ████║██╔════╝"  GREEN BOLD L"   ║",
    GREEN BOLD L"║     " YELLOW BOLD L"██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  "  GREEN BOLD L"   ║",
    GREEN BOLD L"║     " YELLOW BOLD L"██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  "  GREEN BOLD L"   ║",
    GREEN BOLD L"║     " YELLOW BOLD L"╚███╔███╔╝███████╗███████╗███████╗╚██████╔╝██║ ╚═╝ ██║███████╗"  GREEN BOLD L"   ║",
    GREEN BOLD L"║      " YELLOW BOLD L"╚══╝╚══╝ ╚══════╝╚══════╝╚══════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝"  GREEN BOLD L"   ║",
    GREEN BOLD L"║                                                                      ║",
    GREEN BOLD L"║                  " YELLOW BOLD L"Glad to have you here. Lets begin!" GREEN BOLD L"                  ║",
    GREEN BOLD L"║                                                                      ║",
    GREEN BOLD L"╚══════════════════════════════════════════════════════════════════════╝" RESET_COLOUR
};

const std::vector<std::wstring> g_menu_box = {
    GREEN BOLD L"╔════════════════════════════════════════════════════════╗",
    GREEN BOLD L"║                       " RED BOLD L"USERS MENU"  GREEN BOLD      L"                       ║",
    GREEN BOLD L"║                                                        ║",
    GREEN BOLD L"║                 " RESET_COLOUR BOLD L"1. Display all fields"  GREEN  L"                  ║",
    GREEN BOLD L"║                 " RESET_COLOUR BOLD L"2. Display field by number"  GREEN  L"             ║",
    GREEN BOLD L"║                 " RESET_COLOUR BOLD L"3. Create a custom field"  GREEN  L"               ║",
    GREEN BOLD L"║                 " RESET_COLOUR BOLD L"4. Show rules"  GREEN  L"                          ║",
    GREEN BOLD L"║                 " RESET_COLOUR BOLD L"5. Exit the program"  GREEN  L"                    ║",
    GREEN BOLD L"║                                                        ║",
    GREEN BOLD L"║               " RESET_COLOUR BOLD L"By default there are " YELLOW L"5" RESET_COLOUR BOLD L" fields" GREEN BOLD L"            ║",
    GREEN BOLD L"║                                                        ║",
    GREEN BOLD L"╚════════════════════════════════════════════════════════╝" RESET_COLOUR
};

const std::vector<std::wstring> g_rules_box = {
    GREEN BOLD L"╔════════════════════════════════════════════════════════╗",
    GREEN BOLD L"║                         " RED BOLD L"MASYU RULES" RESET_COLOUR GREEN BOLD L"                    ║",
    GREEN BOLD L"║   " RESET_COLOUR BOLD L"1. Draw a single loop through cell centers.          " GREEN L"║",
    GREEN BOLD L"║   " RESET_COLOUR BOLD L"2. The loop must not cross or overlap itself.        " GREEN L"║",
    GREEN BOLD L"║   " RESET_COLOUR BOLD L"3. The loop cannot reverse direction.                " GREEN L"║",
    GREEN BOLD L"║   " RESET_COLOUR BOLD L"4. ○ Must turn and go straight before & after.       " GREEN L"║",
    GREEN BOLD L"║   " RESET_COLOUR BOLD L"5. ● Must go straight and turn before or after.      " GREEN L"║",
    GREEN BOLD L"║   " RESET_COLOUR BOLD L"6. The loop must pass through all circles.           " GREEN L"║",
    GREEN BOLD L"║   " RESET_COLOUR BOLD L"7. The loop must form a closed cycle.                " GREEN L"║",
    GREEN BOLD L"╚════════════════════════════════════════════════════════╝" RESET_COLOUR
};

const std::vector<std::wstring> g_thank_you_box = {
    GREEN BOLD L"╔════════════════════════════════════════════════════════╗",
    GREEN BOLD L"║                                                        ║",
    GREEN BOLD L"║       " YELLOW BOLD L"████████╗██╗  ██╗ █████╗ ███╗   ██╗██╗  ██╗" BOLD GREEN L"      ║",
    GREEN BOLD L"║       " YELLOW BOLD L"╚══██╔══╝██║  ██║██╔══██╗████╗  ██║╚██╗██╔╝" BOLD GREEN L"      ║",
    GREEN BOLD L"║       " YELLOW BOLD L"   ██║   ███████║███████║██╔██╗ ██║ ╚███╔╝ " BOLD GREEN L"      ║",
    GREEN BOLD L"║       " YELLOW BOLD L"   ██║   ██╔══██║██╔══██║██║╚██╗██║ ██╔██╗ " BOLD GREEN L"      ║",
    GREEN BOLD L"║       " YELLOW BOLD L"   ██║   ██║  ██║██║  ██║██║ ╚████║██╔╝ ██╗" BOLD GREEN L"      ║",
    GREEN BOLD L"║       " YELLOW BOLD L"   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝" BOLD GREEN L"      ║",
    GREEN BOLD L"║                                                        ║",
    GREEN BOLD L"║            " YELLOW BOLD L"Thank you for using this program" BOLD GREEN L"            ║",
    GREEN BOLD L"║                                                        ║",
    GREEN BOLD L"╚════════════════════════════════════════════════════════╝" RESET_COLOUR
};

/* ----------------------------------------------------------------------[<]-
    Function: print_welcome
    Synopsis: Prints a welcome message in a formatted box.
-------------------------------------------------------------------------[>]*/
void ui::print_welcome() {
    int terminal_height = get_terminal_height();
    int terminal_width = get_terminal_width();
    int top_indent = (terminal_height + HEIGHT_WELCOME_BOX) / 2;
    int right_indent = (terminal_width - WIDTH_WELCOME_BOX) / 2;
    int bottom_indent = top_indent - HEIGHT_MENU_BOX;
    
    print_new_line(terminal_height);
    move_cursor_up(top_indent);

    for (const std::wstring& line : g_welcome_box) {
        move_cursor_right(right_indent);
        std::wcout << line << std::endl;
    }

    move_cursor_down(bottom_indent);
}

/* ----------------------------------------------------------------------[<]-
    Function: print_rules
    Synopsis: Prints the rules of the game in a formatted box close to field.
-------------------------------------------------------------------------[>]*/
void ui::print_rules(int field_height) {
    int top_indent = field_height * 2 + HEIGHT_TITLE;
    int right_indent = get_terminal_width() - WIDTH_RULES_BOX;
    int bottom_indent = top_indent - HEIGHT_RULES_BOX;

    move_cursor_up(top_indent);

    for (const std::wstring& line : g_rules_box) {
        move_cursor_right(right_indent);
        std::wcout << line << std::endl;
    }

    move_cursor_down(bottom_indent);
}

/* ----------------------------------------------------------------------[<]-
    Function: show_rules
    Synopsis: Prints the rules of the game in a formatted box on centre terminal.
-------------------------------------------------------------------------[>]*/
void ui::show_rules() {
    int terminal_height = get_terminal_height();
    int terminal_width = get_terminal_width();
    int top_indent = (terminal_height + HEIGHT_MENU_BOX) / 2;
    int right_indent = (terminal_width - WIDTH_MENU_BOX) / 2;
    int bottom_indent = top_indent - HEIGHT_MENU_BOX;
    
    print_centered_title(L"You chose menu item — \"Show rules\"");
    print_new_line(terminal_height - HEIGHT_TITLE);
    move_cursor_up(top_indent);

    sleep_for_milliseconds(SLEEP_TITLE);
    for (const std::wstring& line : g_rules_box) {
        move_cursor_right(right_indent);
        std::wcout << line << std::endl;
    }

    move_cursor_down(bottom_indent);
    sleep_for_milliseconds(SLEEP_RULES_BOX);
}

/* ----------------------------------------------------------------------[<]-
    Function: print_menu
    Synopsis: Prints the menu of the game in a formatted box.
-------------------------------------------------------------------------[>]*/
void ui::print_menu() {
    int terminal_height = get_terminal_height();
    int terminal_width = get_terminal_width();
    int top_indent = (terminal_height + HEIGHT_MENU_BOX) / 2;
    int right_indent = (terminal_width - WIDTH_MENU_BOX) / 2;
    int bottom_indent = top_indent - HEIGHT_MENU_BOX;
    
    print_new_line(terminal_height - HEIGHT_TITLE);
    move_cursor_up(top_indent);

    for (const std::wstring& line : g_menu_box) {
        move_cursor_right(right_indent);
        std::wcout << line << std::endl;
    }

    move_cursor_down(bottom_indent);
}

/* ----------------------------------------------------------------------[<]-
    Function: print_centered_title
    Synopsis: Prints a centered title in the terminal. (full-width)
-------------------------------------------------------------------------[>]*/
void ui::print_centered_title(const std::wstring& text) {
    int terminal_height = get_terminal_height();
    int terminal_width = get_terminal_width();
    int total_width = terminal_width;
    int padding = (total_width - static_cast<int>(text.size())) / 2;
    if (padding < 0) padding = 0;

    print_new_line(terminal_height);
    move_cursor_up(terminal_height);
    print_separator_full();
    print_new_line(1);
    print_separator_full();
    move_cursor_up(2);
    std::wcout << std::wstring(padding, L' ') << RED BOLD;
    print_typing_effect(text);
    std::wcout << RESET_COLOUR;
    move_cursor_down(2);
    move_cursor_left(padding + static_cast<int>(text.size()));
}

/* ----------------------------------------------------------------------[<]-
    Function: print_centered_title_bottom
    Synopsis: Prints a centered title in the terminal. (full-width)
-------------------------------------------------------------------------[>]*/
void ui::print_centered_title_bottom(const std::wstring& text) {
    int terminal_width = get_terminal_width();
    int total_width = terminal_width;
    int padding = (total_width - static_cast<int>(text.size())) / 2;
    if (padding < 0) padding = 0;

    move_cursor_up(HEIGHT_TITLE);
    print_separator_full();
    print_new_line(1);
    print_separator_full();
    move_cursor_up(2);
    std::wcout << std::wstring(padding, L' ') << RED BOLD;
    print_typing_effect(text);
    std::wcout << RESET_COLOUR;
    move_cursor_down(2);
    move_cursor_left(padding + static_cast<int>(text.size()));
}

/* ----------------------------------------------------------------------[<]-
    Function: print_separator_half
    Synopsis: Prints a half-width horizontal separator line.
-------------------------------------------------------------------------[>]*/
void ui::print_separator_half() {
    int terminal_width = get_terminal_width();
    int total_width = terminal_width / 2;
    std::wcout << GREEN BOLD << std::wstring(total_width, L'═') << RESET_COLOUR << std::endl;
}

/* ----------------------------------------------------------------------[<]-
    Function: print_separator_full
    Synopsis: Prints a full-width horizontal separator line.
-------------------------------------------------------------------------[>]*/
void ui::print_separator_full() {
    int terminal_width = get_terminal_width();
    const int total_width = terminal_width;
    std::wcout << GREEN BOLD << std::wstring(total_width, L'═') << RESET_COLOUR << std::endl;
}

/* ----------------------------------------------------------------------[<]-
    Function: sleep_for_milliseconds
    Synopsis: Sleeps for the specified number of seconds.
-------------------------------------------------------------------------[>]*/
void ui::sleep_for_milliseconds(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
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

/* ----------------------------------------------------------------------[<]-
Function: get_one_int
Synopsis: Prompts the user to enter a number between 1 and max (inclusive).
-------------------------------------------------------------------------[>]*/
int ui::get_one_int(int max) {
    int choice = -1;
    std::wstring input;

    while (true) {
        std::wcout << RED << BOLD;

        print_typing_effect(L"Enter your choice [1-");
        print_typing_effect(max);
        print_typing_effect(L"]: ");

        std::wcout << RESET_COLOUR << BOLD;

        std::getline(std::wcin, input);
    
        std::wstringstream ss(input);
        std::vector<int> numbers;
        int temp;

        while (ss >> temp) {
            numbers.push_back(temp);
        }

        if (numbers.size() == 1 && numbers[0] >= 1 && numbers[0] <= max) {
            choice = numbers[0];
            break;
        }

        std::wcout << L"Invalid input. Please enter a number from 1 to " << max << L".\n";
    }
    sleep_for_milliseconds(225);
    return choice;
}

/* ----------------------------------------------------------------------[<]-
Function: get_two_int
Synopsis: Prompts the user to enter two integers (x y) representing
-------------------------------------------------------------------------[>]*/
std::pair<int, int> ui::get_two_int(int width, int height) {
    int x = -1, y = -1;
    std::wstring input;
    
    while (true) {
        std::wcout << RED << BOLD;
        print_typing_effect(L"Enter two integer with space between: ");
        std::wcout << RESET_COLOUR << BOLD;
        std::getline(std::wcin, input);
    
        std::wstringstream ss(input);
        std::vector<int> numbers;
        int temp;

        while (ss >> temp) {
            numbers.push_back(temp);
        }

        if (numbers.size() == 2 && numbers[0] >= 0 && numbers[0] <= (width - 1) && numbers[1] >= 0 && numbers[1] <= (height - 1)) {
            x = numbers[0];
            y = numbers[1];
            break;
        }

        std::wcout << L"Please enter two numbers ∈ " << L"[0, " << (width - 1) << L"]\n";
    }
    return {x, y};
}

/* ----------------------------------------------------------------------[<]-
    Function: print_thank_you
    Synopsis: Prints a thank you message in a formatted box.
-------------------------------------------------------------------------[>]*/
void ui::print_thank_you() {
    int terminal_height = get_terminal_height();
    int terminal_width = get_terminal_width();
    int top_indent = (terminal_height + HEIGHT_THANK_BOX) / 2;
    int right_indent = (terminal_width - WIDTH_THANK_BOX) / 2;
    int bottom_indent = top_indent - HEIGHT_MENU_BOX;
    
    print_new_line(terminal_height);
    move_cursor_up(top_indent);

    for (const auto& line : g_thank_you_box) {
        move_cursor_right(right_indent);
        std::wcout << line << std::endl;
    }

    move_cursor_down(bottom_indent);
}

/* ----------------------------------------------------------------------[<]-
    Function: print_typing_effect
    Synopsis: Prints a wstring with typing effect.
-------------------------------------------------------------------------[>]*/
void ui::print_typing_effect(const std::wstring& text, int min_delay, int max_delay, int rare_delay, int rare_chance) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> delay_dist(min_delay, max_delay);
    std::uniform_int_distribution<> rare_dist(1, 100);

    int adjusted_min_delay = min_delay + (text.length() / 10);
    int adjusted_max_delay = max_delay - (text.length() / 10);

    adjusted_min_delay = std::max(adjusted_min_delay, min_delay);
    adjusted_max_delay = std::min(adjusted_max_delay, max_delay);

    for (wchar_t ch : text) {
        std::wcout << ch << std::flush;

        int delay = delay_dist(gen);
        if (rare_dist(gen) <= rare_chance) {
            delay = rare_delay;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

/* ----------------------------------------------------------------------[<]-
    Function: ui::print_typing_effect
    Synopsis: Overload for int with typing effect.
-------------------------------------------------------------------------[>]*/
void ui::print_typing_effect(int number, int min_delay, int max_delay, int rare_delay, int rare_chance) {
    print_typing_effect(std::to_wstring(number), min_delay, max_delay, rare_delay, rare_chance);
}
