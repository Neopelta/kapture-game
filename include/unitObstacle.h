#ifndef UNITOBSTACLE_H
#define UNITOBSTACLE_H
#include <string>

namespace kpt {
    class unitObstacle {
    public:
        static std::string asciiArtPrintNotVisible();
        virtual ~unitObstacle() = default;
        virtual std::string asciiArtPrint() = 0;
        virtual unitObstacle* clone() const = 0;
    };
}

#endif
