/* ----------------------------------------------------------------<Header>-
 Name: ui.h
  Title: Console output utilities
  Group: TV-42
  Student: Kriuchkov R. Y.
  Written: 2025-05-05
  Revised: 2025-05-05
  Description: This file contains utility functions for console output, including moving the cursor, clearing the console, and printing formatted text.
 ------------------------------------------------------------------</Header>-*/

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>

namespace ui {
    void print_field_with_rules(const std::function<void()>& print_field_func);
    void print_centered(const std::wstring& text);
    void print_separator();
    void sleep_for_seconds(int seconds);
    int get_lines_printed();
}
