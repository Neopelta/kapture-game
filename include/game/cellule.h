#ifndef CELLULE_H
#define CELLULE_H
#include <map>
#include <utility>

#include "joueur.h"
#include "../unitObstacle.h"


namespace kpt {
    class cellule {
        std::pair<short unsigned int, short unsigned int> coord;
        unitObstacle *entity;
        std::map<joueur, bool> visible;
    public:
        cellule();
        ~cellule();
        cellule(const cellule &c);
        cellule &operator=(const cellule &c);
        cellule(short unsigned int x, short unsigned int y, unitObstacle *uo = nullptr);
        cellule &operator()(unitObstacle &uo);
        std::pair<short unsigned int, short unsigned int> operator*() const;
        cellule &operator()(joueur &j1, joueur &j2);
    };
}


#endif
