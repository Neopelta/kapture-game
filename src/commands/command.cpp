#include "../../include/commands/command.h"

namespace kpt {
    command::command(const std::string& cmdName,
                    const std::vector<std::string>& cmdAliases,
                    const std::string& cmdDescription) {
        name = std::make_unique<std::string>(cmdName);
        aliases = std::make_unique<std::vector<std::string>>(cmdAliases);
        description = std::make_unique<std::string>(cmdDescription);
    }

    command::command(const command& other) {
        name = std::make_unique<std::string>(*other.name);
        aliases = std::make_unique<std::vector<std::string>>(*other.aliases);
        description = std::make_unique<std::string>(*other.description);
    }

    command& command::operator=(const command& other) {
        if (this != &other) {
            name = std::make_unique<std::string>(*other.name);
            aliases = std::make_unique<std::vector<std::string>>(*other.aliases);
            description = std::make_unique<std::string>(*other.description);
        }
        return *this;
    }
}