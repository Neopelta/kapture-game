#include "../../include/game/cellule.h"

using namespace kpt;
cellule::cellule() {
    coord.first = 0;
    coord.second = 0;
    entity = nullptr;
}

cellule::~cellule() = default; // Not need to free some resources because the unit will be initialized before

cellule::cellule(const cellule &c) {
    coord.first = c.coord.first;
    coord.second = c.coord.second;
    entity = c.entity;
}

cellule &cellule::operator=(const cellule &c) {
    if (this != &c) {
        coord.first = c.coord.first;
        coord.second = c.coord.second;
        entity = c.entity;
    }
    return *this;
}

cellule::cellule(short unsigned int x, short unsigned int y) {
    coord.first = x;
    coord.second = y;
    entity = nullptr;
}

cellule &cellule::operator()(unitObstacle &uo) {
    entity = &uo;
    return *this;
}

std::pair<short unsigned int, short unsigned int> cellule::operator*() const {
    return coord;
}

cellule &cellule::operator()(joueur &j1,  joueur &j2) {
    visible.insert({j1, false});
    visible.insert({j2, false});
    return *this;
}

