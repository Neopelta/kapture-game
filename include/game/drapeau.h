#ifndef DRAPEAU_H
#define DRAPEAU_H
#include "../units/unite.h"


class drapeau {
    short unsigned int initialPosX;
    short unsigned int initialPosY;
    short unsigned int currentPosX;
    short unsigned int currentPosY;
    unite *holder;

public:
    drapeau();
    ~drapeau();
    drapeau(const drapeau &d);
    drapeau &operator=(const drapeau &d);
    unite *operator*() const;
    drapeau& operator()(unite &u);
};



#endif