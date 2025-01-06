#include <iostream>
#include "include/game/kaptureGame.h"
#include "include/game/TurnManager.h"

using namespace kpt;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialisation du jeu
    kaptureGame<8, 8>* kapture = kaptureGame<8, 8>::getInstance(2);
    kapture->loadGame("data.txt");

    std::cout << "\n"
          << " ____  __.              __                        \n"
          << "|    |/ _|____  _______/  |_ __ _________   ____  \n"
          << "|      < \\__  \\ \\____ \\   __\\  |  \\_  __ \\_/ __ \\ \n"
          << "|    |  \\ / __ \\|  |_> >  | |  |  /|  | \\/\\  ___/ \n"
          << "|____|__ (____  /   __/|__| |____/ |__|    \\_____\n"
          << "       \\/    \\/|__|                             \n"
          << "\n";



    // Création du gestionnaire de tours
    TurnManager<8, 8> turnManager(kapture);

    bool gameRunning = true;
    while (gameRunning) {
        for (joueur& player : kapture->getPlayers()) {
            std::cout << "\nTour du joueur " << player() << std::endl;
            turnManager.startTurn(player);

            std::cout << *kapture << std::endl;

            bool playerTurn = true;
            unite* selectedUnit = nullptr;

            while (playerTurn) {
                if (!selectedUnit) {
                    std::cout << "Aucune unité sélectionnée. Entrez 'select <y,x>' pour choisir une unité (par exemple, select 1,1) ou 'quit' pour quitter : ";
                    std::string selectCommand;
                    std::getline(std::cin, selectCommand);

                    if (selectCommand == "quit") {
                        gameRunning = false;
                        playerTurn = false;
                        break;
                    }

                    if (selectCommand == "end") {
                        playerTurn = false;
                        continue;
                    }

                    if (selectCommand.substr(0, 6) == "select") {
                        std::string coords = selectCommand.substr(7);
                        size_t commaPos = coords.find(',');
                        if (commaPos != std::string::npos) {
                            int x = std::stoi(coords.substr(0, commaPos));
                            int y = std::stoi(coords.substr(commaPos + 1));

                            selectedUnit = kapture->getUnitAt(player, {x, y});
                            if (selectedUnit) {
                                turnManager.selectUnit(selectedUnit);
                            } else
                                std::cout << "Aucune unité trouvée aux coordonnées spécifiées." << std::endl;

                        } else
                            std::cout << "Coordonnées invalides. Essayez de nouveau." << std::endl;

                    } else
                        std::cout << "Commande invalide. Utilisez 'select <y,x>' pour choisir une unité." << std::endl;

                    continue;
                }

                std::cout << "Unité sélectionnée : " << selectedUnit->asciiArtPrint()
                          << " (" << turnManager.getRemainingMoves() << " mouvements restants)"
                          << " [" << selectedUnit->getCurrentPosX() << "," << selectedUnit->getCurrentPosY() << "]"
                          << std::endl;

                std::string command;
                std::cout << "Entrez une commande (mv <steps> <direction>, stop pour sélectionner une autre unité, end pour finir le tour, quit pour quitter) : ";
                std::getline(std::cin, command);

                if (command == "quit") {
                    gameRunning = false;
                    playerTurn = false;
                    break;
                }

                bool isChange = false;

                if (command.substr(0, 2) == "mv") {
                    if (!turnManager.processCommand(command))
                        std::cout << "Mouvement invalide ou impossible" << std::endl;
                    else {
                        unite *u = kapture->operator()(selectedUnit);
                        if (u != nullptr) {
                            kapture->handleFight(u, selectedUnit);
                        }
                        isChange = true;

                        if (kapture->checkVictoryCondition(player)) {
                            std::cout << "\033[1;32mLe joueur " << player() << " a gagné en atteignant son drapeau avec le drapeau ennemi!\033[0m" << std::endl;
                            gameRunning = false;
                            playerTurn = false;
                            break;
                        } else {
                            std::cout << "Condition de victoire non remplie." << std::endl;
                        }

                    }
                }
                else if (command == "end_turn" || command == "end" || command == "et")
                    playerTurn = false;
                else if (command == "stop" || command == "s" || command == "next")
                    selectedUnit = nullptr;
                else
                    std::cout << "Commande invalide" << std::endl;

                if (isChange) {
                    kapture->updateVisionFields(player, selectedUnit);
                    std::cout << *kapture << std::endl;
                }
            }

            if (!gameRunning)
                break;
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
