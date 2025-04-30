#ifndef HASH_HPP
#define HASH_HPP

#include <utility>

/**
 * @brief Хеш-функція для std::pair<int, int>
 */
struct pair_hash {
    size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

#endif // HASH_HPP
