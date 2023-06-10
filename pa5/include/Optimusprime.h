#ifndef __OPTIMUSPRIME_H
#define __OPTIMUSPRIME_H
#include "Humanic.h"

class Optimusprime : public Humanic{
    friend class Grid;
    public:
        Optimusprime();
        Optimusprime(Grid* grd, int x, int y, int newStrength, int newHit, std::string newName);
        int getDamage();
        std::string getType();        

};

#endif
