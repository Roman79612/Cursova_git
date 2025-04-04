#pragma once
#include "field.h"
#include "line.h"
#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

class Solver {
private:
    Field& field;
    Line line;
    unordered_set<string> visitedStates;
    bool solveRecursive();
    bool solveIterative();
    bool solveDefaultLoop();
public:
    Solver(Field& field, Position start, Direction dir);
    bool solve();
    void printResult() const;
};
