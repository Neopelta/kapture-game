#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../unitObstacle.h"


namespace kpt {
    class obstacle : public unitObstacle {

    private:
        short unsigned int costToQuit;
    public:
        obstacle();
        virtual ~obstacle() = default;
        short unsigned int operator*() const;
        obstacle &operator()(short unsigned int value);
        virtual obstacle& asciiArtPrint() = 0;
    };
}


#endif
