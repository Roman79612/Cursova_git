#ifndef LINE_HPP
#define LINE_HPP

#include <vector>
#include <utility>
#include <unordered_set>
#include "../utils/hash.hpp"

/**
 * @brief Клас для збереження побудованого шляху
 */
class Line {
public:
    Line();

    void add_point(int x, int y);
    void remove_last_point();
    const std::vector<std::pair<int, int>> &get_path() const;
    bool contains(int x, int y) const;
    void clear();
    int size() const;

private:
    std::vector<std::pair<int, int>> path_;
    std::unordered_set<std::pair<int, int>, pair_hash> visited_;
};

#endif // LINE_HPP
