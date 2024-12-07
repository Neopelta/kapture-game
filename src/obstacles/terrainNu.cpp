#include "../../include/obstacles//terrainNu.h"

using namespace kpt;

terrainNu::terrainNu() {
    this->operator()(1);
}


obstacle &terrainNu::asciiArtPrint() {
    return *this;
}

terrainNu *terrainNu::clone() const {
    return new terrainNu(*this);
}

