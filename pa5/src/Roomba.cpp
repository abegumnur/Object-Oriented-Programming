#include "../include/Roomba.h"

Roomba::Roomba() : Robot()
{}

Roomba::Roomba(Grid* grd, int x, int y, int newStrength, int newHit, std::string newName) : Robot(grd, x, y, newStrength, newHit, newName)
{}

int Roomba::getDamage(){

    int damage = Robot::getDamage();
    damage += Robot::getDamage();
    //std::cout << getName() << " attacks twice for " << damage << " points total!" << std::endl;
    
    return damage;
}

std::string Roomba::getType()
{    
    return "Roomba";
}
