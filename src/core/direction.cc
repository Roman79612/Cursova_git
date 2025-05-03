/* ----------------------------------------------------------------<Header>-
 Name: direction.cc
 Title: Direction class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Source file implementing methods for direction handling.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/direction.h"

/* ---------------------------------------------------------------------[<]- 
 Function: DirectionHelper::get_dx
 Synopsis: Returns the change in the x-coordinate for a given direction.
 ---------------------------------------------------------------------[>]-*/
int DirectionHelper::get_dx(Direction dir) {
    switch (dir) {
        case Direction::UP: return 0;
        case Direction::DOWN: return 0;
        case Direction::LEFT: return -1;
        case Direction::RIGHT: return 1;
        default: return 0;
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: DirectionHelper::get_dy
 Synopsis: Returns the change in the y-coordinate for a given direction.
 ---------------------------------------------------------------------[>]-*/
int DirectionHelper::get_dy(Direction dir) {
    switch (dir) {
        case Direction::UP: return -1;
        case Direction::DOWN: return 1;
        case Direction::LEFT: return 0;
        case Direction::RIGHT: return 0;
        default: return 0;
    }
}

/* ---------------------------------------------------------------------[<]- 
 Function: DirectionHelper::direction_to_string
 Synopsis: Converts a direction to a string for output.
 ---------------------------------------------------------------------[>]-*/
const char* DirectionHelper::direction_to_string(Direction dir) {
    switch (dir) {
        case Direction::UP: return "UP";
        case Direction::DOWN: return "DOWN";
        case Direction::LEFT: return "LEFT";
        case Direction::RIGHT: return "RIGHT";
        default: return "UNKNOWN";
    }
}
