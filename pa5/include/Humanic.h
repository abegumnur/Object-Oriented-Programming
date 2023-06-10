#ifndef __HUMANIC_H
#define __HUMANIC_H
#include "Robot.h"

class Humanic : public Robot{
    friend class Grid;
    public:
        Humanic();
        Humanic(Grid* grd, int x, int y, int newStrength, int newHit, std::string newName);
        virtual int getDamage();
        virtual std::string getType();        

};

#endif
