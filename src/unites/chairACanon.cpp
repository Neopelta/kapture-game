#include "../../include/units/chairACanon.h"

#include <iostream>

using namespace kpt;
chairACanon::chairACanon() {
    maximalMove = 3;
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
    if (flag != nullptr && cf.flag != nullptr) {
        std::cout << "Les deux unités portent un drapeau et se comportent comme des éclaireurs : match nul" << std::endl;
        return DRAW;
    }
    if (flag != nullptr) {
        std::cout << "L'unité courante se comporte comme un éclaireur car elle porte le drapeau : elle perd" << std::endl;
        return LOST;
    }
    if (cf.flag != nullptr) {
        std::cout << "L'unité adverse se comporte comme un éclaireur car elle porte le drapeau : elle perd" << std::endl;
        return WON;
    }
    const short unsigned int rand = std::rand() % 100 + 1;
    std::cout << "Aucune unité ne porte de drapeau : 1 chance sur 2" << std::endl;
    return rand > 50 ? WON : LOST;
}

unitInteraction chairACanon::fightWithShockTroop(troupeDeChoc &st) {
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

std::string chairACanon::asciiArtPrint() const {
    if (flag == nullptr)
        return "\033[42m\033[30mC\033[0m";
    return "\033[45m\033[30mC\033[0m";
}

