/* ----------------------------------------------------------------<Header>-
 Name: line.cc
 Title: Line class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Implementation of line rendering from path.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/line.h"

/* ---------------------------------------------------------------------[<]-
 Function: Line::Line
 Synopsis: Default constructor initializes empty line.
 ---------------------------------------------------------------------[>]-*/
Line::Line() : max_x(0), max_y(0) {}

/* ---------------------------------------------------------------------[<]-
 Function: Line::set_path
 Synopsis: Accepts a path and prepares the rendered Unicode line.
 ---------------------------------------------------------------------[>]-*/
void Line::set_path(const std::vector<std::pair<int, int>>& path) {
    cells = path;

    // Оновлення максимальних розмірів
    max_x = 0;
    max_y = 0;
    for (const auto& [x, y] : cells) {
        if (x > max_x) max_x = x;
        if (y > max_y) max_y = y;
    }

    rendered = std::vector<std::vector<wchar_t>>(max_y + 1, std::vector<wchar_t>(max_x + 1, L' '));
    render_line();
}

/* ---------------------------------------------------------------------[<]-
 Function: Line::render_line
 Synopsis: Renders the Unicode line based on path directions.
 ---------------------------------------------------------------------[>]-*/
void Line::render_line() {
    for (size_t i = 1; i < cells.size() - 1; ++i) {
        int x_prev = cells[i - 1].first;
        int y_prev = cells[i - 1].second;
        int x_curr = cells[i].first;
        int y_curr = cells[i].second;
        int x_next = cells[i + 1].first;
        int y_next = cells[i + 1].second;

        wchar_t symbol = get_unicode_for_direction(x_prev, y_prev, x_next, y_next);
        rendered[y_curr][x_curr] = symbol;
    }

    // Кінці лінії: просто пряма (─ або │)
    if (cells.size() >= 2) {
        int x0 = cells[0].first, y0 = cells[0].second;
        int x1 = cells[1].first, y1 = cells[1].second;
        rendered[y0][x0] = get_unicode_for_direction(x0, y0, x1, y1);

        int xn = cells.back().first, yn = cells.back().second;
        int xnm1 = cells[cells.size() - 2].first, ynm1 = cells[cells.size() - 2].second;
        rendered[yn][xn] = get_unicode_for_direction(xnm1, ynm1, xn, yn);
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Line::get_unicode_for_direction
 Synopsis: Determines the Unicode box drawing symbol based on relative direction.
 ---------------------------------------------------------------------[>]-*/
wchar_t Line::get_unicode_for_direction(int x1, int y1, int x2, int y2) const {
    int dx = x2 - x1;
    int dy = y2 - y1;

    if ((dx == 0 && dy == -1) || (dx == 0 && dy == 1)) {
        return L'│'; // вертикаль
    } else if ((dx == -1 && dy == 0) || (dx == 1 && dy == 0)) {
        return L'─'; // горизонталь
    } else if ((dx == 1 && dy == -1) || (dx == -1 && dy == 1)) {
        return L'┌'; // кут вправо-вгору або вліво-вниз
    } else if ((dx == -1 && dy == -1) || (dx == 1 && dy == 1)) {
        return L'┐'; // кут вліво-вгору або вправо-вниз
    } else if ((dx == -1 && dy == 1) || (dx == 1 && dy == -1)) {
        return L'└'; // кут вліво-вниз або вправо-вгору
    } else if ((dx == 1 && dy == 1) || (dx == -1 && dy == -1)) {
        return L'┘'; // кут вправо-вниз або вліво-вгору
    } else {
        return L' '; // помилкова ситуація
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Line::get_rendered_line
 Synopsis: Returns the rendered Unicode line grid.
 ---------------------------------------------------------------------[>]-*/
const std::vector<std::vector<wchar_t>>& Line::get_rendered_line() const {
    return rendered;
}
