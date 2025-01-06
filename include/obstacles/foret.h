#ifndef FORET_H
#define FORET_H

#include "obstacle.h"

namespace kpt {
    class foret : public obstacle{
    public:
        foret();
        ~foret() override = default;

        std::string asciiArtPrint() const override;
        foret* clone() const override;
    };
}


#endif