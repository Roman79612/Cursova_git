/* ----------------------------------------------------------------<Header>-
 Name: graph.cc
 Title: Graph edge logic for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-08
 Revised: 2025-05-08
 Description: Contains implementation of helper methods for applying rules
              of the Masyu puzzle using edge graph representation.
 ------------------------------------------------------------------</Header>-*/

#include "../logic_headers/graph.h"

/* ---------------------------------------------------------------------[<]-
 Function: Graph
 Synopsis: Constructor that initializes reference to Field object.
 ---------------------------------------------------------------------[>]-*/
Graph::Graph(const Field& field) : field(field) {}

Graph::Graph(const Graph& other) : field(other.field) {
    std::map<const Cell*, Cell*> cell_mapping;

    for (int row = 0; row < field.get_height(); ++row) {
        for (int col = 0; col < field.get_width(); ++col) {
            const Cell* old_cell = other.field.get_cell_ptr(row, col);
            const Cell* new_cell = field.get_cell_ptr(row, col);
            cell_mapping[old_cell] = const_cast<Cell*>(new_cell);
        }
    }

    for (const auto& [edge, state] : other.edge_matrix) {
        const Cell* old_a = edge.first;
        const Cell* old_b = edge.second;
        Cell* new_a = cell_mapping[old_a];
        Cell* new_b = cell_mapping[old_b];
        edge_matrix[{new_a, new_b}] = state;
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: add_edge
 Synopsis: Adds an edge between two cells and marks as YES.
 ---------------------------------------------------------------------[>]-*/
void Graph::add_edge(Cell &a, Cell &b) {
    if (is_connected(a, b)) return;

    int dx = b.get_x() - a.get_x();
    int dy = b.get_y() - a.get_y();
    Direction dir = DirectionHelper::get_dir_delta(dx, dy);
    Direction opp = DirectionHelper::opposite(dir);

    if ((a.get_forb_dir1() == dir || a.get_forb_dir2() == dir) || (b.get_forb_dir1() == opp || b.get_forb_dir2() == opp)) {
        return;
    }

    a.set_dir_to(dir);
    b.set_dir_from(opp);

    set_edge(a, b, EdgeState::YES);
}

/* ---------------------------------------------------------------------[<]-
 Function: remove_edge
 Synopsis: Removes edge and marks as NO (banned).
 ---------------------------------------------------------------------[>]-*/
void Graph::remove_edge(Cell &a, Cell &b) {
    int dx = b.get_x() - a.get_x();
    int dy = b.get_y() - a.get_y();
    Direction dir = DirectionHelper::get_dir_delta(dx, dy);
    Direction opp = DirectionHelper::opposite(dir);

    if (a.get_forb_dir1() != dir && a.get_forb_dir2() != dir)
        a.set_forbidden_dir(dir);
    if (b.get_forb_dir1() != opp && b.get_forb_dir2() != opp)
        b.set_forbidden_dir(opp);

    set_edge(a, b, EdgeState::NO);
}

/* ---------------------------------------------------------------------[<]-
 Function: are_connected
 Synopsis: Checks if two cells are currently connected.
 ---------------------------------------------------------------------[>]-*/
bool Graph::is_connected(const Cell& a, const Cell& b) {
    auto key = std::make_pair(const_cast<Cell*>(&a), const_cast<Cell*>(&b));
    auto it = edge_matrix.find(key);
    return it != edge_matrix.end() && it->second == EdgeState::YES;
}

/* ---------------------------------------------------------------------[<]-
 Function: get_neighbor
 Synopsis: Returns pointer to neighbor cell in the given direction, or nullptr if none.
 ---------------------------------------------------------------------[>]*/
Cell& Graph::get_neighbor(Cell &a, Direction dir) {
    int ax = a.get_x(), ay = a.get_y();
    int nx = ax + DirectionHelper::get_dx(dir);
    int ny = ay + DirectionHelper::get_dy(dir);

    if (!field.in_bounds(nx, ny)) {
        throw std::out_of_range("Neighbor out of bounds");
    }
    return field.get_cell(nx, ny);
}

/* ---------------------------------------------------------------------[<]-
 Function: set_edge
 Synopsis: Sets the state of an edge between two cells (YES / NO / UNKNOWN).
 ---------------------------------------------------------------------[>]-*/
void Graph::set_edge(Cell& a, Cell& b, EdgeState state) {
    edge_matrix[{&a, &b}] = state;
    edge_matrix[{&b, &a}] = state;
}

/* ---------------------------------------------------------------------[<]-
 Function: get_edge
 Synopsis: Returns the state of the edge between two cells.
 ---------------------------------------------------------------------[>]-*/
EdgeState Graph::get_state(Cell &a, Cell &b) const {
    auto key = std::make_pair(&a, &b);
    auto it = edge_matrix.find(key);
    if (it != edge_matrix.end()) {
        return it->second;
    }
    return EdgeState::UNKNOWN;
}

bool Graph::can_connect(Cell& a, Cell& b) {
    if (is_connected(a, b)) return false;

    int dx = b.get_x() - a.get_x();
    int dy = b.get_y() - a.get_y();
    Direction dir = DirectionHelper::get_dir_delta(dx, dy);
    Direction opp = DirectionHelper::opposite(dir);

    if (a.get_forb_dir1() == dir || a.get_forb_dir2() == dir) return false;
    if (b.get_forb_dir1() == opp || b.get_forb_dir2() == opp) return false;

    int a_conn = (a.get_dir_from() != Direction::NONE) + (a.get_dir_to() != Direction::NONE);
    int b_conn = (b.get_dir_from() != Direction::NONE) + (b.get_dir_to() != Direction::NONE);
    if (a_conn >= 2 || b_conn >= 2) return false;

    return true;
}

std::vector<std::pair<Cell&, Cell&>> Graph::get_all_possible_edges() {
    std::vector<std::pair<Cell&, Cell&>> candidates;

    for (Cell* cell_ptr : field.get_all_cells()) {
        for (Direction dir : DirectionHelper::get_all_dirs()) {
            Cell& cell = *cell_ptr;
            int nx = cell.get_x() + DirectionHelper::get_dx(dir);
            int ny = cell.get_y() + DirectionHelper::get_dy(dir);

            if (!field.in_bounds(nx, ny)) continue;

            Cell& neighbor = field.get_cell(nx, ny);
            if (get_state(cell, neighbor) == EdgeState::UNKNOWN && can_connect(cell, neighbor)) {
                candidates.emplace_back(cell, neighbor);
            }
        }
    }

    return candidates;
}


void Graph::force_edge(Cell& a, Cell& b) {
    add_edge(a, b);
}

void Graph::ban_edge(Cell& a, Cell& b) {
    remove_edge(a, b);
}

bool Graph::is_valid_path() {
    std::set<Cell*> visited;
    int components = 0;

    for (Cell* cell_ptr : field.get_all_cells()) {
        Cell& cell = *cell_ptr;
        int degree = (cell.get_dir_from() != Direction::NONE) + (cell.get_dir_to() != Direction::NONE);
        if (degree == 1) return false;
        if (degree == 2 && visited.find(&cell) == visited.end()) {
            if (++components > 1) return false;
            dfs_visit(cell, visited);
        }
    }

    return components == 1;
}

void Graph::dfs_visit(Cell& cell, std::set<Cell*>& visited) {
    visited.insert(&cell);

    for (Direction dir : DirectionHelper::get_all_dirs()) {
        if (cell.get_dir_to() == dir || cell.get_dir_from() == dir) {
            int nx = cell.get_x() + DirectionHelper::get_dx(dir);
            int ny = cell.get_y() + DirectionHelper::get_dy(dir);

            if (field.in_bounds(nx, ny)) {
                Cell& neighbor = field.get_cell(nx, ny);
                if (is_connected(cell, neighbor) && visited.find(&neighbor) == visited.end()) {
                    dfs_visit(neighbor, visited);
                }
            }
        }
    }
}

std::vector<std::vector<Cell*>> Graph::get_connected_components() {
    std::set<Cell*> visited;
    std::vector<std::vector<Cell*>> components;

    for (Cell* cell_ptr : field.get_all_cells()) {
        Cell& cell = *cell_ptr;
        if (visited.find(&cell) == visited.end()) {
            std::vector<Cell*> comp;
            dfs_collect(cell, visited, comp);
            components.push_back(comp);
        }
    }

    return components;
}

void Graph::dfs_collect(Cell& cell, std::set<Cell*>& visited, std::vector<Cell*>& comp) {
    visited.insert(&cell);
    comp.push_back(&cell);

    for (Direction dir : DirectionHelper::get_all_dirs()) {
        if (cell.get_dir_to() == dir || cell.get_dir_from() == dir) {
            int nx = cell.get_x() + DirectionHelper::get_dx(dir);
            int ny = cell.get_y() + DirectionHelper::get_dy(dir);

            if (field.in_bounds(nx, ny)) {
                Cell& neighbor = field.get_cell(nx, ny);
                if (is_connected(cell, neighbor) && visited.find(&neighbor) == visited.end()) {
                    dfs_collect(neighbor, visited, comp);
                }
            }
        }
    }
}
