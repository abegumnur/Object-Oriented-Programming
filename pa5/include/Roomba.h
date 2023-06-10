#ifndef __ROOMBA_H
#define __ROOMBA_H
#include "Robot.h"

class Roomba : public Robot{
    friend class Grid;
    public:
        Roomba();
        Roomba(Grid* grd, int x, int y, int newStrength, int newHit, std::string newName);
        int getDamage();
        std::string getType();        

};

#endif
