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

bool is90Turn(Direction from, Direction to) {
    return (from == Direction::Up && to == Direction::Right) ||
           (from == Direction::Right && to == Direction::Down) ||
           (from == Direction::Down && to == Direction::Left) ||
           (from == Direction::Left && to == Direction::Up);
}

bool is270Turn(Direction from, Direction to) {
    return (from == Direction::Up && to == Direction::Left) ||
           (from == Direction::Left && to == Direction::Down) ||
           (from == Direction::Down && to == Direction::Right) ||
           (from == Direction::Right && to == Direction::Up);
}

bool is180Turn(Direction from, Direction to) {
    return getOpposite(from) == to;
}

int manhattanDistance(Position a, Position b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int heuristicDistance(Position from, const std::vector<Position>& targets) {
    int minDist = INT_MAX;
    for (const auto& target : targets) {
        minDist = std::min(minDist, manhattanDistance(from, target));
    }
    return minDist;
}
