#include "../../include/game/drapeau.h"

using namespace kpt;

drapeau::drapeau() : initialPosX(0), initialPosY(0), currentPosX(0), currentPosY(0) {
}

unitObstacle & drapeau::asciiArtPrint() {
    return *this;
}

drapeau * drapeau::clone() const {
    return new drapeau(*this);
}

