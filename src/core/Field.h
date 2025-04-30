#ifndef FIELD_HPP
#define FIELD_HPP

#include "cell.hpp"
#include <vector>

/**
 * @brief Представляє все поле головоломки
 */

class field {
private:
    int width;
    int height;
    std::vector<std::vector<cell>> cells;

public:
    field(int width_value, int height_value);

    cell *get_cell(int x, int y);
    int get_width() const;
    int get_height() const;
};

#endif // FIELD_HPP
