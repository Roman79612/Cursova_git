#include "cell.hpp"

cell::cell(int x_value, int y_value, cell_type cell_kind)
{
    x = x_value;
    y = y_value;
    type = cell_kind;
    visited = false;
}

void cell::mark_visited()
{
    visited = true;
}

void cell::reset()
{
    visited = false;
}
