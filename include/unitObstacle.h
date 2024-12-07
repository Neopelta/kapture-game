#ifndef UNITOBSTACLE_H
#define UNITOBSTACLE_H

namespace kpt {
    class unitObstacle {
    public:
        virtual ~unitObstacle() = default;
        virtual unitObstacle &asciiArtPrint() = 0;
    };
}

#endif
