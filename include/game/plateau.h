#ifndef PLATEAU_H
#define PLATEAU_H

#include <algorithm>

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

        template<short unsigned int X, short unsigned int Y>
        friend std::ostream &operator<<(std::ostream &os, const plateau<X, Y> &plateau);
    };

    template<short unsigned int X, short unsigned int Y>
    std::ostream &operator<<(std::ostream &os, const plateau<X, Y> &board) {
        const short unsigned int NUMBERS_OF_PLAYERS = 2;

        for (int playerId = 1; playerId <= NUMBERS_OF_PLAYERS; ++playerId) {
            os << "Affichage du plateau pour le joueur " << playerId << std::endl;
            short unsigned int ind = 1;

            std::for_each(board.cells.begin(), board.cells.end(),[&ind, &os, &playerId](const cellule &cell) {
                if (cell.isVisible(playerId))
                    os << cell->asciiArtPrint() << " ";
                else
                    os << unitObstacle::asciiArtPrintNotVisible() << " ";
                if (ind % Y == 0)
                    os << std::endl;
                ++ind;
            });

            os << std::endl;
        }
        return os;
    }
}

#endif
