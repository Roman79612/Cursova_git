#include "line.h"

using namespace std;

Line::Line(Position start, Direction dir) : currentDir(dir) {
    path.push_back(start);
}

bool Line::move(Position next) {
    path.push_back(next);
    return true;
}

void Line::undo() {
    if (path.size() > 1)
        path.pop_back();
}

const vector<Position>& Line::getPath() const {
    return path;
}

Position Line::getCurrent() const {
    return path.back();
}

Direction Line::getDirection() const {
    return currentDir;
}

void Line::setDirection(Direction dir) {
    currentDir = dir;
}

int Line::getLength() const {
    return static_cast<int>(path.size());
}

bool Line::contains(Position pos) const {
    for (const auto& p : path) {
        if (p == pos)
            return true;
    }
    return false;
}

void Line::reset() {
    path.clear();
    path.push_back({0, 0});
    currentDir = Direction::Right;
}