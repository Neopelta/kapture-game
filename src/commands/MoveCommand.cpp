#include "../../include/commands/MoveCommand.h"

#include <stdexcept>

namespace kpt {
    MoveCommand::MoveCommand()
        : command("move", {"mv"}, "Déplace une unité dans une direction donnée") {
    }

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

    std::optional<std::pair<int, int>> MoveCommand::getDirectionDelta(const std::string& direction) {
        std::string normalizedDirection = direction;

        // Convertir l'alias en direction standard si nécessaire
        if (directionAliases.count(direction)) {
            normalizedDirection = directionAliases.at(direction);
        }

        // Vérifier si la direction est valide
        if (!directionDeltas.count(normalizedDirection)) {
            return std::nullopt;
        }

        return directionDeltas.at(normalizedDirection);
    }

    void MoveCommand::execute(const std::vector<std::string>& args) {
        if (args.size() != 2) {
            throw std::invalid_argument("Usage: move/mv <steps> <direction>");
        }
    }
}
