#ifndef KAPTUREGAME_H
#define KAPTUREGAME_H

#include <complex>
#include <list>

#include "plateau.h"
#include <stdexcept>

#include "../obstacles/foret.h"
#include "../obstacles/riviere.h"
#include "../units/eclaireur.h"

namespace kpt {
    template<short unsigned int row, short unsigned int col>
    class kaptureGame {
        static kaptureGame* instance;
        short unsigned int currentNbTurns;
        plateau<row, col> board;
        std::list<joueur> players;

        kaptureGame<row, col>(joueur &p1, joueur &p2) : currentNbTurns(0), board() {
            players.push_back(p1);
            players.push_back(p2);
        }

    public:
        // Only one instance, this why we don't have the canonical form class
        static kaptureGame<row, col>* getInstance(joueur &p1, joueur &p2) {
            if (instance == nullptr)
                instance = new kaptureGame<row, col>(p1, p2);
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

        plateau<row, col> operator*() const {
            return board;
        }
    };

    template<short unsigned int row, short unsigned int col>
    kaptureGame<row, col>* kaptureGame<row, col>::instance = nullptr;
}
#endif
