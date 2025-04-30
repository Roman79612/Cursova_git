#include "direction.hpp"

direction reverse_direction(direction dir)
{
    return static_cast<direction>((dir + 2) % 4);
}

direction rotate_direction(direction dir, int angle)
{
    return static_cast<direction>((dir + angle / 90) % 4);
}
