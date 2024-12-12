#ifndef DRAPEAU_H
#define DRAPEAU_H
#include "../unitObstacle.h"

namespace kpt {
    class drapeau : public unitObstacle {
        short unsigned int currentPosX;
        short unsigned int currentPosY;

    public:
        drapeau();
        ~drapeau() override = default;

        std::string asciiArtPrint() override;
        drapeau* clone() const override;

    };
}

#endif