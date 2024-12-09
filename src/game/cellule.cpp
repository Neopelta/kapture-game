#include "../../include/game/cellule.h"

#include <iostream>
#include <ostream>

#include "../../include/obstacles/terrainNu.h"

using namespace kpt;

cellule::cellule() {
    coord.first = 0;
    coord.second = 0;
    entity = new terrainNu;
    visible = {{1, false}, {2, false}};
}

cellule::~cellule() {
    delete entity;
}

cellule::cellule(const cellule &c) {
    coord.first = c.coord.first;
    coord.second = c.coord.second;
    entity = c.entity ? c.entity->clone() : nullptr;
    visible = c.visible;
}

cellule &cellule::operator=(const cellule &c) {
    if (this != &c) {
        coord.first = c.coord.first;
        coord.second = c.coord.second;
        delete entity;
        entity = c.entity ? c.entity->clone() : nullptr;
        visible = c.visible;
    }
    return *this;
}

cellule::cellule(short unsigned int x, short unsigned int y, unitObstacle *uo) {
    coord.first = x;
    coord.second = y;
    entity = uo ? uo->clone() : new terrainNu;
    visible = {{1, false}, {2, false}};
}

cellule &cellule::operator()(unitObstacle &uo) {
    entity = &uo;
    return *this;
}

std::pair<short unsigned int, short unsigned int> cellule::operator*() const {
    return coord;
}

unitObstacle *cellule::operator->() const {
    return entity;
}

bool cellule::isVisible(short unsigned int playerId) const {
    for (const std::pair<short unsigned int, bool> v : visible) {
        if (v.first == playerId)
            return v.second;
    }
    return false;
}

cellule& cellule::operator()(short unsigned int playerId) {
    visible[playerId] = true;
    return *this;
}



