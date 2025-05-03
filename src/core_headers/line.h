/* ----------------------------------------------------------------<Header>-
 Name: line.h
 Title: Line class definition (line rendering from path)
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Class for converting path into a visual line using Unicode symbols.
 ------------------------------------------------------------------</Header>-*/

#ifndef LINE_H
#define LINE_H

#include <vector>
#include <utility>
#include <cwchar>

class Line {
public:
    Line();

    void set_path(const std::vector<std::pair<int, int>>& path);
    wchar_t get_unicode_for_direction(int x1, int y1, int x2, int y2) const;
    const std::vector<std::vector<wchar_t>>& get_rendered_line() const;

private:
    std::vector<std::pair<int, int>> cells;
    std::vector<std::vector<wchar_t>> rendered;
    void render_line();
    int max_x, max_y;
};

#endif // LINE_H
