#include "../../include/obstacles/foret.h"

using namespace kpt;
foret::foret() {
    this->operator()(2);
}

std::string foret::asciiArtPrint() const {
    return "\033[48;5;23m\033[30m#\033[0m";
}

foret * foret::clone() const {
    return new foret(*this);
}
