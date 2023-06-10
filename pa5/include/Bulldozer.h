#ifndef __BULLDOZER_H
#define __BULLDOZER_H
#include "Robot.h"

class Bulldozer : public Robot{
    friend class Grid;
    public:
        Bulldozer();
        Bulldozer(Grid* grd, int x, int y, int newStrength, int newHit, std::string newName);
        int getDamage();
        std::string getType();

};

#endif
