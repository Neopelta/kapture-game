#include "../../include/game/drapeau.h"

drapeau::drapeau() : initialPosX(0), initialPosY(0), currentPosX(0), currentPosY(0) {
    holder = nullptr;
}

drapeau::~drapeau() = default; // Not need to free some resources because the unit will be initialized before

drapeau::drapeau(const drapeau &d) {
    initialPosX = d.initialPosX;
    initialPosY = d.initialPosY;
    currentPosX = d.currentPosX;
    currentPosY = d.currentPosY;
    holder = d.holder;
}

drapeau & drapeau::operator=(const drapeau &d) {
    if (this != &d) {
        initialPosX = d.initialPosX;
        initialPosY = d.initialPosY;
        currentPosX = d.currentPosX;
        currentPosY = d.currentPosY;
        holder = d.holder;
    }
    return *this;
}

unite *drapeau::operator*() const {
    return holder;
}

drapeau& drapeau::operator()(unite &u) {
    holder = &u;
    return *this;
}

