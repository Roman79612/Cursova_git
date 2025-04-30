#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include "cell.hpp"

/**
 * @brief Клас, що представляє все ігрове поле
 */
class Field {
public:
    Field(int width, int height);

    /**
     * @brief Отримати ширину і висоту
     */
    int get_width() const;
    int get_height() const;

    /**
     * @brief Перевірити, чи координати в межах поля
     */
    bool is_valid(int x, int y) const;

    /**
     * @brief Отримати клітинку за координатами
     */
    Cell &get_cell(int x, int y);
    const Cell &get_cell(int x, int y) const;

    /**
     * @brief Позначити напрямки в кожній клітинці
     */
    void update_directions();

private:
    int width_;
    int height_;
    std::vector<std::vector<Cell>> cells_;

    void update_directions_for_cell(int x, int y);
};

#endif // FIELD_HPP
