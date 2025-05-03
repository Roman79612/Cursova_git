/* ----------------------------------------------------------------<Header>-
 Name: path.cc
 Title: Path class implementation (stack for solving)
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Stack-like implementation for tracking path in DFS/backtracking.
 ------------------------------------------------------------------</Header>-*/

#include "../core_headers/path.h"

/* ---------------------------------------------------------------------[<]-
 Function: Path::Path
 Synopsis: Default constructor initializes empty path.
 ---------------------------------------------------------------------[>]-*/
Path::Path() = default;

/* ---------------------------------------------------------------------[<]-
 Function: Path::push
 Synopsis: Adds a new cell coordinate to the path.
 ---------------------------------------------------------------------[>]-*/
void Path::push(int x, int y) {
    stack.emplace_back(x, y);
}

/* ---------------------------------------------------------------------[<]-
 Function: Path::pop
 Synopsis: Removes the last cell from the path.
 ---------------------------------------------------------------------[>]-*/
void Path::pop() {
    if (!stack.empty()) {
        stack.pop_back();
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: Path::top
 Synopsis: Returns the most recently added cell.
 ---------------------------------------------------------------------[>]-*/
std::pair<int, int> Path::top() const {
    return !stack.empty() ? stack.back() : std::make_pair(-1, -1);
}

/* ---------------------------------------------------------------------[<]-
 Function: Path::contains
 Synopsis: Checks if the path already contains the given cell.
 ---------------------------------------------------------------------[>]-*/
bool Path::contains(int x, int y) const {
    for (const auto& cell : stack) {
        if (cell.first == x && cell.second == y) {
            return true;
        }
    }
    return false;
}

/* ---------------------------------------------------------------------[<]-
 Function: Path::size
 Synopsis: Returns the number of elements in the path.
 ---------------------------------------------------------------------[>]-*/
size_t Path::size() const {
    return stack.size();
}

/* ---------------------------------------------------------------------[<]-
 Function: Path::clear
 Synopsis: Clears the current path.
 ---------------------------------------------------------------------[>]-*/
void Path::clear() {
    stack.clear();
}

/* ---------------------------------------------------------------------[<]-
 Function: Path::get_all
 Synopsis: Returns the full list of cells in the path.
 ---------------------------------------------------------------------[>]-*/
const std::vector<std::pair<int, int>>& Path::get_all() const {
    return stack;
}
