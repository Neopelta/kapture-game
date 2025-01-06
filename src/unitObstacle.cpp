#include "../include/unitObstacle.h"

#include <iostream>
#include <ostream>

using namespace kpt;

unitObstacle::unitObstacle() : initialPosX(0), initialPosY(0) {
}

std::string unitObstacle::asciiArtPrintNotVisible() const {
    return "\033[48;5;235m \033[0m";
}

unitObstacle &unitObstacle::operator^(const std::pair<short unsigned int, short unsigned int> &coords)  {
    initialPosX = coords.first;
    initialPosY = coords.second;
    return *this;
}

bool unitObstacle::operator==(const unitObstacle *uo) const {
    return initialPosX == uo->initialPosX && initialPosY == uo->initialPosY;
}
