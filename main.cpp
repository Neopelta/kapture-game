#include <iostream>
#include "include/game/kaptureGame.h"

using namespace kpt;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    kaptureGame<25, 10>* kapture = kaptureGame<25, 10>::getInstance(2);
    kapture->initializeGame();
    std::cout << "\n"
              << " ____  __.              __                        \n"
              << "|    |/ _|____  _______/  |_ __ _________   ____  \n"
              << "|      < \\__  \\ \\____ \\   __\\  |  \\_  __ \\_/ __ \\ \n"
              << "|    |  \\ / __ \\|  |_> >  | |  |  /|  | \\/\\  ___/ \n"
              << "|____|__ (____  /   __/|__| |____/ |__|    \\_____\n"
              << "       \\/    \\/|__|                             \n"
              << "\n";

    std::cout << *kapture << std::endl;

    kapture->saveGame("data.txt");
    delete kapture;
    return 0;
}
