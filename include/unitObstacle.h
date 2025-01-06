#ifndef UNITOBSTACLE_H
#define UNITOBSTACLE_H
#include <string>

namespace kpt {
    class unitObstacle {
    protected:
        short unsigned int initialPosX;
        short unsigned int initialPosY;
    public:
        unitObstacle();
        virtual std::string asciiArtPrintNotVisible() const;
        virtual ~unitObstacle() = default;
        virtual std::string asciiArtPrint() const = 0;
        virtual unitObstacle* clone() const = 0;
        virtual bool mustBeVisible() const = 0;
        unitObstacle& operator^(const std::pair<short unsigned int, short unsigned int>& coords);
        bool operator==(const unitObstacle *uo) const;
        std::pair<short unsigned int, short unsigned int> pos() const {
            return {initialPosX, initialPosY};
        }
    };
}

#endif
