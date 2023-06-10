#include "../include/Robot.h"
#include <ctime>
#include <cstdlib>
using std::cout;
using std::endl;

/// @brief              displays the hit messages generated to the terminal 
/// @param attacker     the name of the robot that attacks the other one
/// @param attackerhit  current hitpoints of the attacker robot
/// @param victim       the name of the robot that has been attacked
/// @param victimhit    current hitpoints of the victim robot
/// @param damage       the damage points the attacker inflicts on the victim
void hit_message(std::string attacker, int attackerhit, std::string victim, int victimhit, int damage){

    std::cout << attacker << " (" << attackerhit << ") hits "<< victim;
    std::cout << " (" << victimhit << ") with "<< damage << std::endl;

    std::cout << "The new hitpoints of "<< victim << " is " << victimhit - damage << std::endl;


}
/*  no parameter constructor for the Robot class    */
Robot::Robot() : strength(10), hitpoints(10), name("ROBOT") {
    grid = nullptr;
    moved = false;
    x = 0; 
    y = 0;
}

/// @brief      parametered constructor of the Robot class
/// @param grds the pointer to the Grid object the robot will be placed on
/// @param x    the row robot will be placed on
/// @param y    the column robot will be placed on
/// @param newStrength strength value
/// @param newHit      hitpoints value
/// @param newName     name string
Robot::Robot(Grid* grds, int x, int y, int newStrength, int newHit, std::string newName) : grid(grds), strength(newStrength), hitpoints(newHit), name(newName)
{
    moved = false;
    this->x = x;
    this->y = y;
    grds->setRobot(this, x, y); /* set the robot in the grid object */
}


Robot::~Robot()
{}

int Robot::getDamage(){
    int damage;
    // All robots inflict damage which is a
    // random number up to their strength
    damage = (rand() % strength) + 1;
    //std::cout << getName() << " attacks for " <<damage << " points!" << std::endl;
    return damage;

}
 
/// @brief unless the Robot encounters another Robot it keeps
//  moving along the grid, when it encounters another Robot
//  a match between them starts until one of them is announced as dead
void Robot::move(){

    int dir;
    bool hitrobot = false;

    if(TOTAL_ROBOT == 1)
        return;

    /* if the robot has not fighted with any other robot */
    /* keep moving along the grid   */
    while(!hitrobot){

        dir = rand() % 4;   /* pick a random direction to move  */
        if(dir == 0){
            //std::cout << getName() << " is moving left\n";
            /*  if the left grid is empty move there    */
            if((y > 0) && (grid->getAt(x, y - 1) == nullptr)){
                grid->setRobot(grid->getAt(x, y), x, y - 1);
                grid->setRobot(nullptr, x, y);
                y--;    /* decrement the y axis acccordingly    */
            }       
            /* if the left grid is occupied by another robot start the fight    */
            else if((y > 0) && (grid->getAt(x, y - 1) != nullptr)){
                hitrobot = true;
                match(this, grid->getAt(x, y - 1));
            }
        }

        if(dir == 1){
            //std::cout << getName() << " is moving right\n";
            /*  if the right grid is empty move there  */
            if((y < GRID_SIZE - 1) && (grid->getAt(x, y + 1) == nullptr)){
                grid->setRobot(grid->getAt(x, y), x, y + 1);
                grid->setRobot(nullptr, x, y);
                y++;    /* increment the y axis value   */
            }
            /* if the right grid is occupied by another robot start the fight   */
            else if((y < GRID_SIZE - 1) && (grid->getAt(x, y + 1) != nullptr)){
                hitrobot = true;
                match(this, grid->getAt(x, y + 1));
            }

        }

        if(dir == 2){
            //std::cout << getName() << " is moving up\n";

            /*  if the upper grid is empty move there   */
            if((x > 0) && (grid->getAt(x - 1, y) == nullptr)){
                grid->setRobot(grid->getAt(x, y), x - 1, y);
                grid->setRobot(nullptr, x, y);
                x--;
            }
            /*  or else fight with the upper robot  */
            else if((x > 0) && (grid->getAt(x - 1, y) != nullptr)){
                hitrobot = true;
                match(this, grid->getAt(x - 1, y));
            }

        }

        if(dir == 3){
            //std::cout << getName() << " is moving down\n";

            /*  if the bottom grid is empy move there   */
            if((x < GRID_SIZE - 1) && (grid->getAt(x + 1, y) == nullptr)){
                grid->setRobot(grid->getAt(x, y), x + 1, y);
                grid->setRobot(nullptr, x, y);
                x++;
            }
            /*  if it is full, fight with that robot    */
            else if((x < GRID_SIZE - 1) && (grid->getAt(x + 1, y) != nullptr)){
                hitrobot = true;
                match(this, grid->getAt(x + 1, y));
            }

        }
        
    }


}
/* getter and setter functions for member variables */
int Robot::getX()   {  return x;    }

int Robot::getY()   {   return y;   }

std::string Robot::getType() { return "Robot"; }

int Robot::getHit() const{    return hitpoints; }

void Robot::setHit(int newHit){ hitpoints = newHit; }

void Robot::setStrength(int newStrength) { strength = newStrength;  }

int Robot::getStrength() const {   return strength;    }

std::string Robot::getName() const  {   return  name;   }

