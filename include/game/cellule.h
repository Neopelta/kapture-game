#ifndef CELLULE_H
#define CELLULE_H

#include <list>
#include <map>


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
        unitObstacle *operator->() const;
        bool isVisible(joueur &p) const;
        cellule &operator()(joueur &p);
        cellule& operator=(unitObstacle *uo);
        cellule &operator()(std::vector<joueur> &players);
        std::map<joueur, bool> operator!() const;
    };
}


#endif
