#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../unitObstacle.h"


namespace kpt {
    class obstacle : public unitObstacle {
        short unsigned int costToQuit;
    public:
        obstacle();
        virtual ~obstacle() = default;
        short unsigned int operator*() const;
        obstacle &operator()(short unsigned int value);
        std::string asciiArtPrint() override = 0;
        obstacle* clone() const override = 0;
    };
}


#endif
