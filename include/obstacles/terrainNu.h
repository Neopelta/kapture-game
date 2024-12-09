#ifndef TERRAINNU_H
#define TERRAINNU_H

#include "obstacle.h"

namespace kpt {
    class terrainNu : public obstacle {
    public:
        terrainNu();
        ~terrainNu() override = default;

        std::string asciiArtPrint() override;
        terrainNu* clone() const override;
    };
}


#endif
