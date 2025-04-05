#pragma once
#include "field.h"
#include "line.h"
#include "utils.h"
#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

class Solver {
private:
    Field& field;
    Line line;
    unordered_set<string> visitedStates;public:
    Solver(Field& field, Position start, Direction dir);
    bool solve();
    void printResult() const;
    bool solveRecursive();
    bool solveIterative();
    bool solveDefaultLoop();
    bool solveWhiteCellsRecursive();
    bool solveWhiteCellsIterative();
    bool solveBlackCellsRecursive();
    bool solveBlackCellsIterative();
};
