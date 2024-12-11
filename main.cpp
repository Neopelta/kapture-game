#include <iostream>
#include "include/game/kaptureGame.h"

using namespace kpt;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    kaptureGame<25, 10>* kapture = kaptureGame<25, 10>::getInstance(2);
    kapture->initializeGame();
    std::cout << *kapture << std::endl;

    kapture->saveGame("data.txt");
    delete kapture;
    return 0;
}
