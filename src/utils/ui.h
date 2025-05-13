/* ----------------------------------------------------------------<Header>-
 Name: ui.h
  Title: Console output utilities
  Group: TV-42
  Student: Kriuchkov R. Y.
  Written: 2025-05-05
  Revised: 2025-05-14
  Description: This file contains utility functions for console output, including moving the cursor, clearing the console, and printing formatted text.
 ------------------------------------------------------------------</Header>-*/

#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <cwctype>
#include <sstream>
#include <sys/ioctl.h>

//Sleep mode for particular situation
#define SLEEP_BEFORE_SOLVING 2750
#define SLEEP_AFTER_SOLVING 5500
#define SLEEP_POLITE_BOX 3750
#define SLEEP_RULES_BOX 7500
#define SLEEP_TITLE 1400

// Value to set up type effect
#define MIN 5
#define MAX 50
#define RARE_DELAY 200
#define CHANCE 5

// Max number to input
#define CHOICE 5
#define NUMBER_OF_FIELDS 5

// Size of boxes
#define HEIGHT_TITLE 4
#define WIDTH_RULES_BOX 58
#define HEIGHT_RULES_BOX 10
#define WIDTH_MENU_BOX 56
#define HEIGHT_MENU_BOX 12
#define WIDTH_WELCOME_BOX 72
#define HEIGHT_WELCOME_BOX 12
#define WIDTH_THANK_BOX 58
#define HEIGHT_THANK_BOX 12

// Colour
#define RESET_COLOUR "\x1b[0m"
#define YELLOW "\x1b[33m"
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define BOLD "\x1b[1m"

// global text fjr box
extern const std::vector<std::wstring> g_menu_box;
extern const std::vector<std::wstring> g_rules_box;
extern const std::vector<std::wstring> g_thank_you_box;
extern const std::vector<std::wstring> g_welcome_box;

namespace ui {
    void print_welcome();
    void print_rules(int field_height);
    void show_rules();
    void print_menu();
    void print_centered_title(const std::wstring& text);
    void print_centered_title_bottom(const std::wstring& text);
    void print_separator_half();
    void print_separator_full();
    void sleep_for_milliseconds(int milliseconds);
    int get_terminal_width();
    int get_terminal_height();
    void move_cursor_up(int lines);
    void move_cursor_down(int lines);
    void move_cursor_left(int columns);
    void move_cursor_right(int columns);
    void move_cursor_end();
    void print_new_line(int lines);
    void backspace(int lines);
    int get_one_int(int max);
    std::pair<int, int> get_two_int(int width, int height);
    void print_thank_you();
    void print_typing_effect(const std::wstring& text, int min_delay = MIN, int max_delay = MAX, int rare_delay = RARE_DELAY, int rare_chance = CHANCE);
    void print_typing_effect(int number, int min_delay = MIN, int max_delay = MAX, int rare_delay = RARE_DELAY, int rare_chance = CHANCE);
}

#endif // UI_H