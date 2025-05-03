/* ----------------------------------------------------------------<Header>-
 Name: state.cc
 Title: State class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-03
 Revised: 2025-05-03
 Description: Source file implementing the State class for pathfinding logic.
 ------------------------------------------------------------------</Header>-*/

#include "../logic_headers/state.h"

/* ---------------------------------------------------------------------[<]-
 Function: State::State
 Synopsis: Constructor initializing state with starting coordinates.
 ---------------------------------------------------------------------[>] */
State::State(const Field& field) : x(0), y(0), field(field) {
    path.emplace_back(x, y); // початкова точка шляху — (0, 0)
}

/* ---------------------------------------------------------------------[<]-
 Function: State::get_x
 Synopsis: Returns the x-coordinate of the current state.
 ---------------------------------------------------------------------[>] */
int State::get_x() const {
    return x;
}

/* ---------------------------------------------------------------------[<]-
 Function: State::get_y
 Synopsis: Returns the y-coordinate of the current state.
 ---------------------------------------------------------------------[>] */
int State::get_y() const {
    return y;
}

/* ---------------------------------------------------------------------[<]-
 Function: State::get_path
 Synopsis: Returns the reference to the current path.
 ---------------------------------------------------------------------[>] */
const std::vector<std::pair<int, int>>& State::get_path() const {
    return path;
}

/* ---------------------------------------------------------------------[<]-
 Function: State::add_to_path
 Synopsis: Adds a coordinate to the path and updates current position.
 ---------------------------------------------------------------------[>] */
void State::add_to_path(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    path.emplace_back(x, y);
}

/* ---------------------------------------------------------------------[<]-
 Function: State::is_visited
 Synopsis: Checks if a coordinate is already in the path.
 ---------------------------------------------------------------------[>] */
bool State::is_visited(int check_x, int check_y) const {
    for (const auto& cell : path) {
        if (cell.first == check_x && cell.second == check_y) {
            return true;
        }
    }
    return false;
}
