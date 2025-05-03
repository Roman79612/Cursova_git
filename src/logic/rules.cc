/* ----------------------------------------------------------------<Header>-
 Name: rules.cc
 Title: Rules class implementation
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-04-30
 Revised: 2025-05-03
 Description: Implements logic for Masyu rule validation.
 ------------------------------------------------------------------</Header>-*/

#include "../logic_headers/rules.h"

/* ---------------------------------------------------------------------[<]-
 Function: Rules::check_white_dot
 Synopsis: Validates the rule for a white dot at the given position.
 ---------------------------------------------------------------------[>]-*/
bool Rules::check_white_dot(const Field& field, int x, int y, const Graph& graph) {
    // Для білої точки шлях має проходити ПРЯМО через неї, і поворот має бути ДО або ПІСЛЯ
    std::vector<std::pair<int, int>> neighbors = field.get_neighbors(x, y);
    std::vector<std::pair<int, int>> connected;

    for (const auto& [nx, ny] : neighbors) {
        if (graph.has_edge(x, y, nx, ny)) {
            connected.emplace_back(nx, ny);
        }
    }

    if (connected.size() != 2)
        return false;

    // Дві суміжні клітини повинні бути в протилежних напрямках (по горизонталі або вертикалі)
    int dx1 = connected[0].first - x;
    int dy1 = connected[0].second - y;
    int dx2 = connected[1].first - x;
    int dy2 = connected[1].second - y;

    bool straight = (dx1 == -dx2 && dy1 == -dy2);
    return straight;
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::check_black_dot
 Synopsis: Validates the rule for a black dot at the given position.
 ---------------------------------------------------------------------[>]-*/
bool Rules::check_black_dot(const Field& field, int x, int y, const Graph& graph) {
    // Для чорної точки повинен бути поворот в цій точці
    std::vector<std::pair<int, int>> neighbors = field.get_neighbors(x, y);
    std::vector<std::pair<int, int>> connected;

    for (const auto& [nx, ny] : neighbors) {
        if (graph.has_edge(x, y, nx, ny)) {
            connected.emplace_back(nx, ny);
        }
    }

    if (connected.size() != 2)
        return false;

    int dx1 = connected[0].first - x;
    int dy1 = connected[0].second - y;
    int dx2 = connected[1].first - x;
    int dy2 = connected[1].second - y;

    bool is_turn = !(dx1 == -dx2 && dy1 == -dy2);
    return is_turn;
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::validate_all_dots
 Synopsis: Checks all white and black dots on the field for validity.
 ---------------------------------------------------------------------[>]-*/
bool Rules::validate_all_dots(const Field& field, const Graph& graph) {
    for (int y = 0; y < field.get_height(); ++y) {
        for (int x = 0; x < field.get_width(); ++x) {
            CellType type = field.get_cell(x, y).get_type();
            if (type == CellType::WHITE_DOT && !check_white_dot(field, x, y, graph))
                return false;
            if (type == CellType::BLACK_DOT && !check_black_dot(field, x, y, graph))
                return false;
        }
    }
    return true;
}

/* ---------------------------------------------------------------------[<]-
 Function: Rules::validate_cycle
 Synopsis: Validates the entire solution according to the game rules:
           1. The path must form a single cycle.
           2. White dots must lie on straight segments.
           3. Black dots must lie on corner turns.
 ---------------------------------------------------------------------[>]-*/
bool Rules::validate_cycle(const Field& field, const Graph& graph) {
    if (!graph.is_single_cycle()) {
        return false;
    }

    int width = field.get_width();
    int height = field.get_height();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const Cell& cell = field.get_cell(x, y);
            CellType type = cell.get_type();

            if (type == CellType::WHITE_DOT || type == CellType::BLACK_DOT) {
                std::vector<Direction> connected_dirs;

                for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}) {
                    int nx = x + DirectionHelper::get_dx(dir);
                    int ny = y + DirectionHelper::get_dy(dir);

                    if (nx < 0 || ny < 0 || nx >= width || ny >= height) {
                        continue;
                    }

                    if (graph.has_edge(x, y, nx, ny)) {
                        connected_dirs.push_back(dir);
                    }
                }

                // Клітинка повинна мати рівно два з'єднання
                if (connected_dirs.size() != 2) {
                    return false;
                }

                Direction dir1 = connected_dirs[0];
                Direction dir2 = connected_dirs[1];

                if (type == CellType::WHITE_DOT) {
                    // Має бути прямий сегмент
                    bool straight = (dir1 == Direction::UP && dir2 == Direction::DOWN) ||
                                    (dir1 == Direction::DOWN && dir2 == Direction::UP) ||
                                    (dir1 == Direction::LEFT && dir2 == Direction::RIGHT) ||
                                    (dir1 == Direction::RIGHT && dir2 == Direction::LEFT);
                    if (!straight) {
                        return false;
                    }
                } else if (type == CellType::BLACK_DOT) {
                    // Має бути поворот
                    bool corner = (dir1 == Direction::UP || dir1 == Direction::DOWN) && (dir2 == Direction::LEFT || dir2 == Direction::RIGHT);
                    corner |= (dir2 == Direction::UP || dir2 == Direction::DOWN) && (dir1 == Direction::LEFT || dir1 == Direction::RIGHT);
                    if (!corner) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}
