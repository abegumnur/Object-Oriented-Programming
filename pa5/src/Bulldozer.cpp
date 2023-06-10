#include "../include/Bulldozer.h"

Bulldozer::Bulldozer() : Robot()
{}

Bulldozer::Bulldozer(Grid *grd, int x, int y, int newStrength, int newHit, std::string newName) : Robot(grd, x, y, newStrength, newHit, newName)
{}

int Bulldozer::getDamage(){

    int damage = Robot::getDamage(); 
    //std::cout << getType() << " attacks for " << damage << " points!" << std::endl;

    return damage;
}

std::string Bulldozer::getType()
{
    return "Bulldozer";
}

