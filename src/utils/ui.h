/* ----------------------------------------------------------------<Header>-
 Name: ui.h
  Title: Console output utilities
  Group: TV-42
  Student: Kriuchkov R. Y.
  Written: 2025-05-05
  Revised: 2025-05-06
  Description: This file contains utility functions for console output, including moving the cursor, clearing the console, and printing formatted text.
 ------------------------------------------------------------------</Header>-*/

#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <regex>
#include <unistd.h>
#include <sys/ioctl.h>

#define WIDTH_RULES_BOX 58
#define HEIGHT_RULES_BOX 10
#define HEIGHT_TITLE 4

#define RESET_COLOUR "\x1b[0m"
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define BOLD "\x1b[1m"

namespace ui {
    void print_rules(int field_height);
    void print_centered_title_half(const std::wstring& text);
    void print_centered_title(const std::wstring& text);
    void print_separator_half();
    void print_separator_full();
    void sleep_for_seconds(int seconds);
    int get_terminal_width();
    int get_terminal_height();
    void move_cursor_up(int lines);
    void move_cursor_down(int lines);
    void move_cursor_left(int columns);
    void move_cursor_right(int columns);
    void move_cursor_end();
    void print_new_line(int lines);
    void backspace(int lines);
}

#endif // UI_H