#include "../include/Humanic.h"

Humanic::Humanic() : Robot()
{}

Humanic::Humanic(Grid *grd, int x, int y, int newStrength, int newHit, std::string newName) : Robot(grd, x, y, newStrength, newHit, newName)
{
} 

int Humanic::getDamage(){

    int damage = Robot::getDamage();

    if (rand() % 10 == 0) {
        damage += 50;
        //std::cout << getName() << " uses a tactical nuke for extra 50 damage!" << std::endl;
    }
    
    return damage;
}

std::string Humanic::getType()
{   return "Humanic";   }
