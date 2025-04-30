#include "field.hpp"

field::field(int width_value, int height_value)
{
    width = width_value;
    height = height_value;
    cells.resize(height);

    for (int y = 0; y < height; y++) {
        cells[y].reserve(width);
        for (int x = 0; x < width; x++) {
            cells[y].emplace_back(cell(x, y, CELL_NORMAL));
        }
    }
}

cell *field::get_cell(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return nullptr;
    }
    return &cells[y][x];
}

int field::get_width() const
{
    return width;
}

int field::get_height() const
{
    return height;
}
