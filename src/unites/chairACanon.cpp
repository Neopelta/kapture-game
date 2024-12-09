#include "../../include/units/chairACanon.h"

#include <iostream>

using namespace kpt;
chairACanon::chairACanon() {
    maximalMove = 3;
    initialPosX = 0;
    initialPosY = 0;
}

unite & chairACanon::fightWithScoot(eclaireur &s) {
    std::cout << "Chair à canon vs Eclaireur : Eclaireur perd" << std::endl;
    return *this;
}

unite & chairACanon::fightWithCannonFodder(chairACanon &cf) {
    srand(time(nullptr));
    float rand = std::rand() % 100 + 1;
    if (rand < 50.0f)
        std::cout << "Chair à canon vs Chair à canon : le premier gagne" << std::endl;
    else
        std::cout << "Chair à canon vs Chair à canon : le deuxieme gagne" << std::endl;
    return *this;
}

unite & chairACanon::fightWithShockTroop(troupeDeChoc &st) {
    std::cout << "Chair à canon vs Troupe de choc : Chair à canon perd" << std::endl;
    return *this;
}

unite & chairACanon::fight(unite &u) {
    return u.fightWithCannonFodder(*this);
}

bool chairACanon::canTakeFlag() {
    return true;
}

chairACanon *chairACanon::clone() const {
    return new chairACanon(*this);
}

std::string chairACanon::asciiArtPrint() {
    return "\033[42m\033[30m|\033[0m";
}

