#include "../../include/obstacles/obstacle.h"

using namespace kpt;
obstacle::obstacle() : costToQuit(0) {}

short unsigned int obstacle::operator*() const {
    return costToQuit;
}

obstacle & obstacle::operator()(short unsigned int value) {
    costToQuit = value;
    return *this;
}

bool obstacle::mustBeVisible() const {
    return false;
}
