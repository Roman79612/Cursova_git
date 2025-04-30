#ifndef CELL_HPP
#define CELL_HPP

/**
 * @brief Представляє одну клітинку на полі
 * 
 * Містить координати, тип клітинки (звичайна, біла, чорна), статус (відвідана тощо)
 */

enum cell_type {
    CELL_NORMAL,
    CELL_WHITE,
    CELL_BLACK
};

struct cell {
    int x;
    int y;
    cell_type type;
    bool visited;

    cell(int x_value, int y_value, cell_type cell_kind);

    void mark_visited();
    void reset();
};

#endif // CELL_HPP
