#include "../../include/units/unite.h"
#include "../../include/game/drapeau.h"

#include <iostream>
#include <ostream>

using namespace kpt;

unite::unite() : maximalMove(0), currentPosX(0), currentPosY(0) {
    flag = nullptr;
}

unite::unite(const unite &other) {
    std::cout << "[DEBUG-UNITE] Appel au constructeur de copie" << std::endl;
    maximalMove = other.maximalMove;
    initialPosX = other.initialPosX;
    initialPosY = other.initialPosY;
    currentPosX = other.currentPosX;
    currentPosY = other.currentPosY;
    flag = other.flag;
    std::cout << "[DEBUG-UNITE] Position après copie: ["
              << currentPosX << "," << currentPosY << "]" << std::endl;
}

unite &unite::operator=(const unite &other) {
    std::cout << "[DEBUG-UNITE] Appel à l'opérateur d'assignation" << std::endl;
    if (this != &other) {
        maximalMove = other.maximalMove;
        initialPosX = other.initialPosX;
        initialPosY = other.initialPosY;
        currentPosX = other.currentPosX;
        currentPosY = other.currentPosY;
        flag = other.flag;
    }
    return *this;
}


bool unite::mustBeVisible() const {
    return flag != nullptr;
}

unite& unite::takeFlag(drapeau &d) {
    std::cout << "[DEBUG] Appel à takeFlag - flag avant : "
              << flag << (flag ? " (non null)" : " (null)") << std::endl;
    if (canTakeFlag()) {
        flag = &d;
        flag->operator()(true);
    }
    std::cout << "[DEBUG] flag après : "
              << flag << (flag ? " (non null)" : " (null)") << std::endl;
    return *this;
}

drapeau *unite::operator*() const {
    return flag;
}

unite &unite::operator()() {
    std::cout << "[DEBUG] Appel à operator() - flag réinitialisé à nullptr" << std::endl;
    flag = nullptr;
    return *this;
}

unite & unite::operator()(short unsigned int x, short unsigned int y) {
    currentPosX = x;
    currentPosY = y;
    return *this;
}

std::pair<short unsigned int, short unsigned int> unite::operator!() const {
    return {currentPosX, currentPosY};
}

unite& unite::operator&() {
    currentPosX = initialPosX;
    currentPosY = initialPosY;
    return *this;
}

unite & unite::reset() {
    std::cout << "[DEBUG-UNITE] Appel à reset() - Ancienne position: "
                  << currentPosX << "," << currentPosY
                  << " -> Nouvelle position: " << initialPosX << "," << initialPosY << std::endl;    currentPosX = initialPosX;
    currentPosY = initialPosY;
    return *this;
}
