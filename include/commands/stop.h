#ifndef STOP_COMMAND_H
#define STOP_COMMAND_H

#include "../commands/command.h"

namespace kpt {
    class StopCommand : public command {
    public:
        StopCommand() : command("stop",
                              {"s", "next"},
                              "Passe à l'unité suivante") {}

        void execute(const std::vector<std::string>& args) override {
            if (!args.empty()) {
                throw std::invalid_argument("La commande stop ne prend pas d'arguments");
            }
        }
    };
}

#endif