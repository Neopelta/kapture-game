#include "../../include/obstacles//terrainNu.h"

#include <iostream>
#include <ostream>

using namespace kpt;

terrainNu::terrainNu() {
    this->operator()(1);
}


std::string terrainNu::asciiArtPrint() const {
    return "\033[42m\033[30m \033[0m";
}

terrainNu *terrainNu::clone() const {
    return new terrainNu(*this);
}

