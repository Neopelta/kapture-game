#ifndef END_TURN_COMMAND_H
#define END_TURN_COMMAND_H

#include "../commands/command.h"

namespace kpt {
    class EndTurnCommand : public command {
    public:
        EndTurnCommand() : command("end_turn",
                              {"end", "fin"},
                              "Termine le tour du joueur actuel") {}

        void execute(const std::vector<std::string>& args) override {
            if (!args.empty()) {
                throw std::invalid_argument("La commande end ne prend pas d'arguments");
            }
        }
    };
}

#endif