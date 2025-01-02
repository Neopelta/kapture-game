#include "../../include/commands/EndTurnCommand.h"

#include <stdexcept>

namespace kpt {
    EndTurnCommand::EndTurnCommand()
        : command("end_turn", {"end", "fin"}, "Termine le tour du joueur actuel") {
    }

    void EndTurnCommand::execute(const std::vector<std::string>& args) {
        if (!args.empty()) {
            throw std::invalid_argument("La commande end_turn ne prend pas d'arguments");
        }
        // La logique de fin de tour est gérée par le TurnManager
    }
}
