#include "field.hpp"

Field::Field(int width, int height)
    : width_(width), height_(height)
{
    cells_.resize(height_);
    for (int y = 0; y < height_; ++y) {
        cells_[y].reserve(width_);
        for (int x = 0; x < width_; ++x) {
            cells_[y].emplace_back(x, y);
        }
    }
}

int Field::get_width() const {
    return width_;
}

int Field::get_height() const {
    return height_;
}

bool Field::is_valid(int x, int y) const {
    return x >= 0 && y >= 0 && x < width_ && y < height_;
}

Cell &Field::get_cell(int x, int y) {
    return cells_[y][x];
}

const Cell &Field::get_cell(int x, int y) const {
    return cells_[y][x];
}

void Field::update_directions() {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            update_directions_for_cell(x, y);
        }
    }
}

void Field::update_directions_for_cell(int x, int y) {
    Cell &cell = get_cell(x, y);
    cell.get_directions().clear();

    static const std::vector<std::pair<Direction, std::pair<int, int>>> deltas = {
        {Direction::UP, {0, -1}},
        {Direction::DOWN, {0, 1}},
        {Direction::LEFT, {-1, 0}},
        {Direction::RIGHT, {1, 0}}
    };

    for (const auto &[dir, delta] : deltas) {
        int nx = x + delta.first;
        int ny = y + delta.second;
        if (is_valid(nx, ny)) {
            const Cell &neighbor = get_cell(nx, ny);
            if (neighbor.get_type() != CellType::WALL) {
                cell.add_direction(dir);
            }
        }
    }
}