/// @brief imitate a match between two robots until one of them has run out of hitpoints
/// @param rbt1 the robot that will attack first
/// @param rbt2 the other robot
void match(Robot *rbt1, Robot *rbt2){

    std::cout << std::endl;
    /* get the hitpoints and names of the robots    */
    int hitpoints1 = rbt1->getHit();
    int hitpoints2 = rbt2->getHit();
    std::string rbt1name = rbt1->getName();
    std::string rbt2name = rbt2->getName();

    //std::cout << "Starting the fight\n";
    //std::cout << rbt1name <<" is at "<< rbt1->getX()<< " "<<rbt1->getY() <<std::endl;
    //std::cout << rbt2name <<" is at "<< rbt2->getX()<< " "<<rbt2->getY() <<std::endl;

    int alive;  /*  keeps track of which robot is alive (1-2)   */
    /*  if the first robot has 0 or negative hitpoints value   */
    /*  it cannot fight and should be removed from the grid */
    if(hitpoints1 <= 0){
        std::cout << rbt1name << " has minus or 0 hitpoints and cannot match!\n";
        int x = rbt1->getX();
        int y = rbt1->getY();
        /* delete the robot */
        if(rbt1->grid->getAt(x, y) != nullptr){
            delete (rbt1->grid->getAt(x, y));
            rbt2->grid->setRobot(nullptr, x, y);
        }
        return;
    }
    /*  if the second robot has 0 or negative hitpoints value   */
    /*  it cannot fight and should be removed from the grid */
    if(hitpoints2 <= 0){
        std::cout << rbt2name << " has minus or 0 hitpoints and cannot match!\n";
        int x = rbt2->getX();
        int y = rbt2->getY();
        /*  delete it from the grid */
        if(rbt2->grid->getAt(x, y) != nullptr){
            delete (rbt2->grid->getAt(x, y));
            rbt1->grid->setRobot(nullptr, x, y);
        }
        return;
    }

    int damage1, damage2;
    /* loop until one of the robots is announced as dead    */
    while(true){
        /*  calculate the damage the first robot will inflict on the second one   */
        damage1 = rbt1->getDamage();
        hit_message(rbt1name, hitpoints1, rbt2name, hitpoints2, damage1);
        /*  hitpoints of the second robot deccremented accordingly  */
        hitpoints2 -= damage1;
        rbt2->setHit(hitpoints2);
        
        /*  if the hitpoints of the second robot is now negative or 0   */
        /*  remove it from the grid and announce its death  */
        if(hitpoints2 <= 0){
            //std::cout << rbt2name << " dies.\n";
            
            int rbt2x = rbt2->getX();
            int rbt2y = rbt2->getY();
            /*  call the kill robot function for the second robot   */
            kill_robot(rbt2->grid, rbt2->getX(), rbt2->getY());
            
            //std::cout << "Winner of the match is "<< rbt1name << " (" << rbt1->getHit() << ")\n"; 
           
            /*  the first robot should move to the second robots position in the grid   */
            /*  after killing it    */
            rbt1->grid->setRobot(rbt1, rbt2x, rbt2y);
            rbt1->grid->setRobot(nullptr, rbt1->x, rbt1->y);    /* set the old position of the first robot as null  */
            rbt1->x = rbt2x;    /*  update the x and y values of the first robot accordingly    */
            rbt1->y = rbt2y;

            /*  the first robot is left alive    */
            alive = 1;            
            break;
        }
        /*  damage value the second robot will inflict on the first one */
        damage2 = rbt2->getDamage();
        /*  print the hit_message   */
        hit_message(rbt2name, hitpoints2, rbt1name, hitpoints1, damage2);
        /*  decrement the hitpoints value of the first robot accordingly    */
        hitpoints1 -= damage2;
        rbt1->setHit(hitpoints1);
        /*  if the hitpoints of the first robot is negative or 0  */
        /*  it is announced as dead and removed from the grid   */
        if(hitpoints1 <= 0){
            //std::cout << rbt1name << " dies.\n";

            /*  call the kill robot function for the first robot   */
            kill_robot(rbt1->grid, rbt1->getX(), rbt1->getY());
            
            //std::cout << "Winner of the match is "<< rbt2name << " (" << rbt2->getHit() << ")\n";        
            
            /*  the second robot is left alive  */
            alive = 2;
            break;

        }        

    }
    /*  display the match results   */
    /*
    if(alive == 1){
        std::cout << "printing match results:\n";
        rbt1->grid->display();
    }
    else{
        std::cout << "printing match results:\n";
        rbt2->grid->display();

    }*/

}

/// @brief     deletes the robot at the given x and y positons
/// @param grd pointer to the Grid object the robot is being deleted from
/// @param x   the x position of the soon to be dead robot
/// @param y   the y position of the soon to be dead robot
void kill_robot(Grid* grd, int x, int y){

    /*  if it is not nullptr    */
    if(grd->grids[x][y]){
        delete (grd->grids[x][y]);  /* delete the robot and */
        grd->grids[x][y] = nullptr; /* set it to nullptr    */

    /*  decrement the number of total robots and    */
    /*  display its value   */
    --TOTAL_ROBOT;
    //printf("TOTAL ROBOT IS %d\n",TOTAL_ROBOT);

    }

}



