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

cellule::cellule(short unsigned int x, short unsigned int y, unitObstacle *uo): visible() {
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
    std::pair<std::multimap<bool, joueur>::const_iterator, std::multimap<bool, joueur>::const_iterator>
        range = visible.equal_range(true);

    std::multimap<bool, joueur>::const_iterator it = std::find_if(
        range.first, range.second, [&p](const std::pair<const bool, joueur> &pair) {
            return pair.second == p;
        });

    return it != range.second;
}

cellule& cellule::operator()(joueur &p) {
    std::multimap<bool, joueur>::iterator it = visible.find(false);
    if (it != visible.end() && it->second == p)
        visible.erase(it);

    visible.insert({true, p});
    return *this;
}


cellule &cellule::operator=(unitObstacle *uo) {
    entity = uo->clone();
    return *this;
}

cellule &cellule::operator()(std::list<joueur> &players) {
    for (joueur &p: players)
        visible.insert({false, p});

    return *this;
}


