#ifndef CELL_HPP
#define CELL_HPP

#include <set>
#include "direction.hpp"

/**
 * @brief Тип клітинки
 */
enum class CellType {
    EMPTY,
    WALL,
    WHITE_DOT,
    BLACK_DOT
};

/**
 * @brief Клітинка поля
 */
class Cell {
public:
    Cell(int x, int y, CellType type = CellType::EMPTY);

    /**
     * @brief Отримати координати
     */
    int get_x() const;
    int get_y() const;

    /**
     * @brief Отримати / змінити тип клітинки
     */
    CellType get_type() const;
    void set_type(CellType new_type);

    /**
     * @brief Позначити, що клітинка пройдена
     */
    void mark_visited();
    bool is_visited() const;

    /**
     * @brief Додати / отримати доступні напрямки
     */
    void add_direction(Direction dir);
    const std::set<Direction> &get_directions() const;

private:
    int x_;
    int y_;
    CellType type_;
    bool visited_;
    std::set<Direction> directions_; // можливі напрямки для "підсвітки"
};

#endif // CELL_HPP
