#ifndef TROUPEDECHOC_H
#define TROUPEDECHOC_H

#include "unite.h"

namespace kpt {
    class troupeDeChoc : public unite {
    public:
        troupeDeChoc();

        unitInteraction fightWithScoot(eclaireur &s) override;

        unitInteraction fightWithCannonFodder(chairACanon &cf) override;

        unitInteraction fightWithShockTroop(troupeDeChoc &st) override;
        ~troupeDeChoc() override = default;

        unitInteraction fight(unite &u) override;
        bool canTakeFlag() override;
        troupeDeChoc* clone() const override;

        std::string asciiArtPrint() const override;
    };
}



#endif
