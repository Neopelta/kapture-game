#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include <memory>
#include <vector>
#include <sstream>
#include <map>
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
        std::vector<std::unique_ptr<command>> commands;
        plateau<ROW, COL>& board;
        kaptureGame<ROW, COL>* game;
        joueur* currentPlayer;
        unite* selectedUnit;
        int remainingMoves;
        std::map<unite*, int> unitMovesRemaining;
        std::map<std::pair<int, int>, int> usedMoves;

        void registerCommands() {
            commands.push_back(std::make_unique<MoveCommand>());
            commands.push_back(std::make_unique<StopCommand>());
            commands.push_back(std::make_unique<EndTurnCommand>());
        }

        bool isValidPosition(int x, int y) const {
            return x >= 0 && x < ROW && y >= 0 && y < COL;
        }

        bool isOccupiedByFlag(unitObstacle* cell) const {
            return dynamic_cast<drapeau*>(cell) != nullptr;
        }

        bool isOccupiedByUnit(unitObstacle* cell) const {
            return dynamic_cast<unite*>(cell) != nullptr;
        }

        int calculateMoveCost(unitObstacle* cell, unite* unit) const {
            obstacle* obs = dynamic_cast<obstacle*>(cell);
            if (!obs) return 0;

            if (dynamic_cast<riviere*>(cell) != nullptr) {
                return unit->getMaximalMove();
            }
            return **obs;
        }

        bool validateMove(int currentX, int currentY, int dx, int dy) const {
            int newX = currentX + dx;
            int newY = currentY + dy;

            if (!isValidPosition(newX, newY)) return false;

            int targetIndex = newX * COL + newY;
            unitObstacle* targetCell = board[targetIndex]->operator->();

            if (isOccupiedByFlag(targetCell) || isOccupiedByUnit(targetCell)) {
                return false;
            }

            int cost = calculateMoveCost(targetCell, selectedUnit);
            return cost <= remainingMoves;
        }

        bool validatePath(int currentX, int currentY, int dx, int dy, int steps, int& totalCost) {
            for (int i = 1; i <= steps; ++i) {
                int checkX = currentX + (dx * i);
                int checkY = currentY + (dy * i);

                if (!isValidPosition(checkX, checkY)) return false;

                int checkIndex = checkX * COL + checkY;
                unitObstacle* checkCell = board[checkIndex].operator->();

                int stepCost = calculateMoveCost(checkCell, selectedUnit);
                totalCost += stepCost;

                if (totalCost > remainingMoves || !validateMove(currentX, currentY, dx * i, dy * i)) {
                    return false;
                }
            }
            return true;
        }

        bool executeMove(const std::vector<std::string>& args) {
            if (args.size() != 2) {
                return false;
            }

            try {
                int steps = std::stoi(args[0]);
                const std::string& direction = args[1];

                auto delta = MoveCommand::getDirectionDelta(direction);
                if (!delta.has_value()) {
                    return false;
                }

                auto [dx, dy] = delta.value();

                if (!selectedUnit) {
                    throw std::runtime_error("Unité invalide");
                }

                int currentX = selectedUnit->operator!().first;
                int currentY = selectedUnit->operator!().second;

                int totalCost = 0;
                for (int i = 1; i <= steps; ++i) {
                    int checkX = currentX + (dx * i);
                    int checkY = currentY + (dy * i);

                    if (checkX < 0 || checkX >= ROW || checkY < 0 || checkY >= COL) {
                        return false;
                    }

                    int checkIndex = checkX * COL + checkY;
                    std::cout << "CHECK" << checkX << " " << checkY << std::endl;
                    unitObstacle* checkCell = board[checkIndex]->operator->();

                    obstacle* obs = dynamic_cast<obstacle*>(checkCell);
                    if (obs != nullptr) {
                        if (dynamic_cast<riviere*>(checkCell) != nullptr) {
                            totalCost += selectedUnit->getMaximalMove();

                        } else
                            totalCost += obs->operator*();

                        int nextX = checkX + dx;
                        int nextY = checkY + dy;
                        std::cout << "next" << nextX << " " << nextY << std::endl;

                        if (!isValidPosition(nextX, nextY)) {
                            std::cout << "La case suivante est hors limites." << std::endl;
                            return false;
                        }
                        if (dynamic_cast<terrainNu*>(checkCell) == nullptr) {
                            int nextIndex = nextX * COL + nextY;
                            unitObstacle* nextCell = board[nextIndex]->operator->();

                            if (dynamic_cast<terrainNu*>(nextCell) == nullptr) {
                                std::cout << "La case suivante est occupée." << std::endl;
                                return false;
                            }
                        }
                    }

                    std::cout << "COST" << totalCost << std::endl;
                    if (totalCost > remainingMoves)
                        return false;

                    if (!validateMove(currentX, currentY, dx * i, dy * i))
                        return false;
                }

                board[currentX * COL + currentY]->operator()();

                int newX = currentX + (dx * steps);
                int newY = currentY + (dy * steps);

                selectedUnit->operator()(newX, newY);

                board[newX * COL + newY]->operator=(selectedUnit);
                board[newX * COL + newY]->operator()(*currentPlayer);

                remainingMoves -= totalCost;
                std::pair<int, int> newPos = {newX, newY};
                usedMoves[newPos] = remainingMoves;

                game->updateVisionFields(*currentPlayer, selectedUnit);

                return true;

            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de l'exécution du mouvement : " << e.what() << std::endl;
                return false;
            }
        }

        void resetUnitMoves() {
            unitMovesRemaining.clear();
            std::vector<unite*> units = currentPlayer->operator*();
            for (std::vector<unite*>::iterator it = units.begin(); it != units.end(); ++it) {
                unite* unit = *it;
                unitMovesRemaining[unit] = unit->getMaximalMove();
            }
        }

    public:
        explicit TurnManager(kaptureGame<ROW, COL>* g)
        : board(g->getBoard()), game(g), currentPlayer(nullptr), selectedUnit(nullptr), remainingMoves(0) {
            registerCommands();
        }

        void startTurn(joueur& player) {
            currentPlayer = &player;
            game->setActivePlayer(currentPlayer);

            if (!currentPlayer) {
                throw std::runtime_error("Joueur invalide");
            }

            auto playerUnits = *player;
            if (playerUnits.empty())
                throw std::runtime_error("Pas d'unités disponibles pour le joueur");

            usedMoves.clear();
            selectedUnit = nullptr;
            remainingMoves = 0;
        }

        unite* getSelectedUnit() const {
            return selectedUnit;
        }

        bool processCommand(const std::string& input) {
            std::istringstream iss(input);
            std::string commandName;
            iss >> commandName;

            auto cmdIt = std::find_if(commands.begin(), commands.end(),
                [&commandName](const auto& cmd) { return cmd->matches(commandName); });

            if (cmdIt == commands.end())
                return false;


            std::vector<std::string> args;
            std::string arg;
            while (iss >> arg)
                args.push_back(arg);


            if (commandName == "end" || commandName == "fin")
                return false;


            if (commandName == "stop" || commandName == "s" || commandName == "next")
                return nextUnit();

            return executeMove(args);
        }

        bool nextUnit() {
            selectedUnit = nullptr;
            return true;
        }

        int getRemainingMoves() const {
            return remainingMoves;
        }

        TurnManager<ROW,COL>& selectUnit(unite* unit) {
            selectedUnit = unit;
            if (selectedUnit) {
                std::pair<int, int> pos = {selectedUnit->getCurrentPosX(), selectedUnit->getCurrentPosY()};

                if (usedMoves.find(pos) == usedMoves.end()) {
                    remainingMoves = selectedUnit->getMaximalMove();
                    usedMoves[pos] = remainingMoves;
                } else {
                    remainingMoves = usedMoves[pos];
                }
            }
            return *this;
        }
    };
}

#endif
