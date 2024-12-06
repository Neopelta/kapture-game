#ifndef UNITE_H
#define UNITE_H

#include "../unitObstacle.h"
class eclaireur;
class chairACanon;
class troupeDeChoc;

class unite: public unitObstacle {
protected:
    short unsigned int maximalMove;
    short unsigned int initialPosX;
    short unsigned int initialPosY;
    short unsigned int currentPosX;
    short unsigned int currentPosY;
    // TODO : implement the flag system here
public:
    unite();
    ~unite() override = default;
    virtual unite& fight(unite &u) = 0;
    virtual unite &fightWithScoot(eclaireur &s) = 0;
    virtual unite &fightWithCannonFodder(chairACanon &cf) = 0;
    virtual unite &fightWithShockTroop(troupeDeChoc &st) = 0;
    virtual bool canTakeFlag() = 0;
    virtual unite* clone() const = 0;
};



#endif
