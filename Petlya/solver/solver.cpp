#include "solver.h"
#include <iostream>
#include <sstream>
#include <functional>


Solver::Solver(Field& field, Position start, Direction dir) : field(field), line(start, dir) {}

bool Solver::solve() {
    int width = field.getCols();
    int height = field.getRows();

    if (!field.hasPrivilegedCells()) { return solveDefaultLoop(); }
    if (field.hasOnlyWhiteCells()) {
        if (width * height <= 100) { return solveWhiteCellsRecursive(); } 
        else { return solveWhiteCellsIterative(); }
    }
    if (field.hasOnlyBlackCells()) {
        if (width * height <= 100) { return solveBlackCellsRecursive(); } 
        else { return solveBlackCellsIterative(); }
    }
    if (width * height <= 100) { return solveRecursive(); } 
    else { return solveIterative(); }
}

bool Solver::solveDefaultLoop() {
    cout << "\nRunning default loop (no special cells)...\n";

    // Початкові клітинки не відвідані
    for (int y = 0; y < field.getRows(); ++y) {
        for (int x = 0; x < field.getCols(); ++x) {
            field.getCell(x, y).linePassed = false; // очищаємо статус лінії
        }
    }

    // Рух по краях поля
    function<bool(Position, Direction)> moveEdge = [&](Position current, Direction dir) {
        // Якщо поточна позиція на краю поля, рухаємо лінію по периметру
        if (current.x == 0 || current.x == field.getCols() - 1 || current.y == 0 || current.y == field.getRows() - 1) {
            // Переміщаємо лінію
            line.setDirection(dir);
            if (line.move(current)) {
                // Відзначаємо клітинку як пройдену
                field.getCell(current.x, current.y).linePassed = true;
                return true;
            }
        }
        return false;
    };

    // Рухаємо лінію по краях поля (зліва направо, зверху вниз і т.д.)
    for (int y = 0; y < field.getRows(); ++y) {
        for (int x = 0; x < field.getCols(); ++x) {
            Position current = {x, y};
            moveEdge(current, Direction::Right);
        }
    }

    // Повертаємо успіх, якщо лінія змогла пройти по краях
    return true;
}


bool Solver::solveRecursive() {
    cout << "\nRunning recursive (DFS-based) solver...\n";

    // Лямбда-функція для DFS
    function<bool(Position, Direction)> dfs = [&](Position current, Direction dir) -> bool {
        // Якщо вже були тут у цьому напрямку — скипаємо
        string stateKey = to_string(current.x) + "," + to_string(current.y) + "," + to_string(static_cast<int>(dir));
        if (visitedStates.count(stateKey)) return false;
        visitedStates.insert(stateKey);

        // Якщо вийшли за межі поля або на заборонену клітинку
        if (!field.isInside(current.x, current.y) || !isLegalNextStep(current, dir)) return false;

        // Якщо повернулися у старт і замкнули петлю
        if (line.getPath().size() > 4 && current == line.getStartPosition() && isLoopClosed() && allPrivilegedVisited()) {
            return true;  // Знайшли розв'язок
        }

        // Зберігаємо поточний стан і робимо крок
        line.setDirection(dir);
        line.move(current);
        field.getCell(current.x, current.y).linePassed = true;

        // Список можливих напрямків руху
        vector<Direction> directions = {Direction::Up, Direction::Down, Direction::Left, Direction::Right};
        for (Direction nextDir : directions) {
            // Не йдемо назад у напрямок, з якого прийшли
            if (getOpposite(dir) == nextDir) continue;

            // Рухаємося в новий напрямок
            Position nextPos = moveInDirection(current, nextDir);

            // Застосування правил для білих клітинок
            Cell cell = field.getCell(current.x, current.y);
            if (cell.type == CellType::WhiteCircle) {
                if (!(dir == nextDir)) continue; // Має бути прямий рух
            }
            // Застосування правил для чорних клітинок
            if (cell.type == CellType::BlackCircle) {
                if (!(is90Turn(dir, nextDir) || is270Turn(dir, nextDir))) continue; // Має бути поворот
            }

            // Рекурсивно пробуємо наступний крок
            if (dfs(nextPos, nextDir)) return true;
        }

        // Бектрек: прибираємо з шляху, знімаємо позначку
        line.popLast();
        field.getCell(current.x, current.y).linePassed = false;
        return false;  // Немає шляху, повертаємось назад
    };

    // Запускаємо DFS з початкової позиції
    return dfs(line.getCurrentPosition(), line.getCurrentDirection());
}


bool Solver::solveIterative() {
    cout << "\nRunning iterative (heuristic) solver...\n";
    return true; // тимчасова заглушка
}

