/* ----------------------------------------------------------------<Header>-
 Name: graph.cc
 Title: Graph edge logic for Masyu puzzle
 Group: TV-42
 Student: Kriuchkov R. Y.
 Written: 2025-05-07
 Revised: 2025-05-14
 Description: Contains implementation of helper methods for applying rules of the Masyu puzzle using edge graph representation.
 ------------------------------------------------------------------</Header>-*/

#include "../logic_headers/graph.h"

/* ---------------------------------------------------------------------[<]-
 Function: Graph
 Synopsis: Constructor that initializes reference to Field object.
 ---------------------------------------------------------------------[>]-*/
Graph::Graph(Field& field) : field(field) {}

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