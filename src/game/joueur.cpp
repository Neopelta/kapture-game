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
    // On ne détruit plus les unités car elles appartiennent au plateau
    units.clear();
}

joueur::joueur() {
    id = ++index;
    // On n'initialise plus les unités ici car elles seront ajoutées par insertUnit
}

joueur::joueur(const joueur &j) {
    units = j.units;  // Copie simple des pointeurs
    flag = j.flag;
    id = j.id;
}

joueur & joueur::operator=(const joueur &j) {
    if (this != &j) {
        units = j.units;  // Copie simple des pointeurs
        flag = j.flag;
        id = j.id;
    }
    return *this;
}

joueur &joueur::initializeUnits() {
    return *this;
}

std::vector<unite*> joueur::operator*() const {
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
        isIncluded |= (u == unit);  // Comparaison des pointeurs au lieu du contenu
    });
    return isIncluded;
}

joueur &joueur::resetUnits() {
    // On ne détruit plus les unités, on vide simplement le vecteur
    units.clear();
    return *this;
}

joueur &joueur::insertUnit(unite* u) {
    // On stocke directement le pointeur sans faire de clone
    units.push_back(u);
    return *this;
}