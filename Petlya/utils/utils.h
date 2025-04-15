#pragma once
#include "line.h"

// Напрямки
Direction getOpposite(Direction dir);
Position moveInDirection(Position pos, Direction dir);

// Повороти
bool is90Turn(Direction from, Direction to);
bool is270Turn(Direction from, Direction to);
bool is180Turn(Direction from, Direction to);

// Евклідова та евристична відстань
int manhattanDistance(Position a, Position b);
int heuristicDistance(Position from, const std::vector<Position>& targets);
