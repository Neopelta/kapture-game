#ifndef KAPTUREGAME_H
#define KAPTUREGAME_H

#include <algorithm>
#include <complex>
#include <fstream>
#include <list>

#include "plateau.h"
#include <stdexcept>

#include "../uniteObstacleFactory.h"
#include "../obstacles/foret.h"
#include "../obstacles/riviere.h"
#include "../obstacles/terrainNu.h"
#include "../units/eclaireur.h"

namespace kpt {
    template<short unsigned int row, short unsigned int col>
    class kaptureGame {
        static kaptureGame *instance;
        short unsigned int currentNbTurns;
        plateau<row, col> board;
        std::vector<joueur> players;

        kaptureGame<row, col>(short unsigned int nbPlayers) : currentNbTurns(0), board() {
            for (short unsigned int i = 0; i < nbPlayers; ++i)
                players.emplace_back();

            board(players);
        }

        static short unsigned int nextPowerOf2(unsigned int n) {
            if (n == 0)
                return 1;

            short unsigned int currentConnexite = 1;
            const short unsigned int maxOfConnexities = 8;

            --n;
            while (currentConnexite != maxOfConnexities) {
                n |= n >> currentConnexite;
                currentConnexite *= 2;
            }
            return n + 1;
        }

        kaptureGame<row, col> &generate(std::vector<std::pair<short, short> > &offsets, short distance, short unsigned int playerIndex) {
            for (short dx = -distance; dx <= distance; ++dx) {
                for (short dy = -distance; dy <= distance; ++dy) {
                    if (dx == 0 && dy == 0)
                        continue;
                    if (std::abs(dx) == distance || std::abs(dy) == distance) {
                        short newDx = (playerIndex % 2 != 0) ? dx : -dx;
                        short newDy = (playerIndex % 2 != 0) ? dy : -dy;
                        offsets.emplace_back(newDx, newDy);
                    }
                }
            }

            return *this;
        }

        std::vector<std::pair<short, short> > generateOffsets(short unsigned int maxUnits, short unsigned int playerIndex) {
            std::vector<std::pair<short, short> > offsets;

            for (short distance = 1; offsets.size() < maxUnits; ++distance)
                generate(offsets, distance, playerIndex);

            return offsets;
        }

        kaptureGame<row, col> &initializeForPlayer(joueur &p, short unsigned int flagIndex, short unsigned int playerIndex) {
            drapeau flag = !p;
            flag.operator()({flagIndex / col, flagIndex % col});
            flag.operator^({flagIndex / col, flagIndex % col});
            p.operator()(flag);
            board[flagIndex]->operator=(&flag);
            board[flagIndex]->operator()(p);

            // generates all offset depending on the number of units
            const std::vector<std::pair<short, short> > offsets = generateOffsets(
                nextPowerOf2((*p).size()), playerIndex);

            short unsigned int i = 0;
            for (unite *u: *p) {
                const std::pair<short, short> &delta = offsets.at(i);

                // calculates the new position of the unit, adjacent to the flag.
                const short int newRow = (flagIndex / col) + delta.first;
                const short int newCol = (flagIndex % col) + delta.second;

                if (newRow >= 0 && newRow < row && newCol >= 0 && newCol < col) {
                    const short unsigned int uniteIndex = newRow * col + newCol;
                    u->operator^({uniteIndex / col, uniteIndex % col});
                    u->operator&();
                    board[uniteIndex]->operator=(u);
                    board[uniteIndex]->operator()(p);
                }
                ++i;
            }
            return *this;
        }


