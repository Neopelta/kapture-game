#ifndef CHAIRACANON_H
#define CHAIRACANON_H

#include "unite.h"

namespace kpt {
    class chairACanon : public unite {
    public:
        chairACanon();
        ~chairACanon() override = default;

        unitInteraction fightWithScoot(eclaireur &s) override;

        unitInteraction fightWithCannonFodder(chairACanon &cf) override;

        unitInteraction fightWithShockTroop(troupeDeChoc &st) override;

        unitInteraction fight(unite &u) override;
        bool canTakeFlag() override;
        chairACanon* clone() const override;

        std::string asciiArtPrint() override;
    };
}



#endif
