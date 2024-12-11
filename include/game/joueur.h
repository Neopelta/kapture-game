#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>

#include "drapeau.h"

namespace kpt {
    class unite;
    class joueur {
        static short unsigned int index;
        static const short unsigned int NUMBER_OF_SCOOTS;
        static const short unsigned int NUMBER_OF_SHOCK_TROOPS;
        static const short unsigned int NUMBER_OF_CANON_FODDER;
        short unsigned int id;
        std::vector<unite*> units;
        drapeau flag;

        joueur &initializeUnits();
    public:
        ~joueur();
        joueur();
        joueur(const joueur &j);
        joueur& operator=(const joueur &j);
        std::vector<unite*> operator*() const;
        drapeau operator!() const;
        bool operator==(const joueur &p) const;
        bool operator<(const joueur &p) const {
            return id < p.id;
        }
        short unsigned int operator()() const {
            return id;
        }
    };
}

#endif
