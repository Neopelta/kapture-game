#ifndef END_TURN_COMMAND_H
#define END_TURN_COMMAND_H

#include "command.h"

namespace kpt {
    class EndTurnCommand : public command {
    public:
        EndTurnCommand();
        void execute(const std::vector<std::string>& args) override;
    };
}

#endif