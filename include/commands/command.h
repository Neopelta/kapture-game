#ifndef KAPTURE_COMMAND_H
#define KAPTURE_COMMAND_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

namespace kpt {
    class command {
    protected:
        std::unique_ptr<std::string> name;
        std::unique_ptr<std::vector<std::string>> aliases;
        std::unique_ptr<std::string> description;

    public:
        command(const std::string& cmdName,
               const std::vector<std::string>& cmdAliases,
               const std::string& cmdDescription);

        command(const command& other);
        command& operator=(const command& other);
        command(command&& other) = default;
        command& operator=(command&& other) = default;
        virtual ~command() = default;

        virtual void execute(const std::vector<std::string>& args) = 0;

        const std::string& operator*() const {
            return *name;
        }

        const std::vector<std::string>& operator!() const {
            return *aliases;
        }

        const std::string& operator->() const {
            return *description;
        }

        bool matches(const std::string& input) const {
            return input == *name || std::find(aliases->begin(), aliases->end(), input) != aliases->end();
        }    };
}

#endif