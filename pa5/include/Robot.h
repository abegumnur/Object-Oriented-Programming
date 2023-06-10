#ifndef __ROBOT_H
#define __ROBOT_H
#include <string>
#include "Grid.h"
#include <iostream>

const int INITIAL_ROBOT = 5; // initial value for each robot type
const int ROBOT_TYPES = 4;   // number of robot types
/*  default hitpoints and strength values of each robot type    */
const int OPTIMUS_HIT = 100;
const int OPTIMUS_STRENGTH = 100;
const int ROBOCOP_HIT = 40;
const int ROBOCOP_STRENGTH = 30;
const int ROOMBA_HIT = 10;
const int ROOMBA_STRENGTH = 3;
const int BULLDOZER_HIT = 200;
const int BULLDOZER_STRENGTH = 50;

extern int TOTAL_ROBOT; //  total number of robots present on the grid

class Grid; //forward definition of Grid class

class Robot{
    friend class Grid;
    public:
        Robot();
        Robot(Grid* grds,int x, int y, int newStrength, int newHit, std::string newName);
        virtual ~Robot();
        /* getter - setters  */
        /* since every robot type has different conditions  */ 
        /* for calculation of its damage value getDamage() is */
        /* declared as virtual along with getType()  */
        virtual int getDamage();    
        virtual std::string getType();
        int getHit() const;
        void setHit(int newHit);
        void setStrength(int newStrength);
        int getStrength() const;
        std::string getName() const;
        int getX();
        int getY();
        /* moves the Robot object along the Grid   */
        void move();
        /*  simulates a match between two given robots    */
        friend void match(Robot* rbt1, Robot* rbt2);
        /*  deletes the given robot from the grid   */
        friend void kill_robot(Grid* grd, int x, int y);

    protected:
        int x, y; //position of the robot in the grid
        Grid* grid;
        std::string name;   //name of the robot
        int strength, hitpoints;    
        bool moved; //indicates if the robot has moved
};


#endif
