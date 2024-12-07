#include "../../include/game/cellule.h"

#include "../../include/obstacles/terrainNu.h"

using namespace kpt;

cellule::cellule() {
    coord.first = 0;
    coord.second = 0;
    entity = new terrainNu;
}

cellule::~cellule() {
    delete entity;
}

cellule::cellule(const cellule &c) {
    coord.first = c.coord.first;
    coord.second = c.coord.second;
    entity = c.entity ? c.entity->clone() : nullptr;
}

cellule &cellule::operator=(const cellule &c) {
    if (this != &c) {
        coord.first = c.coord.first;
        coord.second = c.coord.second;
        delete entity;
        entity = c.entity ? c.entity->clone() : nullptr;
    }
    return *this;
}

cellule::cellule(short unsigned int x, short unsigned int y, unitObstacle *uo) {
    coord.first = x;
    coord.second = y;
    entity = uo ? uo->clone() : new terrainNu;
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

