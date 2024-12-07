#include "../../include/units/unite.h"

using namespace kpt;

unite::unite() : maximalMove(0), initialPosX(0), initialPosY(0), currentPosX(0), currentPosY(0) {
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

