#ifndef KAPTUREGAME_H
#define KAPTUREGAME_H

#include <algorithm>
#include <complex>
#include <fstream>
#include <list>
#include <queue>
#include <set>
#include <random>
#include <stdexcept>

#include "plateau.h"
#include "../uniteObstacleFactory.h"
#include "../obstacles/foret.h"
#include "../obstacles/riviere.h"
#include "../obstacles/terrainNu.h"
#include "../units/eclaireur.h"

namespace kpt {
    template<short unsigned int row, short unsigned int col>
    class TurnManager;

    template<short unsigned int row, short unsigned int col>
    class kaptureGame {
        friend class TurnManager<row, col>;

        static kaptureGame *instance;
        short unsigned int currentNbTurns;
        plateau<row, col> board;
        std::vector<joueur> players;
        joueur* activePlayer;

        kaptureGame<row, col>(short unsigned int nbPlayers)
        : currentNbTurns(0), board(), activePlayer(nullptr) {
            for (short unsigned int i = 0; i < nbPlayers; ++i)
                players.emplace_back();

            board.operator()(players);

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

            const std::vector<std::pair<short, short> > offsets = generateOffsets(
                nextPowerOf2((*p).size()), playerIndex);

            short unsigned int i = 0;
            for (unite *u: *p) {
                const std::pair<short, short> &delta = offsets.at(i);

                const short int newRow = (flagIndex / col) + delta.first;
                const short int newCol = (flagIndex % col) + delta.second;

                if (newRow >= 0 && newRow < row && newCol >= 0 && newCol < col) {
                    const short unsigned int uniteIndex = newRow * col + newCol;
                    u->operator^({uniteIndex / col, uniteIndex % col});
                    u->reset();
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

        std::pair<short unsigned int, short unsigned int> findClosestFreeCell(short unsigned int startX, short unsigned int startY) {
            std::queue<std::pair<short unsigned int, short unsigned int>> q;
            std::set<std::pair<short unsigned int, short unsigned int>> visited;

            q.emplace(startX, startY);
            visited.insert({startX, startY});

            std::vector<std::pair<int, int>> directions = {
                {0, 1}, {1, 0}, {0, -1}, {-1, 0},  // Droite, Bas, Gauche, Haut
                {1, 1}, {1, -1}, {-1, 1}, {-1, -1} // Diagonales
            };

            while (!q.empty()) {
                auto coord = q.front();
                q.pop();

                short unsigned int x = coord.first;
                short unsigned int y = coord.second;

                const cellule *currentCell = board[x * col + y];
                if (dynamic_cast<terrainNu*>(currentCell->operator->()) != nullptr) {
                    return {x, y};
                }

                for (const auto& dir : directions) {
                    short unsigned int newX = x + dir.first;
                    short unsigned int newY = y + dir.second;

                    if (newX < row && newY < col && visited.find({newX, newY}) == visited.end()) {
                        q.push({newX, newY});
                        visited.insert({newX, newY});
                    }
                }
            }

            return {startX, startY};
        }
        std::pair<short unsigned int, short unsigned int> findRandomAdjacentFreeCell(short unsigned int startX, short unsigned int startY) {
            std::vector<std::pair<short unsigned int, short unsigned int>> freeCells;

            std::vector<std::pair<int, int>> directions = {
                {-1, -1}, {-1, 0}, {-1, 1},
                {0, -1},           {0, 1},
                {1, -1},  {1, 0},  {1, 1}
            };

            std::random_device rd;
            std::mt19937 gen(rd());
            std::shuffle(directions.begin(), directions.end(), gen);

            for (const auto& dir : directions) {
                short unsigned int newX = startX + dir.first;
                short unsigned int newY = startY + dir.second;

                if (newX < row && newY < col) {
                    const cellule* currentCell = board[newX * col + newY];
                    if (dynamic_cast<terrainNu*>(currentCell->operator->()) != nullptr) {
                        freeCells.push_back({newX, newY});
                    }
                }
            }

            if (!freeCells.empty()) {
                int randomIndex = rand() % freeCells.size();
                return freeCells[randomIndex];
            }

            return findClosestFreeCell(startX, startY);
        }

        void checkFlags() {
            for (joueur& player : players) {
                drapeau flag = !player;
                if (flag.isOnGround() && flag.shouldReturnToBase(currentNbTurns)) {
                    flag.initCurrentCoord();
                    player(flag);
                    std::cout << "\033[1;35m" << "Le drapeau du joueur " << player()
                              << " est retourné à sa base !" << "\033[0m" << std::endl;
                }
            }
        }

        void handleFlagDrop(const unite* unit) {
            if (unit->operator*() != nullptr) {
                drapeau* flag = unit->operator*();
                if (flag != nullptr) {
                    flag->drop(currentNbTurns);
                }
                if (flag != nullptr) {
                    flag->drop(currentNbTurns);
                } else {
                    std::cerr << "[ERROR] Tentative d'accès à un drapeau null dans handleFlagDrop" << std::endl;
                }
                std::pair<short unsigned int, short unsigned int> unitPos = !(*unit);
                auto dropPos = findRandomAdjacentFreeCell(unitPos.first, unitPos.second);

                flag->operator()(dropPos);
                board[dropPos.first * col + dropPos.second]->operator=(flag);

                std::cout << "\033[1;33m" << "Le drapeau a été lâché ! Il est tombé en position ["
                          << dropPos.first << "," << dropPos.second << "]" << std::endl
                          << "Il retournera à sa base dans 2 tours s'il n'est pas récupéré."
                          << "\033[0m" << std::endl;
            }
        }

        bool canCaptureFlag(const unite* unit, const drapeau* flag) const {
            std::pair<short unsigned int, short unsigned int> unitPos = !(*unit);
            std::pair<short unsigned int, short unsigned int> flagPos = !(*flag);

            return (std::abs(static_cast<int>(unitPos.first) - static_cast<int>(flagPos.first)) <= 1) &&
                   (std::abs(static_cast<int>(unitPos.second) - static_cast<int>(flagPos.second)) <= 1) &&
                   flag->canBePickedUpBy(unit);
        }

        bool isInitialFlagPosition(int x, int y) const {
            for (const joueur& player : players) {
                const drapeau flag = !player;
                const auto initialPos = flag.pos();
                if (initialPos.first == x && initialPos.second == y) {
                    return true;
                }
            }
            return false;
        }

    public:
        static kaptureGame<row, col> *getInstance(short unsigned int nbPlayers) {
            if (instance == nullptr)
                instance = new kaptureGame<row, col>(nbPlayers);
            return instance;
        }

        kaptureGame<row, col> &operator++() {
            ++currentNbTurns;
            checkFlags();
            return *this;
        }

        kaptureGame<row, col> &saveGame(const std::string &filename) {
            throw std::runtime_error("kaptureGame<row, col>::saveGame");
        }

        kaptureGame<row, col> &updateVisionFields(joueur &p, unite*u) {
            updateVisionFieldUnit(p, u, operator()(p, u));
            return *this;
        }
        void setActivePlayer(joueur* player) {
            activePlayer = player;
        }
        std::vector<joueur>& getPlayers() { return players; }
        plateau<row, col>& getBoard() { return board; }

        kaptureGame<row, col>* loadGame(const std::string& filename) {
            std::ifstream file(filename);
            if (!file.is_open())
                throw std::runtime_error("Impossible d'ouvrir le fichier");
            for (joueur &p: players)
                p.resetUnits();

            std::string line;
            std::vector<std::string> lines;

            std::cout << "Chargement de la carte :" << std::endl;
            for (const auto& line : lines) {
                std::cout << line << std::endl;
            }

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

        unite* getUnitAt(joueur &p, const std::pair<short unsigned int, short unsigned int> &coords) {
            if (!plateau<row, col>::isValidPosition(coords.first, coords.second)) {
                return nullptr;
            }

            cellule *cell = board[coords.first * col + coords.second];
            unite *u = dynamic_cast<unite*>(cell->operator->());
            if (!u) return nullptr;

            return p.operator()(u) ? u : nullptr;
        }

        plateau<row, col> operator*() const {
            return board;
        }

        std::vector<joueur> operator()() const {
            return players;
        }

        kaptureGame<row, col> &initializeGame() {
            const size_t numberOfUnits = (*players.front()).size();
            const short unsigned int maximalOfConnexities = 8;

            const std::pair<short unsigned int, short unsigned int> corners[] = {
                std::make_pair(0, 0),
                std::make_pair(1, 1),
                std::make_pair(1, 0),
                std::make_pair(0, 1)
            };

            const short unsigned int padding = 1 + static_cast<short unsigned int>(std::ceil(numberOfUnits / maximalOfConnexities));
            const short unsigned int offset = 2 * padding + 1;

            short unsigned int playerIndex = 0;

            std::for_each(players.begin(), players.end(), [&](joueur &player) {
                const std::pair<short unsigned int, short unsigned int> corner = corners[playerIndex % 4];
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
                handleFlagDrop(u2);
                board[currentU1Coord.first * col + currentU1Coord.second]->operator()();
                u1->reset();

                const std::pair<short unsigned int, short unsigned int> spawnCoords = !(*u1);
                short unsigned int spawnX = spawnCoords.first;
                short unsigned int spawnY = spawnCoords.second;

                const cellule *spawnUnitCell = board[spawnX * col + spawnY];
                if (dynamic_cast<terrainNu*>(spawnUnitCell->operator->()) == nullptr) {
                    const std::pair<short unsigned int, short unsigned int> freeCoords = findClosestFreeCell(spawnX, spawnY);
                    spawnX = freeCoords.first;
                    spawnY = freeCoords.second;
                }

                board[spawnX * col + spawnY]->operator=(u1);
            }
            else if (interaction == LOST) {
                handleFlagDrop(u1);
                board[currentU2Coord.first * col + currentU2Coord.second]->operator()();
                u2->reset();

                const std::pair<short unsigned int, short unsigned int> spawnCoords = !(*u2);
                short unsigned int spawnX = spawnCoords.first;
                short unsigned int spawnY = spawnCoords.second;

                const cellule *spawnUnitCell = board[spawnX * col + spawnY];
                if (dynamic_cast<terrainNu*>(spawnUnitCell->operator->()) == nullptr) {
                    const std::pair<short unsigned int, short unsigned int> freeCoords = findClosestFreeCell(spawnX, spawnY);
                    spawnX = freeCoords.first;
                    spawnY = freeCoords.second;

                    u2->operator()(spawnX, spawnY);
                }

                board[spawnX * col + spawnY]->operator=(u2);
            }
            else {
                board[previousU1Coord.first * col + previousU1Coord.second]->operator()();
                board[previousU2Coord.first * col + previousU2Coord.second]->operator()();
                board[currentU1Coord.first * col + currentU1Coord.second]->operator=(u1);
                board[currentU2Coord.first * col + currentU2Coord.second]->operator=(u2);
            }

            return *this;
        }

        kaptureGame<row, col>& assignFlag(joueur &player, unite *u) {
            drapeau& d = player.getFlag();
            const std::pair<short unsigned int, short unsigned int> coord = !(*u);
            const std::pair<short unsigned int, short unsigned int> flagCoord = !d;

            u->takeFlag(d);

            d.operator()(true);

            board[coord.first * col + coord.second]->operator=(u);
            board[flagCoord.first * col + flagCoord.second]->operator()();
            player.operator()(d);

            std::cout << "\033[1;35m" << "Le drapeau du joueur " << player()
                      << " a été capturé par une unité adverse !" << "\033[0m" << std::endl;

            return *this;
        }

        unite *operator()(unite *u) {
            const std::pair<short, short> spaces[] = {
                {-1, -1}, {-1, 0}, {-1, 1},
                {0, -1}, {0, 1},
                {1, -1}, {1, 0}, {1, 1},
            };

            unite *result = nullptr;
            std::pair<short unsigned int, short unsigned int> coords = !(*u);

            for (const std::pair<short, short> &delta: spaces) {
                const short unsigned newX = coords.first + delta.first;
                const short unsigned newY = coords.second + delta.second;

                if (newX < row && newY < col) {
                    cellule *adjacentCell = board[newX * col + newY];
                    unite *unit = dynamic_cast<unite*>(adjacentCell->operator->());

                    if (unit) {
                        for (joueur &player: players) {
                            if (player.operator()(u) && !player.operator()(unit))
                                result = unit;
                        }
                    }
                }
            }

            return result;
        }

        bool checkVictoryCondition(const joueur& player) const {

            const drapeau& playerFlag = !player;
            auto basePos = playerFlag.pos();

            const std::vector<unite*>& playerUnits = *player;
            for (unite* unit : playerUnits) {

                auto unitPos = !(*unit);
                if (unit->operator*() != nullptr) {
                    if (unitPos.first == basePos.first && unitPos.second == basePos.second) {
                        std::cout << "\033[1;32m[VICTOIRE] L'unité avec le drapeau est sur sa base !\033[0m" << std::endl;
                        return true;
                    }
                }
            }

            return false;
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

        std::vector<cellule*> cells = *(game.board);
        short unsigned int ind = 1;
        std::for_each(cells.begin(), cells.end(),
            [&ind, &os, &game, &activePlayer = game.activePlayer](const cellule *cell) {
                int x = (ind - 1) / Y;
                int y = (ind - 1) % Y;

                if (cell->isVisible(*activePlayer)) {
                    bool isFlag = dynamic_cast<const drapeau*>(cell->operator->()) != nullptr;
                    if (game.isInitialFlagPosition(x, y) && !isFlag) {
                        os << "\033[48;5;124mX\033[0m ";
                    } else {
                        os << cell->operator->()->asciiArtPrint() << " ";
                    }
                } else {
                    os << cell->operator->()->unitObstacle::asciiArtPrintNotVisible() << " ";
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
