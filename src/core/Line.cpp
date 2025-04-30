#include "line.hpp"

Line::Line() {}

void Line::add_point(int x, int y) {
    path_.emplace_back(x, y);
    visited_.insert({x, y});
}

void Line::remove_last_point() {
    if (!path_.empty()) {
        auto last = path_.back();
        path_.pop_back();
        visited_.erase(last);
    }
}

const std::vector<std::pair<int, int>> &Line::get_path() const {
    return path_;
}

bool Line::contains(int x, int y) const {
    return visited_.count({x, y}) > 0;
}

void Line::clear() {
    path_.clear();
    visited_.clear();
}

int Line::size() const {
    return path_.size();
}

// Функція перетворення координат на рядок (для hash-функції)
std::string Line::coord_to_str(int x, int y) const {
    return std::to_string(x) + "," + std::to_string(y);
}
