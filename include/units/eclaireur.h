#ifndef ECLAIREUR_H
#define ECLAIREUR_H

#include "unite.h"

namespace kpt {
    class eclaireur: public unite {
    public:
        eclaireur();
        ~eclaireur() override = default;

        unitInteraction fightWithScoot(eclaireur &s) override;

        unitInteraction fightWithCannonFodder(chairACanon &cf) override;

        unitInteraction fightWithShockTroop(troupeDeChoc &st) override;

        unitInteraction fight(unite &u) override;
        bool canTakeFlag() override;
        eclaireur *clone() const override;

        std::string asciiArtPrint() const override;
    };
}


#endif
