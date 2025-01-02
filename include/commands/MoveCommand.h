#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <unordered_map>
#include <optional>
#include "command.h"

namespace kpt {
    class MoveCommand : public command {
    private:
        static const std::unordered_map<std::string, std::string> directionAliases;
        static const std::unordered_map<std::string, std::pair<int, int>> directionDeltas;

    public:
        MoveCommand();
        static std::optional<std::pair<int, int>> getDirectionDelta(const std::string& direction);
        void execute(const std::vector<std::string>& args) override;
    };
}

#endif