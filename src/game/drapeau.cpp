#include "../../include/game/drapeau.h"

#include <iostream>
#include <ostream>

using namespace kpt;

const short unsigned int drapeau::TURNS_BEFORE_RETURN = 2;

drapeau::drapeau(): currentPosX(0), currentPosY(0), hasAWarner(false), turnWhenDropped(0) {
}

std::string drapeau::asciiArtPrint() const {
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

std::pair<short unsigned, short unsigned> drapeau::operator!() const {
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

drapeau& drapeau::operator()() {
    currentPosX = initialPosX;
    currentPosY = initialPosY;
    return *this;
}

drapeau &drapeau::initCurrentCoord() {
    currentPosX = initialPosX;
    currentPosY = initialPosY;
    return *this;
}


bool drapeau::mustBeVisible() const {
    return hasAWarner;
}

bool drapeau::isOnGround() const {
    return !hasAWarner && (currentPosX != initialPosX || currentPosY != initialPosY);
}

bool drapeau::shouldReturnToBase(short unsigned int currentTurn) const {
    return isOnGround() && (currentTurn - turnWhenDropped >= TURNS_BEFORE_RETURN);
}

void drapeau::drop(short unsigned int currentTurn) {
    hasAWarner = false;
    turnWhenDropped = currentTurn;
}

bool drapeau::canBePickedUpBy(const unite* unit) const {
    return dynamic_cast<const eclaireur*>(unit) == nullptr;
}