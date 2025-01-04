#ifndef STOP_COMMAND_H
#define STOP_COMMAND_H

#include "command.h"

namespace kpt {
    class StopCommand : public command {
    public:
        StopCommand();
        void execute(const std::vector<std::string>& args) override;
    };
}

#endif