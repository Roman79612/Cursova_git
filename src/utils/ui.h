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

namespace ui {
    void print_rules(int field_lines);
    void print_centered(const std::wstring& text);
    void print_centered_title(const std::wstring& text);
    void print_separator_half();
    void print_separator_full();
    void sleep_for_seconds(int seconds);
    int get_terminal_width();
    int get_terminal_height();
}

#endif // UI_H