#include "../../include/game/cellule.h"

#include <algorithm>
#include <iostream>
#include <ostream>

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

cellule::cellule(const cellule &c): visible(c.visible) {
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
        visible = c.visible;
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

unitObstacle *cellule::operator->() const {
    return entity;
}

bool cellule::isVisible(joueur &p) const {
    for (const auto& [key, value] : visible) {
        if (key == p)
            return value;
    }
    return false;
}

cellule& cellule::operator()(joueur &p) {
    visible[p] = true;
    return *this;
}


cellule &cellule::operator=(unitObstacle *uo) {
    entity = uo->clone();
    return *this;
}

cellule &cellule::operator()(std::list<joueur> &players) {
    for (joueur &p: players)
        visible.insert({p, false});

    return *this;
}

std::map<joueur, bool> cellule::operator!() const {
    return visible;
}



