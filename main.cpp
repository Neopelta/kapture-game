#include <iostream>
#include "include/game/kaptureGame.h"

using namespace kpt;

int main() {
    joueur j1 = joueur(1);
    joueur j2 = joueur(2);

    kaptureGame<25, 25> *kapture = kaptureGame<25, 25>::getInstance(j1, j2);

    std::cout << **kapture << std::endl;

    delete kapture;
    return 0;
}
