#ifndef KAPTUREGAME_H
#define KAPTUREGAME_H

#include "plateau.h"
#include <stdexcept>

namespace kpt {
    template<short unsigned int row, short unsigned int col>
    class kaptureGame {
        static kaptureGame* instance;
        short unsigned int currentNbTurns;
        plateau<row, col> board;
        std::pair<joueur, joueur> players;

        kaptureGame<row, col>() : currentNbTurns(0), board(), players() {}

    public:
        // Only one instance, this why we don't have the canonical form class
        static kaptureGame<row, col>* getInstance() {
            if (instance == nullptr)
                instance = new kaptureGame<row, col>();
            return instance;
        }

        kaptureGame<row, col>& operator++() {
            ++currentNbTurns;
            return *this;
        }

        kaptureGame<row, col>& saveGame(const std::string &filename) {
            throw std::invalid_argument("kaptureGame::saveGame()");
        }

        static kaptureGame<row, col> loadGame(const std::string &filename) {
            throw std::invalid_argument("kaptureGame::loadGame()");
        }
    };

    template<short unsigned int row, short unsigned int col>
    kaptureGame<row, col>* kaptureGame<row, col>::instance = nullptr;
}
#endif
