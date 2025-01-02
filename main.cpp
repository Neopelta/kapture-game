#include <iostream>
#include "include/game/kaptureGame.h"
#include "include/game/turnManager.h"

using namespace kpt;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialisation du jeu
    kaptureGame<25, 10>* kapture = kaptureGame<25, 10>::getInstance(2);
    kapture->initializeGame();

    // Création du gestionnaire de tours
    TurnManager<25, 10> turnManager(kapture);

    bool gameRunning = true;
    while (gameRunning) {
        for (joueur& player : kapture->getPlayers()) {
            // D'abord initialiser le tour du joueur
            std::cout << "\nTour du joueur " << player() << std::endl;
            turnManager.startTurn(player);

            // Ensuite afficher le plateau
            std::cout << *kapture << std::endl;

            bool playerTurn = true;
            while (playerTurn) {
                unite* currentUnit = turnManager.getCurrentUnit();
                if (!currentUnit) {
                    // Si plus d'unités disponibles, recommencer avec la première
                    turnManager.startTurn(player);
                    currentUnit = turnManager.getCurrentUnit();
                }

                try {
                    std::cout << "\nUnité actuelle : " << currentUnit->asciiArtPrint()
                          << " (" << turnManager.getRemainingMoves() << " mouvements restants)"
                          << " [" << currentUnit->getCurrentPosX() << "," << currentUnit->getCurrentPosY() << "]"
                          << std::endl;

                    std::string command;
                    std::cout << "Entrez une commande (move <steps> <direction>, stop pour unité suivante, end pour finir le tour) : ";
                    std::getline(std::cin, command);

                    if (command == "quit") {
                        gameRunning = false;
                        break;
                    }

                    if (!turnManager.processCommand(command)) {
                        if (command == "end_turn" || command == "end" || command == "et") {
                            playerTurn = false;  // Fin du tour du joueur
                        } else if (command != "stop") {
                            std::cout << "Commande invalide ou mouvement impossible" << std::endl;
                        }
                    }

                    // Afficher le plateau après chaque commande
                    std::cout << *kapture << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Erreur : " << e.what() << std::endl;
                }
            }

            if (!gameRunning) break;
        }

        ++(*kapture);
    }

    try {
        kapture->saveGame("data.txt");
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la sauvegarde : " << e.what() << std::endl;
    }

    delete kapture;
    return 0;
}