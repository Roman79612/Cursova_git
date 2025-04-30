#include "direction.hpp"

int delta_x(Direction dir) {
    switch (dir) {
        case Direction::RIGHT: return 1;
        case Direction::LEFT:  return -1;
        default: return 0;
    }
}

int delta_y(Direction dir) {
    switch (dir) {
        case Direction::DOWN:  return 1;
        case Direction::UP:    return -1;
        default: return 0;
    }
}

Direction rotate_right(Direction dir) {
    switch (dir) {
        case Direction::RIGHT: return Direction::DOWN;
        case Direction::DOWN:  return Direction::LEFT;
        case Direction::LEFT:  return Direction::UP;
        case Direction::UP:    return Direction::RIGHT;
    }
    return dir; // fallback
}

Direction rotate_left(Direction dir) {
    switch (dir) {
        case Direction::RIGHT: return Direction::UP;
        case Direction::UP:    return Direction::LEFT;
        case Direction::LEFT:  return Direction::DOWN;
        case Direction::DOWN:  return Direction::RIGHT;
    }
    return dir;
}

Direction opposite(Direction dir) {
    return rotate(dir, 180);
}

Direction rotate(Direction dir, int degrees) {
    int steps = (degrees / 90) % 4;
    if (steps < 0) steps += 4;
    for (int i = 0; i < steps; ++i) {
        dir = rotate_right(dir);
    }
    return dir;
}
