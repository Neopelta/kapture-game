#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>

#include "drapeau.h"

class unite;

class joueur {
    short unsigned int id;
    static const short unsigned int NUMBER_OF_SCOOTS;
    static const short unsigned int NUMBER_OF_SHOCK_TROOPS;
    static const short unsigned int NUMBER_OF_CANON_FODDER;
    std::vector<unite*> units;
    drapeau flag;
    joueur &initializeUnits();

public:
    joueur();
    ~joueur();
    joueur(short unsigned int id);
    joueur(const joueur &j);
    joueur& operator=(const joueur &j);
    std::vector<unite*>operator*() const;
    bool isFlagStolen() const;
    bool operator<(const joueur &j) const;
};

#endif
