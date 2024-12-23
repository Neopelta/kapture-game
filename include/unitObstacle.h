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
        virtual std::string asciiArtPrintNotVisible();
        virtual ~unitObstacle() = default;
        virtual std::string asciiArtPrint() = 0;
        virtual unitObstacle* clone() const = 0;
        unitObstacle& operator^(const std::pair<short unsigned int, short unsigned int>& coords);
        bool operator==(const unitObstacle *uo) const;
    };
}

#endif
