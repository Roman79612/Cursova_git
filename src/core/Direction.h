#ifndef DIRECTION_HPP
#define DIRECTION_HPP

/**
 * @brief Напрямки руху та повороту
 */

enum direction {
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT,
    DIR_UP
};

/**
 * @brief Отримати протилежний напрям
 * 
 * @param dir Вхідний напрям
 * @return direction Протилежний напрям
 */
direction reverse_direction(direction dir);

/**
 * @brief Повернути напрям на 90/180/270 градусів вправо
 * 
 * @param dir Вхідний напрям
 * @param angle Кут повороту (тільки 90, 180, 270)
 * @return direction Новий напрям
 */
direction rotate_direction(direction dir, int angle);

#endif // DIRECTION_HPP
