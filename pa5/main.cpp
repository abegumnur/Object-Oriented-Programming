#include "include/Robot.h"
#include "include/Grid.h"
#include "include/Humanic.h"
#include "include/Robocop.h"
#include "include/Roomba.h"
#include "include/Bulldozer.h"
#include "include/Optimusprime.h"

/*  total number of robots in the grid  */
int TOTAL_ROBOT = INITIAL_ROBOT * ROBOT_TYPES;

int main(){

    srand(time(NULL));
    Grid myGrid;

    int robocount = 0;
    int opticount = 0;
    int roombacount = 0;
    int bullcount = 0;

    /*  construct and place every new robot in the grid*/
    while(opticount < INITIAL_ROBOT){
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        /*  name the robots according to their construction */
        if(myGrid.getAt(x, y) == nullptr){  /* if there is no other robot at x-y    */
            std::string str = std::to_string(opticount);
            std::string name = "optimusprime_" + str;
            Optimusprime* opti = new Optimusprime(&myGrid, x, y, OPTIMUS_STRENGTH, OPTIMUS_HIT, name);
            opticount++;    
        }

    }

    while(robocount < INITIAL_ROBOT){
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        if(myGrid.getAt(x, y) == nullptr){
            std::string str = std::to_string(robocount);
            std::string name = "robocop_" + str;
            Robocop* robo = new Robocop(&myGrid, x, y, ROBOCOP_STRENGTH, ROBOCOP_HIT, name);
            robocount++;
        }

    }

    while(roombacount < INITIAL_ROBOT){
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        if(myGrid.getAt(x, y) == nullptr){
            std::string str = std::to_string(roombacount);
            std::string name = "roomba_" + str;
            Roomba* room = new Roomba(&myGrid, x, y, ROOMBA_STRENGTH, ROOMBA_HIT, name);
            roombacount++;

        }

    }

    while(bullcount < INITIAL_ROBOT){
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        if(myGrid.getAt(x, y) == nullptr){
            std::string str = std::to_string(bullcount);
            std::string name = "bulldozer_" +str;
            Bulldozer* bull = new Bulldozer(&myGrid, x, y, BULLDOZER_STRENGTH, BULLDOZER_HIT, name);
            bullcount++;

        }

    }
    /*  while the number of robots is greater than one  */
    /*  keep displaying and simulating */
    while(TOTAL_ROBOT > 1){
        //std::string s;
        //myGrid.display();
        myGrid.simulate();
        //std::cout << std::endl << "Press enter for the next step" << std::endl;
        //std::getline(std::cin, s);
    }
        //myGrid.display();

    return 0;

}
