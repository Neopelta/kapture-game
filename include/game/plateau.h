#ifndef PLATEAU_H
#define PLATEAU_H

#include "cellule.h"

namespace kpt {
    template<short unsigned int row, short unsigned int col>
    class plateau {
        std::vector<cellule> cells;
    public:
        plateau<row,col>() {
            for (short unsigned int i = 0; i < row * col; i++)
                cells.emplace_back(i / col, i % col);
        }

        cellule &operator[](short unsigned int index) {
            return cells.at(index);
        }

        std::vector<cellule> operator*() const {
            return cells;
        }

        plateau<row, col> &operator()(std::list<joueur> &players) {
            for (cellule &c : cells)
                c(players);

            return *this;
        }
    };
}

#endif
