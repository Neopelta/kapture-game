#include "../../include/units/unite.h"

#include <iostream>
#include <ostream>

using namespace kpt;

unite::unite() : maximalMove(0), currentPosX(0), currentPosY(0) {
    flag = nullptr;
}

unite::unite(const unite &other) {
    maximalMove = other.maximalMove;
    initialPosX = other.initialPosX;
    initialPosY = other.initialPosY;
    currentPosX = other.currentPosX;
    currentPosY = other.currentPosY;
    flag = other.flag;
}

unite &unite::operator=(const unite &other) {
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

unite &unite::takeFlag(drapeau &d) {
    if (canTakeFlag())
        flag = &d;
    return *this;
}

drapeau *unite::operator*() const {
    return flag;
}

unite &unite::operator()() {
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

unite & unite::reset() {
    std::cout << "IIT" << initialPosX << "," << initialPosY << std::endl;
    currentPosX = initialPosX;
    currentPosY = initialPosY;
    return *this;
}
