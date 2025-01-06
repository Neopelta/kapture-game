#ifndef PLATEAU_H
#define PLATEAU_H

#include "cellule.h"

namespace kpt {
    template<short unsigned int row, short unsigned int col>
    class plateau {
        std::vector<cellule*> cells;
    public:
        plateau<row,col>() {
            for (short unsigned int i = 0; i < row * col; i++)
                cells.emplace_back(new cellule(i / col, i % col));
        }

        cellule *operator[](short unsigned int index) const {
            if (index >= row * col) {
                throw std::out_of_range("Coordonnées hors limites du plateau");
            }

            return cells.at(index);
        }

        static bool isValidPosition(short unsigned int x, short unsigned int y) {
            return x < row && y < col;
        }

        std::vector<cellule*> operator*() const {
            return cells;
        }

        plateau<row, col> &operator()(std::vector<joueur> &players) {
            for (cellule *c : cells)
                c->operator()(players);

            return *this;
        }
    };
}

#endif
