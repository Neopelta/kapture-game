#ifndef UNITEOBSTACLEFACTORY_H
#define UNITEOBSTACLEFACTORY_H

#include "unitObstacle.h"

namespace kpt {
    class uniteObstacleFactory {
    public:
        static unitObstacle* createEntity(const std::string &data, const std::pair<short unsigned int, short unsigned int> &pos);
    };
}



#endif
