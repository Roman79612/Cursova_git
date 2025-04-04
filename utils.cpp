#include "utils.h"

Direction getOpposite(Direction dir) {
    switch (dir) {
        case Direction::Up: return Direction::Down;
        case Direction::Down: return Direction::Up;
        case Direction::Left: return Direction::Right;
        case Direction::Right: return Direction::Left;
    }
    return Direction::Up; // fallback
}

Position moveInDirection(Position pos, Direction dir) {
    switch (dir) {
        case Direction::Up: return {pos.x, pos.y - 1};
        case Direction::Down: return {pos.x, pos.y + 1};
        case Direction::Left: return {pos.x - 1, pos.y};
        case Direction::Right: return {pos.x + 1, pos.y};
    }
    return pos;
}
