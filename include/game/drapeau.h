#ifndef DRAPEAU_H
#define DRAPEAU_H
#include "../unitObstacle.h"

namespace kpt {
    class drapeau : public unitObstacle {
        short unsigned int currentPosX;
        short unsigned int currentPosY;
        bool hasAWarner;
    public:
        drapeau();
        ~drapeau() override = default;

        std::string asciiArtPrint() override;
        drapeau* clone() const override;
        drapeau &operator()(bool assignment);
        std::pair<short unsigned, short unsigned> operator!() const;
        drapeau& operator()(const std::pair<short unsigned, short unsigned>& pos);
        bool operator*() const;
        drapeau &operator()();
        drapeau &operator!();
        bool mustBeVisible() const override;
    };
}

#endif