void Solver::printResult() const {
    int rows = field.getRows();
    int cols = field.getCols();

    // Створюємо копію поля для відображення результату
    vector<vector<char>> display(rows, vector<char>(cols, ' '));

    // Заповнюємо типи клітинок (білі/чорні)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Cell cell = field.getCell(i, j);
            switch (cell.type) {
                case CellType::BlackCircle: display[i][j] = 'B'; break;
                case CellType::WhiteCircle: display[i][j] = 'W'; break;
                case CellType::Empty: display[i][j] = '.'; break;
            }
        }
    }

    // Накладаємо шлях лінії зірочками
    for (const Position& pos : line.getPath()) {
        if (field.isInside(pos.x, pos.y)) {
            display[pos.x][pos.y] = '*';
        }
    }
    // Виводимо результат
    cout << "\n=== Result ===\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << display[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool Solver::solveWhiteCellsRecursive() {
    cout << "\nSolving for white cells (recursive)...\n";
    // Логіка для рекурсивного вирішення головоломки з тільки білими клітинками
    return true;
}

bool Solver::solveWhiteCellsIterative() {
    cout << "\nSolving for white cells (iterative)...\n";
    // Логіка для ітеративного вирішення головоломки з тільки білими клітинками
    return true;
}

bool Solver::solveBlackCellsRecursive() {
    cout << "\nSolving for black cells (recursive)...\n";
    // Логіка для рекурсивного вирішення головоломки з тільки чорними клітинками
    return true;
}

bool Solver::solveBlackCellsIterative() {
    cout << "\nSolving for black cells (iterative)...\n";
    // Логіка для ітеративного вирішення головоломки з тільки чорними клітинками
    return true;
}

bool Solver::isLoopClosed() const {
    if (line.getPath().empty()) return false;
    Position end = line.getCurrentPosition();
    Position start = line.getStartPosition();
    return manhattanDistance(end, start) == 1;
}

bool Solver::allPrivilegedVisited() const {
    for (int y = 0; y < field.getRows(); ++y) {
        for (int x = 0; x < field.getCols(); ++x) {
            const Cell& cell = field.getCell(x, y);
            if ((cell.type == CellType::WhiteCircle || cell.type == CellType::BlackCircle) && !cell.linePassed) {
                return false;
            }
        }
    }
    return true;
}

bool Solver::isDirectionChangeValid(Position pos, Direction from, Direction to) const {
    if (from == to) return true; // без зміни напрямку завжди валідно

    const Cell& cell = field.getCell(pos.x, pos.y);
    if (cell.type == CellType::WhiteCircle) {
        return false; // на білій — заборонено змінювати напрям
    }
    if (cell.type == CellType::BlackCircle) {
        return is90Turn(from, to) || is270Turn(from, to); // дозволені тільки 90° або 270°
    }

    // на порожній — будь-який поворот дозволено
    return true;
}

bool Solver::checkConnectivity() const {
    const auto& path = line.getPath();
    if (path.empty()) return false;

    unordered_set<int> visited;
    queue<Position> q;

    auto posToKey = [&](Position p) {
        return p.y * field.getCols() + p.x;
    };

    visited.insert(posToKey(path[0]));
    q.push(path[0]);

    auto isInPath = [&](Position p) {
        return std::find(path.begin(), path.end(), p) != path.end();
    };

    while (!q.empty()) {
        Position current = q.front(); q.pop();

        for (Direction dir : {Direction::Up, Direction::Down, Direction::Left, Direction::Right}) {
            Position neighbor = current;
            switch (dir) {
                case Direction::Up:    neighbor.y -= 1; break;
                case Direction::Down:  neighbor.y += 1; break;
                case Direction::Left:  neighbor.x -= 1; break;
                case Direction::Right: neighbor.x += 1; break;
            }

            if (!field.isInside(neighbor.x, neighbor.y)) continue;
            int key = posToKey(neighbor);
            if (visited.count(key)) continue;

            if (isInPath(neighbor)) {
                visited.insert(key);
                q.push(neighbor);
            }
        }
    }

    return visited.size() == path.size();
}

bool Solver::canReturnToStart() const {
    Position current = line.getCurrentPosition();
    Position start = line.getStartPosition();
    return manhattanDistance(current, start) == 1;
}

bool Solver::isPathToAllUnvisitedPrivileged() const {
    vector<Position> targets;
    for (int y = 0; y < field.getRows(); ++y) {
        for (int x = 0; x < field.getCols(); ++x) {
            const Cell& cell = field.getCell(x, y);
            if ((cell.type == CellType::WhiteCircle || cell.type == CellType::BlackCircle) && !cell.linePassed) {
                targets.push_back({x, y});
            }
        }
    }

    if (targets.empty()) return true;

    Position current = line.getCurrentPosition();
    int distance = heuristicDistance(current, targets);
    return distance < 10; //ще не пізно повернутись
}

bool Solver::isLegalNextStep(Position next, Direction dir) const {
    if (!field.isInside(next.x, next.y)) return false;
    const Cell& cell = field.getCell(next.x, next.y);
    if (cell.linePassed) return false;

    Position current = line.getCurrentPosition();
    Direction currentDir = line.getCurrentDirection();
    return isDirectionChangeValid(current, currentDir, dir);
}

void Solver::saveState() {
    history.push(line);
}

void Solver::restoreState() {
    if (!history.empty()) {
        line = history.top();
        history.pop();
    }
}
