#include "../../include/units/eclaireur.h"

#include <iostream>

using namespace kpt;
eclaireur::eclaireur() {
    maximalMove = 5;
    initialPosX = 0;
    initialPosY = 0;
    currentPosX = 0;
    currentPosY = 0;
}

unite& eclaireur::fightWithScoot(eclaireur &s) {
    std::cout << "Rien ne se passe" << std::endl;
    return *this;
}

unite& eclaireur::fightWithCannonFodder(chairACanon &cf) {
    std::cout << "Eclaireur vs Chair à canon : Eclaireur perd" << std::endl;
    return *this;
}

unite& eclaireur::fightWithShockTroop(troupeDeChoc &st) {
    std::cout << "Eclaireur vs Troupe de choc : Eclaireur perd" << std::endl;
    return *this;
}

unite& eclaireur::fight(unite &u) {
    return u.fightWithScoot(*this);
}

bool eclaireur::canTakeFlag() {
    return false;
}

eclaireur *eclaireur::clone() const {
    return new eclaireur(*this);
}

std::string eclaireur::asciiArtPrint() {
    return "\033[42m\033[30m*\033[0m";
}



