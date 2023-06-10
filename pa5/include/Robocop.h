#ifndef __ROBOCOP_H
#define __ROBOCOP_H
#include "Humanic.h"

class Robocop : public Humanic{
    friend class Grid;
    public:
        Robocop();
        Robocop(Grid* grd, int x, int y, int newStrength, int newHit, std::string newName);
        int getDamage();
        std::string getType();        

};

#endif
