/* ----------------------------------------------------------------<Header>-
 Name: direction.cpp
 Title: Direction class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-05
 Description: Implementation of direction movement and utility functions.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/direction.h"

/* ---------------------------------------------------------------------[<]-
 Function: get_dx
 Synopsis: Returns X-axis movement for the given direction.
 ---------------------------------------------------------------------[>]*/
int DirectionHelper::get_dx(Direction dir) {
    switch (dir) {
        case Direction::LEFT:  return -1;
        case Direction::RIGHT: return 1;
        default:               return 0;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: get_dy
 Synopsis: Returns Y-axis movement for the given direction.
 ---------------------------------------------------------------------[>]*/
int DirectionHelper::get_dy(Direction dir) {
    switch (dir) {
        case Direction::UP:    return -1;
        case Direction::DOWN:  return 1;
        default:               return 0;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: opposite
 Synopsis: Returns opposite direction.
 ---------------------------------------------------------------------[>]*/
Direction DirectionHelper::opposite(Direction dir) {
    switch (dir) {
        case Direction::UP:    return Direction::DOWN;
        case Direction::DOWN:  return Direction::UP;
        case Direction::LEFT:  return Direction::RIGHT;
        case Direction::RIGHT: return Direction::LEFT;
        default:               return Direction::NONE;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: rotate_left
 Synopsis: Returns direction rotated 90° counter-clockwise.
 ---------------------------------------------------------------------[>]*/
Direction DirectionHelper::rotate_left(Direction dir) {
    switch (dir) {
        case Direction::UP:    return Direction::LEFT;
        case Direction::LEFT:  return Direction::DOWN;
        case Direction::DOWN:  return Direction::RIGHT;
        case Direction::RIGHT: return Direction::UP;
        default:               return Direction::NONE;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: rotate_right
 Synopsis: Returns direction rotated 90° clockwise.
 ---------------------------------------------------------------------[>]*/
Direction DirectionHelper::rotate_right(Direction dir) {
    switch (dir) {
        case Direction::UP:    return Direction::RIGHT;
        case Direction::RIGHT: return Direction::DOWN;
        case Direction::DOWN:  return Direction::LEFT;
        case Direction::LEFT:  return Direction::UP;
        default:               return Direction::NONE;
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
 Function: direction_to_string
 Synopsis: Returns direction name as string.
 ---------------------------------------------------------------------[>]*/
const char *DirectionHelper::direction_to_string(Direction dir) {
    switch (dir) {
        case Direction::UP:    return "UP";
        case Direction::DOWN:  return "DOWN";
        case Direction::LEFT:  return "LEFT";
        case Direction::RIGHT: return "RIGHT";
        case Direction::NONE:  return "NONE";
        default:               return "UNKNOWN";
    }
}
