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
    protected:
        short unsigned int maximalMove;
        short unsigned int currentPosX;
        short unsigned int currentPosY;
        drapeau *flag;
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
        std::string asciiArtPrintNotVisible() override;
        unite& takeFlag(drapeau &d);
        unite* clone() const override = 0;
        drapeau* operator*() const;
        unite& operator()();
        std::string asciiArtPrint() override = 0;
        unite& operator()(short unsigned int x, short unsigned int y);
        std::pair<short unsigned int, short unsigned int> operator!() const;
        unite &operator&();
    };
}


#endif
