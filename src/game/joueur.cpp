#include "../../include/game/joueur.h"

#include <algorithm>
#include <iostream>
#include <ostream>

#include "../../include/units/chairACanon.h"
#include "../../include/units/eclaireur.h"
#include "../../include/units/troupeDeChoc.h"

using namespace kpt;
const short unsigned int joueur::NUMBER_OF_SCOOTS = 2;
const short unsigned int joueur::NUMBER_OF_SHOCK_TROOPS = 4;
const short unsigned int joueur::NUMBER_OF_CANON_FODDER = 6;

short unsigned int joueur::index = 0;

joueur::~joueur() {
    std::for_each(units.begin(), units.end(), [](unite* u) {
        delete u;
    });
    units.clear();
}

joueur::joueur() {
    id = ++index;
    this->initializeUnits();
}

joueur::joueur(const joueur &j) {
    std::for_each(units.begin(), units.end(), [](unite* u) {
        delete u;
    });
    units.clear();

    std::for_each(j.units.begin(), j.units.end(), [this](unite* u) {
        units.push_back(u->clone());
    });
    flag = j.flag;
    id = j.id;
}

joueur & joueur::operator=(const joueur &j) {
    if (this != &j) {
        std::for_each(units.begin(), units.end(), [](unite* u) {
            delete u;
        });
        units.clear();

        std::for_each(j.units.begin(), j.units.end(), [this](unite* u) {
            units.push_back(u->clone());
        });

        flag = j.flag;
        id = j.id;
    }
    return *this;
}

joueur &joueur::initializeUnits() {
    for (short unsigned int i = 0; i < NUMBER_OF_SCOOTS; ++i)
        units.push_back(new eclaireur);

    for (short unsigned int i = 0; i < NUMBER_OF_SHOCK_TROOPS; ++i)
        units.push_back(new troupeDeChoc);

    for (short unsigned int i = 0; i < NUMBER_OF_CANON_FODDER; ++i)
        units.push_back(new chairACanon);

    return *this;
}

const std::vector<unite*>& joueur::operator*() const {
    return units;
}

const drapeau& joueur::operator!() const {
    return flag;
}

bool joueur::operator==(const joueur &p) const {
    return this->id == p.id;
}

bool joueur::operator<(const joueur &p) const {
    return id < p.id;
}

short unsigned int joueur::operator()() const {
    return id;
}

joueur & joueur::operator()(const drapeau &f) {
    flag = f;
    return *this;
}

bool joueur::operator()(const unite *u) {
    bool isIncluded = false;
    std::for_each(units.begin(), units.end(), [&](const unite *unit) {
        isIncluded |= (*u == unit);
    });
    return isIncluded;
}

joueur &joueur::resetUnits() {
    units.clear();
    return *this;
}

joueur &joueur::insertUnit(unite *u) {
    units.push_back(u);
    return *this;
}

