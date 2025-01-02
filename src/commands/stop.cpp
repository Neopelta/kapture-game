#include "../../include/commands/stop.h"

#include <stdexcept>

namespace kpt {
    StopCommand::StopCommand()
        : command("stop", {"s", "next"}, "Passe à l'unité suivante") {
    }

    void StopCommand::execute(const std::vector<std::string>& args) {
        if (!args.empty()) {
            throw std::invalid_argument("La commande stop ne prend pas d'arguments");
        }
        // La logique de passage à l'unité suivante est gérée par le TurnManager
    }
}
