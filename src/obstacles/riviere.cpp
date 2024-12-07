#include "../../include/obstacles/riviere.h"

using namespace kpt;
riviere::riviere() {
    this->operator()(0); // 0 at this moment but maximalCost of an unit in the game
}


obstacle &riviere::asciiArtPrint() {
    return *this;
}