        kaptureGame<row, col> &updateVisionFieldUnit(joueur &p, unite *u, bool isAlreadyVisited) {
            std::vector<std::pair<short, short>> spaces;
            if (isAlreadyVisited)
                spaces = {
                    {-2, 0}, {0, -2}, {2, 0}, {0, 2},
                    {-1, -1}, {-1, 0}, {-1, 1},
                    {0, -1}, {0, 1}, {1, -1}, {1, 0},
                    {1, 1}
                };
            else
                spaces = {
                    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
                };

            std::pair<short unsigned int, short unsigned int> coords = !(*u);
            for (const std::pair<short, short> &delta: spaces) {
                const short unsigned newX = coords.first + delta.first;
                const short unsigned newY = coords.second + delta.second;

                if (newX < row && newY < col)
                    board[newX * col + newY]->operator()(p);
            }
            return *this;
        }

        bool operator()(joueur &p, unite *u) {
            const std::pair<short, short> spaces[] = {
                {-1, 0}, {1, 0}, {0, -1}, {0, 1}
            };

            bool isVisible = true;
            std::pair<short unsigned int, short unsigned int> coords = !(*u);
            for (const std::pair<short, short> &delta: spaces) {
                const short unsigned newX = coords.first + delta.first;
                const short unsigned newY = coords.second + delta.second;

                if (newX < row && newY < col)
                    isVisible &= board[newX * col + newY]->isVisible(p);
            }

            return isVisible;
        }

    public:
        // Only one instance, this why we don't have the canonical form class
        static kaptureGame<row, col> *getInstance(short unsigned int nbPlayers) {
            if (instance == nullptr)
                instance = new kaptureGame<row, col>(nbPlayers);
            return instance;
        }

        kaptureGame<row, col> &operator++() {
            ++currentNbTurns;
            return *this;
        }

        kaptureGame<row, col> &saveGame(const std::string &filename) {
            std::fstream file(filename);

            for (cellule *c : *board) {
                file << "coords : (" << (**c).first << "," << (**c).second << ")\n";

                for (const std::pair<joueur, bool> pair : !(*c)) {
                    joueur key = pair.first;
                    bool value = pair.second;
                    file << "playerId: " << key() << "\n";
                    file << "visible: " << value << "\n";

                    bool unitWritten = true;
                    for (unite *u : *key) {
                        if (**u != nullptr)
                            std::cout << "passs" << std::endl;

                        const joueur& p = key;
                        if (u->asciiArtPrint() == c->operator->()->asciiArtPrint() && c->isVisible(p) && unitWritten) {
                            file << "units: " << c->operator->()->asciiArtPrint() << "\n";
                            file << "in: " << key() << "\n";
                            unitWritten = false;
                            drapeau d = !key;
                        }
                    }
                }
                file << "\n";
            }
            file.close();
            return *this;
        }

        kaptureGame<row, col> &updateVisionFields(joueur &p) {
            for (unite* u : *p)
                updateVisionFieldUnit(p, u, operator()(p, u));

            return *this;
        }

        kaptureGame<row, col>* loadGame(const std::string& filename) {
            std::ifstream file(filename);
            if (!file.is_open())
                throw std::runtime_error("Impossible d'ouvrir le fichier");

            for (joueur &p: players)
                p.resetUnits();

            std::string line;
            std::vector<std::string> lines;
            while (std::getline(file, line) && !line.empty())
                lines.push_back(line);

            for (short unsigned int i = 0; i < row; ++i) {
                std::istringstream iss(lines[i]);
                std::string cell;
                for (short unsigned int j = 0; j < col; ++j) {
                    iss >> cell;
                    unitObstacle* uo = uniteObstacleFactory::createEntity(cell, {i,j});

                    board[i* col + j]->operator=(uo);

                    if (!cell.substr(1, 1).empty()) {
                        int playerIndex = std::stoi(cell.substr(1, 1)) - 1;
                        joueur &p = players.at(playerIndex);
                        if (cell.substr(0, 1) == "D")
                            p.operator()(*dynamic_cast<drapeau*>(uo));
                        else
                            p.insertUnit(dynamic_cast<unite*>(uo));
                        board[i * col + j]->operator()(p);
                    }

                }
            }

            file.close();
            std::cout << "Le jeu a été chargé : " << filename << std::endl;

            return instance;
        }

        plateau<row, col> operator*() const {
            return board;
        }

