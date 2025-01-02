#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <unordered_map>
#include <optional>
#include "../commands/command.h"

namespace kpt {
    class MoveCommand : public command {
    private:
        static const std::unordered_map<std::string, std::string> directionAliases;
        static const std::unordered_map<std::string, std::pair<int, int>> directionDeltas;

    public:
        MoveCommand() : command("move",
                              {"mv"},
                              "Déplace une unité dans une direction donnée") {}

        static std::optional<std::pair<int, int>> getDirectionDelta(std::string direction) {
            // Convertir l'alias en direction standard si nécessaire
            if (directionAliases.count(direction)) {
                direction = directionAliases.at(direction);
            }

            // Vérifier si la direction est valide
            if (!directionDeltas.count(direction)) {
                return std::nullopt;
            }

            return directionDeltas.at(direction);
        }

        void execute(const std::vector<std::string>& args) override {
            if (args.size() != 2) {
                throw std::invalid_argument("Usage: move/mv <steps> <direction>");
            }

            // La validation et l'exécution réelle sont gérées par le TurnManager
        }
    };

    // Initialisation des alias de direction
    const std::unordered_map<std::string, std::string> MoveCommand::directionAliases = {
        {"n", "north"},
        {"s", "south"},
        {"e", "east"},
        {"w", "west"},

        {"nw", "northwest"},
        {"ne", "northeast"},
        {"sw", "southwest"},
        {"se", "southeast"},
    };

    // Initialisation des deltas de direction
    const std::unordered_map<std::string, std::pair<int, int>> MoveCommand::directionDeltas = {
        {"north",     {-1, 0}},
        {"south",     {1, 0}},
        {"east",      {0, 1}},
        {"west",      {0, -1}},
        {"northwest", {-1, -1}},
        {"northeast", {-1, 1}},
        {"southwest", {1, -1}},
        {"southeast", {1, 1}},
    };
}

#endif