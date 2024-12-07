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
                cells.push_back(cellule());
        }

        cellule &operator[](const std::pair<int,int> &pos) {
            return cells.at(pos.first * pos.first + pos.second);
        }
    };
}

#endif
