#ifndef TROUPEDECHOC_H
#define TROUPEDECHOC_H

#include "unite.h"


class troupeDeChoc : public unite {
public:
    troupeDeChoc();
    unite& fightWithScoot(eclaireur &s) override;
    unite& fightWithCannonFodder(chairACanon &cf) override;
    unite& fightWithShockTroop(troupeDeChoc &st) override;
    ~troupeDeChoc() override = default;
    unite & fight(unite &u) override;
    bool canTakeFlag() override;
    troupeDeChoc* clone() const override;
};



#endif
