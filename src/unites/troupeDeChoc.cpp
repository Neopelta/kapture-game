#include "../../include/units/troupeDeChoc.h"

#include <iostream>

using namespace kpt;
troupeDeChoc::troupeDeChoc() {
    maximalMove = 2;
    initialPosX = 0;
    initialPosY = 0;
    currentPosX = 0;
    currentPosY = 0;
}

unitInteraction troupeDeChoc::fightWithScoot(eclaireur &s) {
    std::cout << "Troupes de choc vs Eclaireur : Eclaireur perd" << std::endl;
    return WON;
}

unitInteraction troupeDeChoc::fightWithCannonFodder(chairACanon &cf) {
    std::cout << "Troupes de choc vs Chair à canon : Chair à canon perd" << std::endl;
    return WON;
}

unitInteraction troupeDeChoc::fightWithShockTroop(troupeDeChoc &st) {
    std::cout << "Troupe de choc vs Troupe de choc : Action" << std::endl;
    if (currentPosY > 0 && st.currentPosY > 0) {
        std::cout << "Les deux reculent" << std::endl;
        --currentPosY;
        --st.currentPosY;
    }
    else {
        std::cout << "Les deux reviennent au spawn" << std::endl;
        currentPosX = initialPosX;
        currentPosY = initialPosY;
        st.currentPosX = st.initialPosX;
        st.currentPosY = st.initialPosY;
    }
    return DRAW;
}

unitInteraction troupeDeChoc::fight(unite &u) {
    return u.fightWithShockTroop(*this);
}

bool troupeDeChoc::canTakeFlag() {
    return true;
}

troupeDeChoc *troupeDeChoc::clone() const {
    return new troupeDeChoc(*this);
}

std::string troupeDeChoc::asciiArtPrint() {
    if (flag == nullptr)
        return "\033[42m\033[30mT\033[0m";
    return "\033[48;5;196mX\033[0m";
}


