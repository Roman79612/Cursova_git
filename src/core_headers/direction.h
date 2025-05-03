/* ----------------------------------------------------------------<Header>-
 Name: direction.h
 Title: Direction class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Header file for handling movement directions in the puzzle grid.
 ------------------------------------------------------------------</Header>-*/

#ifndef DIRECTION_H
#define DIRECTION_H

// Enum for directions
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Class for representing a direction
class DirectionHelper {
public:
    static int get_dx(Direction dir);
    static int get_dy(Direction dir);
    static const char* direction_to_string(Direction dir);
};

#endif // DIRECTION_H
