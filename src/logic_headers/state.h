/* ----------------------------------------------------------------<Header>-
 Name: state.h
 Title: State class definition
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-03
 Revised: 2025-05-03
 Description: Header file for representing a single state in the pathfinding process.
 ------------------------------------------------------------------</Header>-*/

#ifndef STATE_H
#define STATE_H

#include <vector>
#include <utility>
#include "../core_headers/field.h" // щоб мати доступ до Field

class State {
public:
    // Конструктор: приймає посилання на поле
    explicit State(const Field& field);

    // Гетери координат
    int get_x() const;
    int get_y() const;

    // Гетер шляху
    const std::vector<std::pair<int, int>>& get_path() const;

    // Додати точку до шляху
    void add_to_path(int x, int y);

    // Чи вже відвідано координати
    bool is_visited(int x, int y) const;

private:
    int x;
    int y;
    std::vector<std::pair<int, int>> path;
    const Field& field; // поле, з яким пов'язаний стан
};

#endif // STATE_H
