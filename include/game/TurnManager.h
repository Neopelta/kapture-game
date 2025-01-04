#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include <memory>
#include <vector>
#include <map>
#include <sstream>
#include "../commands/command.h"
#include "../commands/MoveCommand.h"
#include "../commands/stop.h"
#include "../commands/EndTurnCommand.h"
#include "../game/joueur.h"
#include "../units/unite.h"
#include "../game/plateau.h"
#include "../obstacles/obstacle.h"
#include "../obstacles/terrainNu.h"

namespace kpt {
    template<short unsigned int ROW, short unsigned int COL>
    class TurnManager {
    private:
        std::vector<std::unique_ptr<command>> commands;
        plateau<ROW, COL>& board;
        kaptureGame<ROW, COL>* game;
        joueur* currentPlayer;
        std::vector<unite*> currentUnits;  // Stockage des unités du joueur actuel
        std::vector<unite*>::iterator currentUnit;
        int remainingMoves;

        void registerCommands() {
            commands.push_back(std::make_unique<MoveCommand>());
            commands.push_back(std::make_unique<StopCommand>());
            commands.push_back(std::make_unique<EndTurnCommand>());
        }

        bool validateMove(int currentX, int currentY, int dx, int dy) const {
            // Calculer la nouvelle position
            int newX = currentX + dx;
            int newY = currentY + dy;

            // Vérifier les limites du plateau
            if (newX < 0 || newX >= ROW || newY < 0 || newY >= COL) {
                return false;
            }

            // Vérifier la cellule de destination
            int targetIndex = newX * COL + newY;
            unitObstacle* targetCell = board[targetIndex].operator->();

            // Vérifier si c'est un drapeau
            if (dynamic_cast<drapeau*>(targetCell) != nullptr) {
                return false;
            }

            // Vérifier si c'est une unité
            if (dynamic_cast<unite*>(targetCell) != nullptr) {
                return false;
            }

            // Gérer le coût de déplacement selon le type d'obstacle
            obstacle* obs = dynamic_cast<obstacle*>(targetCell);
            if (obs != nullptr) {
                short unsigned int cost = **obs;

                // Si c'est une rivière
                if (dynamic_cast<riviere*>(targetCell) != nullptr) {
                    unite* unit = *currentUnit;
                    if (unit != nullptr) {
                        cost = unit->getMaximalMove();
                    }
                }

                return cost <= remainingMoves;
            }

            return true;
        }

        bool executeMove(const std::vector<std::string>& args) {
            if (args.size() != 2) {
                return false;
            }

            try {
                int steps = std::stoi(args[0]);
                std::string direction = args[1];

                auto delta = MoveCommand::getDirectionDelta(direction);
                if (!delta.has_value()) {
                    return false;
                }

                auto [dx, dy] = delta.value();
                unite* unit = *currentUnit;

                if (!unit) {
                    throw std::runtime_error("Unité invalide");
                }

                int currentX = unit->getCurrentPosX();
                int currentY = unit->getCurrentPosY();

                // Calculer le coût total du déplacement
                int totalCost = 0;
                for (int i = 1; i <= steps; ++i) {
                    int checkX = currentX + (dx * i);
                    int checkY = currentY + (dy * i);

                    if (checkX < 0 || checkX >= ROW || checkY < 0 || checkY >= COL) {
                        return false;
                    }

                    int checkIndex = checkX * COL + checkY;
                    unitObstacle* checkCell = board[checkIndex].operator->();

                    obstacle* obs = dynamic_cast<obstacle*>(checkCell);
                    if (obs != nullptr) {
                        if (dynamic_cast<riviere*>(checkCell) != nullptr) {
                            totalCost += unit->getMaximalMove();
                        } else {
                            totalCost += **obs;
                        }
                    }

                    if (totalCost > remainingMoves) {
                        return false;
                    }

                    // Vérifier si le chemin est bloqué
                    if (!validateMove(currentX, currentY, dx * i, dy * i)) {
                        return false;
                    }
                }

                // Si on arrive ici, le mouvement est valide
                // Retirer l'unité de sa position actuelle
                board[currentX * COL + currentY] = new terrainNu();

                // Mettre à jour la position de l'unité
                int newX = currentX + (dx * steps);
                int newY = currentY + (dy * steps);
                unit->setPosition(newX, newY);

                // Placer l'unité à sa nouvelle position
                board[newX * COL + newY] = unit;
                board[newX * COL + newY](*currentPlayer);

                remainingMoves -= totalCost;
                return true;

            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de l'exécution du mouvement : " << e.what() << std::endl;
                return false;
            }
        }
    public:
        TurnManager(kaptureGame<ROW, COL>* g)
        : board(g->getBoard()), game(g), currentPlayer(nullptr), remainingMoves(0) {
            registerCommands();
        }

        void startTurn(joueur& player) {
            currentPlayer = &player;
            game->setActivePlayer(currentPlayer);  // Met à jour le joueur actif dans le jeu

            if (!currentPlayer) {
                throw std::runtime_error("Joueur invalide");
            }

            currentUnits = *player;
            if (currentUnits.empty()) {
                throw std::runtime_error("Pas d'unités disponibles pour le joueur");
            }

            currentUnit = currentUnits.begin();
            if (!(*currentUnit)) {
                throw std::runtime_error("Unité invalide");
            }

            remainingMoves = (*currentUnit)->getMaximalMove();
        }

        unite* getCurrentUnit() const {
            if (currentUnit == currentUnits.end() || !(*currentUnit)) {
                return nullptr;
            }
            return *currentUnit;
        }

        bool processCommand(const std::string& input) {
            std::istringstream iss(input);
            std::string commandName;
            iss >> commandName;

            auto cmdIt = std::find_if(commands.begin(), commands.end(),
                [&commandName](const auto& cmd) { return cmd->matches(commandName); });

            if (cmdIt == commands.end()) {
                return false;
            }

            std::vector<std::string> args;
            std::string arg;
            while (iss >> arg) {
                args.push_back(arg);
            }

            if (commandName == "end" || commandName == "fin") {
                return false;
            }

            if (commandName == "stop" || commandName == "s" || commandName == "next") {
                return nextUnit();  // Continue avec l'unité suivante
            }

            return executeMove(args);
        }

        bool nextUnit() {
            ++currentUnit;
            if (currentUnit == currentUnits.end()) {
                return false;
            }

            if (!(*currentUnit)) {
                throw std::runtime_error("Unité suivante invalide");
            }

            remainingMoves = (*currentUnit)->getMaximalMove();
            return true;
        }

        int getRemainingMoves() const {
            return remainingMoves;
        }
    };
}

#endif