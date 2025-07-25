#include "../../include/units/troupeDeChoc.h"

#include <iostream>

using namespace kpt;
troupeDeChoc::troupeDeChoc() {
    maximalMove = 2;
}

unitInteraction troupeDeChoc::fightWithScoot(eclaireur &s) {
    if (flag != nullptr) {
        std::cout << "L'unité se comporte comme un éclaireur : Rien ne se passe" << std::endl;
        return DRAW;
    }
    std::cout << "Troupes de choc vs Eclaireur : Eclaireur perd" << std::endl;
    return WON;
}

unitInteraction troupeDeChoc::fightWithCannonFodder(chairACanon &cf) {
    if (flag != nullptr) {
        std::cout << "L'unité se comporte comme un éclaireur : Troupe de choc perd" << std::endl;
        return LOST;
    }
    std::cout << "Troupes de choc vs Chair à canon : Chair à canon perd" << std::endl;
    return WON;
}

unitInteraction troupeDeChoc::fightWithShockTroop(troupeDeChoc &st) {
    if (flag != nullptr) {
        std::cout << "L'unité se comporte comme un éclaireur : Troupe de choc perd" << std::endl;
        return LOST;
    }

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

std::string troupeDeChoc::asciiArtPrint() const {
    if (flag == nullptr)
        return "\033[42m\033[30mT\033[0m";
    return "\033[45m\033[30mT\033[0m";
}


