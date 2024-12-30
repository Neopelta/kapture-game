#include "../../include/units/chairACanon.h"

#include <iostream>

using namespace kpt;
chairACanon::chairACanon() {
    maximalMove = 3;
    initialPosX = 0;
    initialPosY = 0;
}

unitInteraction chairACanon::fightWithScoot(eclaireur &s) {
    if (flag != nullptr) {
        std::cout << "L'unité se comporte comme un éclaireur : Rien ne se passe" << std::endl;
        return DRAW;
    }
    std::cout << "Chair à canon vs Eclaireur : Eclaireur perd" << std::endl;
    return WON;
}

unitInteraction chairACanon::fightWithCannonFodder(chairACanon &cf) {
    if (flag != nullptr) {
        std::cout << "L'unité se comporte comme un éclaireur : Chair à canon perd" << std::endl;
        return LOST;
    }
    const short unsigned int rand = std::rand() % 100 + 1;
    std::cout << "1 chance sur 2" << std::endl;
    return rand > 50 ? WON : LOST;
}

unitInteraction chairACanon::fightWithShockTroop(troupeDeChoc &st) {
    // he looses with a flag or not
    std::cout << "Chair à canon vs Troupe de choc : Chair à canon perd" << std::endl;
    return LOST;
}

unitInteraction chairACanon::fight(unite &u) {
    return u.fightWithCannonFodder(*this);
}

bool chairACanon::canTakeFlag() {
    return true;
}

chairACanon *chairACanon::clone() const {
    return new chairACanon(*this);
}

std::string chairACanon::asciiArtPrint() {
    if (flag == nullptr)
        return "\033[42m\033[30mC\033[0m";
    return "\033[48;5;196mX\033[0m";
}

