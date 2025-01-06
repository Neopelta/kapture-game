#include "../../include/obstacles/riviere.h"

using namespace kpt;
riviere::riviere() {
    this->operator()(0); // 0 at this moment but maximalCost of an unit in the game
}


std::string riviere::asciiArtPrint() const {
    return "\033[48;5;38m\033[30m~\033[0m";
}

riviere * riviere::clone() const {
    return new riviere(*this);
}
