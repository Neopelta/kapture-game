#ifndef UNITOBSTACLE_H
#define UNITOBSTACLE_H

namespace kpt {
    class unitObstacle {
    public:
        virtual ~unitObstacle() = default;
        virtual unitObstacle &asciiArtPrint() = 0;
        virtual unitObstacle* clone() const = 0;
    };
}

#endif
