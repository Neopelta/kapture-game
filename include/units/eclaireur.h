#ifndef ECLAIREUR_H
#define ECLAIREUR_H

#include "unite.h"

namespace kpt {
    class eclaireur: public unite {
    public:
        eclaireur();
        ~eclaireur() override = default;
        unite& fightWithScoot(eclaireur &s) override;
        unite& fightWithCannonFodder(chairACanon &cf) override;
        unite& fightWithShockTroop(troupeDeChoc &st) override;
        unite& fight(unite &u) override;
        bool canTakeFlag() override;
        eclaireur *clone() const override;
        unite& asciiArtPrint() override;
    };
}


#endif
