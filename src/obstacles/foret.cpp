#include "../../include/obstacles/foret.h"

using namespace kpt;
foret::foret() {
    this->operator()(2);
}


obstacle &foret::asciiArtPrint() {
    return *this;
}
