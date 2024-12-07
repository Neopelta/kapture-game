#ifndef UNITE_H
#define UNITE_H

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
        virtual unite& fight(unite &u) = 0;
        virtual unite &fightWithScoot(eclaireur &s) = 0;
        virtual unite &fightWithCannonFodder(chairACanon &cf) = 0;
        virtual unite &fightWithShockTroop(troupeDeChoc &st) = 0;
        unite& takeFlag(drapeau &d);
        virtual unite* clone() const = 0;
        drapeau* operator*() const;
        unite& operator()();
        unite& asciiArtPrint() override = 0;
    };
}


#endif
