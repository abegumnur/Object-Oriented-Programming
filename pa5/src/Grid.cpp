#include "../include/Grid.h"

/// @brief default constructor for Grid class
//  sets all the members of the grid to nullptr 
Grid::Grid(){
    
    int i,j;
    
    for(i = 0; i < GRID_SIZE; i++){
        for(j = 0; j < GRID_SIZE; j++){
            grids[i][j] = nullptr;
        }
    }
}


/// @brief destructor of the Grid class
//  deletes the remaining robots 
Grid::~Grid(){
    int i,j;

    for(i = 0; i < GRID_SIZE; i++){
        for(j = 0; j < GRID_SIZE; j++){
            if(grids[i][j] != nullptr)
                delete (grids[i][j]);
        }
    }

}

/// @brief returns a pointer to the given x-y positions at the grid
/// @param x x position of the grid
/// @param y y position of the grid
/// @return the pointer to a Robot or nullptr 
Robot *Grid::getAt(int x, int y)
{
    if((x >= 0) && ( x < GRID_SIZE) && (y >= 0) && ( y < GRID_SIZE) )
        return grids[x][y];

    return nullptr;

}

/// @brief sets the grid member at the given x-y positions to the rbt value
/// @param rbt pointer to the Robot objects to be set on the grid or nullptr
/// @param x new x position of the robot
/// @param y new y position of the robot
void Grid::setRobot(Robot *rbt, int x, int y)
{
    if((x >= 0) && ( x < GRID_SIZE) && (y >= 0) && ( y < GRID_SIZE) )
        grids[x][y] = rbt;
    
}

/// @brief simulates a one step of interaction between the robots 
//  starts from the first row and column and moves the Robots
//  if they have not moved yet
void Grid::simulate(){

    int i,j;
    if(TOTAL_ROBOT == 1)
        return;
    //  First reset all robots to not moved
    for(i = 0; i < GRID_SIZE; i++){
        for(j = 0; j < GRID_SIZE; j++){
            if(grids[i][j] != nullptr) grids[i][j]->moved = false;

        }
    }

    // Loop through the cells and move the robots one by one
    for(i = 0; i < GRID_SIZE; i++){
        for(j = 0; j < GRID_SIZE; j++){
            if(grids[i][j] != nullptr){
                if(grids[i][j]->moved == false){
                    //std::cout << "Moving "<<grids[i][j]->getName() << " at position "<< grids[i][j]->getX() << " "<<grids[i][j]->getY()<<std::endl;
                    grids[i][j]->moved = true;
                    grids[i][j]->move();
                }
            }
        }
    }

}


/// @brief display the current picture of the grid  
//  for debugging purposes  
void Grid::display(){

    std::cout << std::endl;

    for(int i = 0; i < GRID_SIZE; i++){
        for(int k = 0; k < GRID_SIZE; k++){
            if(grids[i][k] == nullptr)
                std::cout << ".";
            else if(grids[i][k]->getType() == "Roomba")
                std::cout << "m";
            else if(grids[i][k]->getType() == "Robocop")
                std::cout << "o";
            else if(grids[i][k]->getType() == "Bulldozer")
                std::cout << "u";
            else if(grids[i][k]->getType() == "Optimusprime")
                std::cout << "p";
        }

        std::cout << std::endl;

    }


}
