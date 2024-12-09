#ifndef RIVIERE_H
#define RIVIERE_H

#include "obstacle.h"

namespace kpt {
    class riviere : public obstacle {
    public:
        riviere();
        ~riviere() override = default;

        std::string asciiArtPrint() override;
        riviere* clone() const override;
    };
}

#endif
