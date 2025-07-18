#ifndef UNITE_H
#define UNITE_H

#include "../unitObstacle.h"

namespace kpt {
    class drapeau;
    class eclaireur;
    class chairACanon;
    class troupeDeChoc;

    enum unitInteraction {
        DRAW,
        WON,
        LOST,
    };

    class unite: public unitObstacle {
    protected:
        short unsigned int maximalMove;
        short unsigned int currentPosX;
        short unsigned int currentPosY;
        drapeau* flag;
        virtual bool canTakeFlag() = 0;
        virtual unite* clone() const = 0;
    public:
        unite();
        ~unite() override = default;

        unite(const unite &other);
        unite &operator=(const unite &other);

        short unsigned int getMaximalMove() const { return maximalMove; }
        short unsigned int getCurrentPosX() const { return currentPosX; }
        short unsigned int getCurrentPosY() const { return currentPosY; }

        void setPosition(short unsigned int x, short unsigned int y) {
            currentPosX = x;
            currentPosY = y;
        }

        virtual unitInteraction fight(unite &u) = 0;
        virtual unitInteraction fightWithScoot(eclaireur &s) = 0;
        virtual unitInteraction fightWithCannonFodder(chairACanon &cf) = 0;
        virtual unitInteraction fightWithShockTroop(troupeDeChoc &st) = 0;
        bool mustBeVisible() const override;
        unite& takeFlag(drapeau &d);
        drapeau* operator*() const;
        unite& operator()();
        unite& operator()(short unsigned int x, short unsigned int y);
        std::pair<short unsigned int, short unsigned int> operator!() const;
        unite& operator&();
        unite &reset();
    };
}

#endif