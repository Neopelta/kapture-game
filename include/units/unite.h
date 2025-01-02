#ifndef UNITE_H
#define UNITE_H

#include <iostream>
#include <ostream>

#include "../unitObstacle.h"

namespace kpt {
    class drapeau;
    class eclaireur;
    class chairACanon;
    class troupeDeChoc;

    class unite: public unitObstacle {
        drapeau *flag;
    protected:
        short unsigned int maximalMove;
        short unsigned int initialPosX;
        short unsigned int initialPosY;
        short unsigned int currentPosX;
        short unsigned int currentPosY;
        virtual bool canTakeFlag() = 0;
    public:
        unite();
        ~unite() override = default;

        unite(const unite &other);
        unite &operator=(const unite &other);

        // Nouvelles méthodes pour la gestion des déplacements
        short unsigned int getMaximalMove() const { return maximalMove; }
        short unsigned int getCurrentPosX() const { return currentPosX; }
        short unsigned int getCurrentPosY() const { return currentPosY; }

        void setPosition(short unsigned int x, short unsigned int y) {
            currentPosX = x;
            currentPosY = y;

            std::cout << "Nouvelle position : " << x << "," << y << std::endl;
        }

        void resetPosition() {
            currentPosX = initialPosX;
            currentPosY = initialPosY;
        }

        virtual unite& fight(unite &u) = 0;
        virtual unite& fightWithScoot(eclaireur &s) = 0;
        virtual unite& fightWithCannonFodder(chairACanon &cf) = 0;
        virtual unite& fightWithShockTroop(troupeDeChoc &st) = 0;
        unite& takeFlag(drapeau &d);
        unite* clone() const override = 0;
        drapeau* operator*() const;
        unite& operator()();
        std::string asciiArtPrint() override = 0;
    };
}

#endif