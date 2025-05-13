/* ----------------------------------------------------------------<Header>-
 Name: direction.cpp
 Title: Direction class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-29
 Revised: 2025-05-14
 Description: Implementation of direction movement and utility functions.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/direction.h"

/* ---------------------------------------------------------------------[<]-
 Function: get_dx
 Synopsis: Returns X-axis movement for the given direction.
 ---------------------------------------------------------------------[>]*/
int DirectionHelper::get_dx(Direction dir) {
    switch (dir) {
        case Direction::LEFT:
            return -1;
        case Direction::RIGHT:
            return 1;
        default:
            return 0;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: get_dy
 Synopsis: Returns Y-axis movement for the given direction.
 ---------------------------------------------------------------------[>]*/
int DirectionHelper::get_dy(Direction dir) {
    switch (dir) {
        case Direction::UP:
            return -1;
        case Direction::DOWN:
            return 1;
        default:
            return 0;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: get_dir_delta
 Synopsis: Returns Direction enum value for a given delta (dx, dy).
 ---------------------------------------------------------------------[>]-*/
Direction DirectionHelper::get_dir_delta(int dx, int dy) {
    if (dx == 0 && dy == -1) {
        return Direction::UP;
    } else if (dx == 0 && dy ==  1) {
        return Direction::DOWN;
    } else if (dx == -1 && dy == 0) {
        return Direction::LEFT;
    } else if (dx == 1 && dy == 0) { 
        return Direction::RIGHT; 
    } else {
        return Direction::NONE;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: get_delta
 Synopsis: Returns delta (dx, dy) for the given direction.
 ---------------------------------------------------------------------[>]*/
std::pair<int, int> DirectionHelper::get_delta(Direction dir) {
    switch (dir) {
        case Direction::UP:
            return {0, -1};
        case Direction::DOWN:
            return {0, 1};
        case Direction::LEFT:
            return {-1, 0};
        case Direction::RIGHT:
            return {1, 0};
        default:
            return {0, 0};
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: opposite
 Synopsis: Returns opposite direction.
 ---------------------------------------------------------------------[>]*/
Direction DirectionHelper::opposite(Direction dir) {
    switch (dir) {
        case Direction::UP:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::LEFT;
        default:
            return Direction::NONE;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: rotate_left
 Synopsis: Returns direction rotated 90° counter-clockwise.
 ---------------------------------------------------------------------[>]*/
Direction DirectionHelper::rotate_left(Direction dir) {
    switch (dir) {
        case Direction::UP:
            return Direction::LEFT;
        case Direction::LEFT:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::UP;
        default:
            return Direction::NONE;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: rotate_right
 Synopsis: Returns direction rotated 90° clockwise.
 ---------------------------------------------------------------------[>]*/
Direction DirectionHelper::rotate_right(Direction dir) {
    switch (dir) {
        case Direction::UP:
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::LEFT;
        case Direction::LEFT:
            return Direction::UP;
        default:
            return Direction::NONE;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: is_valid
 Synopsis: Checks if the direction is valid (not NONE).
 ---------------------------------------------------------------------[>]*/
bool DirectionHelper::is_valid_direction(Direction dir) {
    return dir == Direction::UP || dir == Direction::DOWN || dir == Direction::LEFT || dir == Direction::RIGHT || dir == Direction::NONE;
}

/* ---------------------------------------------------------------------[<]-
 Function: perpendicular
 Synopsis: Returns a vector of two perpendicular directions.
 ---------------------------------------------------------------------[>]*/
std::pair<Direction, Direction> DirectionHelper::get_perpendicular(Direction dir) {
    switch (dir) {
        case Direction::UP:
            return {Direction::LEFT, Direction::RIGHT};
        case Direction::DOWN:
            return {Direction::LEFT, Direction::RIGHT};
        case Direction::LEFT:
            return {Direction::UP, Direction::DOWN};
        case Direction::RIGHT:
            return {Direction::UP, Direction::DOWN};
        default:
            return {};
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: direction_to_string
 Synopsis: Returns direction name as string.
 ---------------------------------------------------------------------[>]*/
const char *DirectionHelper::to_string(Direction dir) {
    switch (dir) {
        case Direction::UP:
            return "UP";
        case Direction::DOWN:
            return "DOWN";
        case Direction::LEFT:
            return "LEFT";
        case Direction::RIGHT:
            return "RIGHT";
        case Direction::NONE:
            return "NONE";
        default:
            return "UNKNOWN";
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: all_dirs
 Synopsis: Returns a vector of all directions.
 ---------------------------------------------------------------------[>]*/
std::vector<Direction> DirectionHelper::get_all_dirs() {
    return {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
}

