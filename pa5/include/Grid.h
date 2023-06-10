#ifndef __GRID_H
#define __GRID_H
#include "Robot.h"

const int GRID_SIZE = 10;
// forward defitions
class Robot;
class Robocop;
class Humanic;
class OptimusPrime;
class Roomba;
class Bulldozer;

/* every robot class is a friend to grid    */
class Grid{
    friend class Robot;
    friend class Robocop;
    friend class Humanic;
    friend class OptimusPrime;
    friend class Roomba;
    friend class Bulldozer;
    
    public:
        Grid();
        ~Grid();
        Robot* getAt(int x, int y);
        void setRobot(Robot* rbt, int x, int y);
        void simulate();    //simulates one step 
        void display();     //displays the robots in the grid
        friend void kill_robot(Grid* grd, int x, int y); 
    private:
        Robot* grids[GRID_SIZE][GRID_SIZE];

};


#endif
