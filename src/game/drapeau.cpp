#include "../../include/game/drapeau.h"

using namespace kpt;

drapeau::drapeau(): currentPosX(0), currentPosY(0) {
}

std::string drapeau::asciiArtPrint() {
    return "\033[42m\033[30m>\033[0m";
}

drapeau * drapeau::clone() const {
    return new drapeau(*this);
}

