#include "../../include/game/drapeau.h"

using namespace kpt;

drapeau::drapeau(): currentPosX(0), currentPosY(0), hasAWarner(false) {
}

std::string drapeau::asciiArtPrint() {
    if (hasAWarner)
        return unitObstacle::asciiArtPrintNotVisible();
    return "\033[42m\033[30m>\033[0m";
}

drapeau * drapeau::clone() const {
    return new drapeau(*this);
}

drapeau & drapeau::operator()(bool assignment) {
    hasAWarner = assignment;
    return *this;
}

std::pair<short unsigned int, short unsigned int> drapeau::operator!() const {
    return std::make_pair(currentPosX, currentPosY);
}

drapeau & drapeau::operator()(const std::pair<short unsigned int, short unsigned int> &pos) {
    currentPosX = pos.first;
    currentPosY = pos.second;
    return *this;
}

bool drapeau::operator*() const {
    return hasAWarner;
}

bool drapeau::mustBeVisible() const {
    return hasAWarner;
}

