#ifndef DIRECTION_HPP
#define DIRECTION_HPP

/**
 * @brief Перелік напрямків руху.
 */
enum class Direction {
    RIGHT,
    DOWN,
    LEFT,
    UP
};

/**
 * @brief Отримати зсув по X для заданого напрямку.
 * 
 * @param dir Напрямок
 * @return int Зміщення по осі X
 */
int delta_x(Direction dir);

/**
 * @brief Отримати зсув по Y для заданого напрямку.
 * 
 * @param dir Напрямок
 * @return int Зміщення по осі Y
 */
int delta_y(Direction dir);

/**
 * @brief Отримати новий напрямок після повороту на 90° вправо.
 * 
 * @param dir Початковий напрямок
 * @return Direction Новий напрямок
 */
Direction rotate_right(Direction dir);

/**
 * @brief Отримати новий напрямок після повороту на 90° вліво.
 */
Direction rotate_left(Direction dir);

/**
 * @brief Отримати напрямок, протилежний до заданого.
 */
Direction opposite(Direction dir);

/**
 * @brief Отримати напрямок після повороту на задану кількість градусів (90, 180, 270).
 * 
 * @param dir Початковий напрямок
 * @param degrees Кількість градусів
 * @return Direction Новий напрямок
 */
Direction rotate(Direction dir, int degrees);

#endif // DIRECTION_HPP
