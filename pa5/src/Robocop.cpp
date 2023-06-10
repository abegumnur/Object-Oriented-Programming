#include "../include/Robocop.h"

Robocop::Robocop() : Humanic()
{}

Robocop::Robocop(Grid *grd, int x, int y, int newStrength, int newHit, std::string newName) : Humanic(grd, x, y, newStrength, newHit, newName)
{}

int Robocop::getDamage()
{
    int damage = Humanic::getDamage();    
    //std::cout << getName() << " attacks for " << damage << " damage!" << std::endl;

    return damage;
}

std::string Robocop::getType()
{   return "Robocop";   
}
