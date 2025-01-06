#ifndef DRAPEAU_H
#define DRAPEAU_H
#include "../unitObstacle.h"
#include "../units/eclaireur.h"

namespace kpt {
    class unite;

    class drapeau : public unitObstacle {
        short unsigned int currentPosX;
        short unsigned int currentPosY;
        bool hasAWarner;
        short unsigned int turnWhenDropped;
        static const short unsigned int TURNS_BEFORE_RETURN;
    public:
        drapeau();
        ~drapeau() override = default;

        std::string asciiArtPrint() const override;
        drapeau* clone() const override;
        drapeau &operator()(bool assignment);
        std::pair<short unsigned, short unsigned> operator!() const;
        drapeau& operator()(const std::pair<short unsigned, short unsigned>& pos);
        bool operator*() const;
        drapeau &operator()();
        drapeau &initCurrentCoord();
        bool mustBeVisible() const override;
        bool shouldReturnToBase(short unsigned int currentTurn) const;
        bool isOnGround() const;
        void drop(short unsigned int currentTurn);
        bool canBePickedUpBy(const unite* unit) const;
    };
}

#endif