        std::vector<joueur> operator()() const {
            return players;
        }

        kaptureGame<row, col> &initializeGame() {
            const size_t numberOfUnits = (*players.front()).size(); // each player has the same number of units
            const short unsigned int maximalOfConnexities = 8;

            const std::pair<short unsigned int, short unsigned int> corners[] = {
                std::make_pair(0, 0),
                std::make_pair(1, 1),
                std::make_pair(1, 0),
                std::make_pair(0, 1)
            };

            // calculates the number of squares with the flag for center to set up all player's units
            const short unsigned int padding = 1 + static_cast<short unsigned int>(std::ceil(numberOfUnits / maximalOfConnexities));
            // calculates the space between the flag and the board in function of the padding
            const short unsigned int offset = 2 * padding + 1;

            short unsigned int playerIndex = 0;

            std::for_each(players.begin(), players.end(), [&](joueur &player) {
                const std::pair<short unsigned int, short unsigned int> corner = corners[playerIndex % 4];
                // calculates the position of the flag
                const short unsigned int flagIndex = (corner.first * (row - offset) + padding) * col + corner.second * (col - offset) + padding;

                initializeForPlayer(player, flagIndex, playerIndex + 1);
                ++playerIndex;
            });

            return *this;
        }

        kaptureGame<row, col> &handleFight(unite *u1, unite *u2) {
            const std::pair<short unsigned int, short unsigned int> previousU1Coord = !(*u1);
            const std::pair<short unsigned int, short unsigned int> previousU2Coord = !(*u2);

            const unitInteraction interaction = u1->fight(*u2);

            const std::pair<short unsigned int, short unsigned int> currentU1Coord = !(*u1);
            const std::pair<short unsigned int, short unsigned int> currentU2Coord = !(*u2);

            if (interaction == WON) {
                u1->operator&();
            }
            else if (interaction == LOST)
                u2->operator&();
            else {
                board[previousU1Coord.first * col + previousU1Coord.second]->operator()();
                board[previousU2Coord.first * col + previousU2Coord.second]->operator()();
                board[currentU1Coord.first * col + currentU1Coord.second]->operator=(u1);
                board[currentU2Coord.first * col + currentU2Coord.second]->operator=(u2);
            }

            return *this;
        }

        kaptureGame<row, col>& assignFlag(joueur &player, unite *u) {
            drapeau d = !player;
            const std::pair<short unsigned int, short unsigned int> coord = !(*u);
            const std::pair<short unsigned int, short unsigned int> flagCoord = !d;

            u->takeFlag(d);
            d.operator()(true);

            board[coord.first * col + coord.second]->operator=(u); // reassignment to avoid copy
            board[flagCoord.first * col + flagCoord.second]->operator()(); // the cell that contained the flag must be free
            player.operator()(d); // same

            return *this;
        }

        template<short unsigned int X, short unsigned int Y>
        friend std::ostream &operator<<(std::ostream &os, kaptureGame<X, Y> &game);
    };

    template<short unsigned int row, short unsigned int col>
    kaptureGame<row, col> *kaptureGame<row, col>::instance = nullptr;

    template<short unsigned int X, short unsigned int Y>
    std::ostream &operator<<(std::ostream &os, kaptureGame<X, Y> &game) {
        short i = 1;
        for (joueur &p: game.players) {
            short unsigned int ind = 1;
            os << "Affichage du plateau pour le joueur " << i << std::endl;

            std::vector<cellule*> cells = *(game.board);
            std::for_each(cells.begin(), cells.end(), [&ind, &os, &p](const cellule *cell) {
                if (cell->isVisible(p))
                    os << cell->operator->()->asciiArtPrint() << " ";
                else
                    os << cell->operator->()->asciiArtPrintNotVisible() << " ";
                if (ind % Y == 0)
                    os << std::endl;
                ++ind;
            });

            os << std::endl;
            ++i;
        }
        return os;
    }
}

#endif
