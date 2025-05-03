/* ----------------------------------------------------------------<Header>-
 Name: path.h
 Title: Path class definition (used in Solver for DFS/backtracking)
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Helper class to store and manipulate current path during solving.
 ------------------------------------------------------------------</Header>-*/

#ifndef PATH_H
#define PATH_H

#include <cstddef>
#include <vector>
#include <utility>

class Path {
public:
    Path();

    void push(int x, int y);
    void pop();
    std::pair<int, int> top() const;
    bool contains(int x, int y) const;
    size_t size() const;
    void clear();
    const std::vector<std::pair<int, int>>& get_all() const;

private:
    std::vector<std::pair<int, int>> stack;
};

#endif // PATH_H
