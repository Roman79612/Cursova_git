#pragma once
#include <vector>

using namespace std;

enum class Direction {
    Up, Down, Left, Right
};

struct Position {
    int x, y;
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
};

class Line {
private:
    vector<Position> path;
    Direction currentDir;

public:
    Line(Position start, Direction dir);
    bool move(Position next);
    void undo();
    const vector<Position>& getPath() const;
    Position getCurrent() const;
    Direction getDirection() const;
    void setDirection(Direction dir);
    int getLength() const;
};
