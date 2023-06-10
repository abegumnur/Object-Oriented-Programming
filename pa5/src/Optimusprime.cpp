#include "../include/Optimusprime.h"

Optimusprime::Optimusprime() : Humanic()
{}

Optimusprime::Optimusprime(Grid* grd, int x, int y, int newStrength, int newHit, std::string newName) : Humanic(grd, x, y, newStrength, newHit, newName)
{}

int Optimusprime::getDamage(){
    
    int damage = Humanic::getDamage();

    if (rand() % 15 == 0) {
        damage *= 2;
        //std::cout << getName() << " uses a strong attack for double damage!" << std::endl;
    }
    
    return damage;
}

std::string Optimusprime::getType()
{
    return "Optimusprime";
}
