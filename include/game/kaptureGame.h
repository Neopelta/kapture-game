#ifndef KAPTUREGAME_H
#define KAPTUREGAME_H

#include <algorithm>
#include <complex>
#include <fstream>
#include <list>

#include "plateau.h"
#include <stdexcept>

#include "../obstacles/foret.h"
#include "../obstacles/riviere.h"
#include "../units/eclaireur.h"

namespace kpt {
    template<short unsigned int row, short unsigned int col>
    class TurnManager;

    template<short unsigned int row, short unsigned int col>
    class kaptureGame {
        friend class TurnManager<row, col>;
    private:
        static kaptureGame *instance;
        short unsigned int currentNbTurns;
        plateau<row, col> board;
        std::list<joueur> players;
        joueur* activePlayer;

        kaptureGame<row, col>(short unsigned int nbPlayers)
        : currentNbTurns(0), board(), activePlayer(nullptr) {
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
            board[flagIndex] = &flag;
            board[flagIndex](p);

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
                    board[uniteIndex] = u;
                    board[uniteIndex](p);

                    u->setPosition(newRow, newCol);
                }

                ++i;
            }
            return *this;
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
            // Ouvre le fichier en mode écriture (écrase le contenu existant)
            std::ofstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Impossible d'ouvrir le fichier pour la sauvegarde");
            }

            // Sauvegarde les informations générales du jeu
            file << "NbTours:" << currentNbTurns << "\n";
            file << "NbJoueurs:" << players.size() << "\n\n";

            // Pour chaque cellule du plateau
            for (size_t i = 0; i < row * col; ++i) {
                cellule &c = board[i];
                file << "Cellule:" << i << "\n";
                file << "Coords:(" << (*c).first << "," << (*c).second << ")\n";

                // Sauvegarde le type de terrain
                file << "Terrain:" << c->asciiArtPrint() << "\n";

                // Pour chaque joueur, sauvegarde la visibilité
                for (const auto& [player, isVisible] : !c) {
                    file << "Joueur:" << player() << "\n";
                    file << "Visible:" << (isVisible ? "1" : "0") << "\n";

                    // Si la cellule est visible pour ce joueur
                    if (isVisible) {
                        // Vérifie si une unité du joueur est présente sur cette cellule
                        for (unite* unit : *player) {
                            if (unit && unit->asciiArtPrint() == c->asciiArtPrint()) {
                                file << "Unite:" << unit->asciiArtPrint() << "\n";

                                // Si l'unité porte un drapeau
                                if (unit->operator*() != nullptr) {
                                    file << "PorteDrapeau:1\n";
                                }

                                break;
                            }
                        }
                    }
                }
                file << "\n";
            }

            file.close();
            return *this;
        }
        std::list<joueur>& getPlayers() { return players; }
        plateau<row, col>& getBoard() { return board; }

        void setActivePlayer(joueur* player) {
            activePlayer = player;
        }

        static kaptureGame<row, col> loadGame(const std::string &filename) {
            throw std::invalid_argument("kaptureGame::loadGame()");
        }

        plateau<row, col> operator*() const {
            return board;
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


        template<short unsigned int X, short unsigned int Y>
        friend std::ostream &operator<<(std::ostream &os, kaptureGame<X, Y> &game);
    };

    template<short unsigned int row, short unsigned int col>
    kaptureGame<row, col> *kaptureGame<row, col>::instance = nullptr;

    template<short unsigned int X, short unsigned int Y>
    std::ostream &operator<<(std::ostream &os, kaptureGame<X, Y> &game) {
        if (!game.activePlayer) {
            os << "Erreur: Aucun joueur actif" << std::endl;
            return os;
        }

        os << "Affichage du plateau pour le joueur " << game.activePlayer->operator()() << std::endl;

        std::vector<cellule> cells = *(game.board);
        short unsigned int ind = 1;
        std::for_each(cells.begin(), cells.end(), [&ind, &os, &activePlayer = game.activePlayer](const cellule &cell) {
            if (cell.isVisible(*activePlayer)) {
                os << cell->asciiArtPrint() << " ";
            } else {
                os << unitObstacle::asciiArtPrintNotVisible() << " ";
            }
            if (ind % Y == 0) {
                os << std::endl;
            }
            ++ind;
        });

        os << std::endl;
        return os;
    }
}

#endif