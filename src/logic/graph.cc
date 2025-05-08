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
Graph::Graph(Field &field) : field(field) {
    initialize_neighbors();
}

/* ---------------------------------------------------------------------[<]-
 Function: initialize_neighbors
 Synopsis: Ініціалізує всі сусіди для кожної клітинки на полі.
 ---------------------------------------------------------------------[>]-*/
void Graph::initialize_neighbors() {
    for (int y = 0; y < field.get_height(); ++y) {
        for (int x = 0; x < field.get_width(); ++x) {
            Cell* cell = field.get_cell_ptr(x, y);
            if (!cell) continue;

            std::vector<Cell*> neighbors = field.get_neighbors(*cell);
            for (Cell* neighbor : neighbors) {
                if (neighbor) {
                    adjacency[cell].insert(neighbor);
                }
            }
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 Function: get_edge
 Synopsis: Returns the state of the edge between two cells.
 ---------------------------------------------------------------------[>]-*/
EdgeState Graph::get_edge(Cell &a, Cell &b) const {
    auto key = std::make_pair(&a, &b);
    auto it = edge_matrix.find(key);
    if (it != edge_matrix.end()) {
        return it->second;
    }
    return EdgeState::UNKNOWN;
}

/* ---------------------------------------------------------------------[<]-
 Function: get_neighbor
 Synopsis: Returns pointer to neighbor cell in the given direction, or nullptr if none.
 ---------------------------------------------------------------------[>]*/
Cell& Graph::get_neighbor(Cell& cell, Direction dir) const {
    std::vector<Cell*> neighbors = field.get_neighbors(cell);

    for (Cell* neighbor : neighbors) {
        if (!neighbor) continue;

        int dx = neighbor->get_x() - cell.get_x();
        int dy = neighbor->get_y() - cell.get_y();

        if (DirectionHelper::get_dir_delta(dx, dy) == dir) {
            return *neighbor;
        }
    }

    throw std::runtime_error("Neighbor in specified direction not found.");
}

/* ---------------------------------------------------------------------[<]-
 Function: are_connected
 Synopsis: Checks if two cells are currently connected.
 ---------------------------------------------------------------------[>]-*/
bool Graph::are_connected(const Cell &a, const Cell &b) {
    auto it = adjacency.find(const_cast<Cell *>(&a));
    if (it != adjacency.end()) {
        return it->second.count(const_cast<Cell *>(&b)) > 0;
    }
    return false;
}

/* ---------------------------------------------------------------------[<]-
 Function: add_edge
 Synopsis: Adds an edge between two cells and marks as YES.
 ---------------------------------------------------------------------[>]-*/
void Graph::add_edge(Cell &a, Cell &b) {
    int dx = b.get_x() - a.get_x();
    int dy = b.get_y() - a.get_y();
    Direction dir = DirectionHelper::get_dir_delta(dx, dy);
    Direction opp = DirectionHelper::opposite(dir);

    if ((dir != a.get_forb_dir1()) && (opp != a.get_forb_dir2())) {
        a.set_dir_to(dir);
        b.set_dir_from(opp);

        edge_matrix[{&a, &b}] = EdgeState::YES;
        edge_matrix[{&b, &a}] = EdgeState::YES;
    }   
}


/* ---------------------------------------------------------------------[<]-
 Function: remove_edge
 Synopsis: Removes edge and marks as NO (banned).
 ---------------------------------------------------------------------[>]-*/
void Graph::remove_edge(Cell &a, Cell &b) {
    edge_matrix[{&a, &b}] = EdgeState::NO;
    edge_matrix[{&b, &a}] = EdgeState::NO;

    int dx = b.get_x() - a.get_x();
    int dy = b.get_y() - a.get_y();
    Direction dir = DirectionHelper::get_dir_delta(dx, dy);
    Direction opp = DirectionHelper::opposite(dir);
    
    a.set_forbidden_dir(dir);
    b.set_forbidden_dir(opp);
}

/* ---------------------------------------------------------------------[<]-
 Function: ban_edge
 Synopsis: Forbids (removes) edge between two adjacent cells.
 ---------------------------------------------------------------------[>]-*/
void Graph::ban_edge(Cell &a, Cell &b) {
    EdgeState state = get_edge(a, b);
    if (state == EdgeState::YES) {
        remove_edge(a, b);
        return;
    } else if (state == EdgeState::NO) {
        remove_edge(a, b);
        return;
    } else {
        remove_edge(a, b);
        return;
    }
}

