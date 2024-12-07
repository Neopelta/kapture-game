#ifndef CHAIRACANON_H
#define CHAIRACANON_H

#include "unite.h"

namespace kpt {
    class chairACanon : public unite {
    public:

        chairACanon();
        ~chairACanon() override = default;
        unite& fightWithScoot(eclaireur &s) override;
        unite& fightWithCannonFodder(chairACanon &cf) override;
        unite& fightWithShockTroop(troupeDeChoc &st) override;
        unite& fight(unite &u) override;
        bool canTakeFlag() override;
        chairACanon* clone() const override;
        unite& asciiArtPrint() override;
    };
}



#endif
