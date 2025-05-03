/* ----------------------------------------------------------------<Header>-
 Name: rules.h
 Title: Rules class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Header file for rule validation logic in Masyu puzzle.
 ------------------------------------------------------------------</Header>-*/

#ifndef RULES_H
#define RULES_H

#include "../core_headers/field.h"
#include "../logic_headers/graph.h"

class Rules {
public:
    static bool check_white_dot(const Field& field, int x, int y, const Graph& graph);
    static bool check_black_dot(const Field& field, int x, int y, const Graph& graph);
    static bool validate_all_dots(const Field& field, const Graph& graph);
    static bool validate_cycle(const Field& field, const Graph& graph);
};

#endif // RULES_H
