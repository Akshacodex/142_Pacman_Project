// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "ghost.h"
#include "game.h"
char *map = NULL , *dot_map = NULL;
int width = 11;
int height = 11;
}

int pacX;
int pacY;
int ghost_Y[];
int ghost_X[];
int map_width;
int map_height;

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

void setup(void) {

}

void teardown(void) {

}

/* tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// tests for load_map
TEST_CASE("A test for load_map") {

    //declaring varaibles to call the load_map function
    char *fp = "map.txt";
    int * m_height= &height;
    int * m_width = &width;
    load_map(fp, m_height, m_width);

    //Creating a memory space for the hard coded 1D array map
    char * mapArray = (char *) malloc(11*11+1);

    //hard coded map in a 1D array
    char gamemap[] = {
            'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
            'W', 'G', '.', '.', '.', 'W', '.', '.', '.', '.', 'W',
            'W', '.', 'W', 'W', '.', 'W', '.', 'W', 'W', '.', 'W',
            'W', '.', 'W', '.', '.', '.', '.', '.', 'W', '.', 'W',
            'W', '.', 'W', '.', 'W', 'W', 'W', '.', 'W', '.', 'W',
            'W', '.', '.', '.', '.', 'P', '.', '.', '.', '.', 'W',
            'W', '.', 'W', '.', 'W', 'W', 'W', '.', 'W', '.', 'W',
            'W', '.', 'W', '.', '.', '.', '.', '.', 'W', '.', 'W',
            'W', '.', 'W', 'W', '.', 'W', '.', 'W', 'W', '.', 'W',
            'W', '.', '.', '.', '.', 'W', '.', '.', '.', 'G', 'W',
            'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'
    };


    //Using a loop to store all units in the array into the memory space in the correct locations.
    for(int i = 0; i < 120; i++){
        mapArray[i] = gamemap[i];
    }

    //Checks if the data stored in the dynamic array is correct by comapring it to the original map
    for(int i = 0; i < 120; i++){
        CHECK(mapArray[i] == map[i]);
    }

    //Checks if height and width are correct
    CHECK(height == *m_height);
    CHECK(width == *m_width);
}


// tests for is_wall
TEST_CASE("A test for is_wall") {

    //declaring varaibles to call the load_map function
    char *fp = "map.txt";
    int * m_height = &height;
    int * m_width = &width;
    load_map(fp, m_height, m_width);

    //Insert the coordinates and change the corresponding variable (YES_WALL/NOT_WALL) that represents the position on the map to check if it is a wall or not.
    int y = 1;
    int x = 1;
    //is_wall returns true or false
    CHECK(is_wall(y, x) == NOT_WALL);


}

TEST_CASE("A test for move_actor"){
    //declaring varaibles to call the load_map function
    char *fp = "map.txt";
    int * m_height = &height;
    int * m_width = &width;
    load_map(fp, m_height, m_width);

    //declaring pacman's initial position and using pointers to point at his new coordinates
    int PacY;
    int PacX;
    int *py1 = &PacY;
    int *px1 = &PacX;
    //move the actor twice
    move_actor(py1, px1, RIGHT , EAT_DOTS);
    move_actor(py1, px1, RIGHT , EAT_DOTS);

    //checks for new changes in pacman's coordinates and index
    CHECK(dot_map[*py1 * map_width + *px1 ] == EAT_DOTS);
    CHECK(dot_map[*py1 * map_width + *px1 ] == EAT_DOTS);
    CHECK(*py1 == 5);
    CHECK(*px1 == 7);

    //declaring the ghost's initial position and using pointers to point at his new coordinates
    int y2 = 1;
    int x2 = 1;
    int *py2 = &y2;
    int *px2 = &x2;

    //move the actor twice
    move_actor(py2, px2, RIGHT, REPLACE_DOTS);
    move_actor(py2, px2, RIGHT, REPLACE_DOTS);
    //checks for new changes in the ghost's coordinates and index
    CHECK(dot_map[*py2 * map_width + *px2] == EAT_DOTS);
    CHECK(dot_map[*py2 * map_width + *px2] == REPLACE_DOTS);
    CHECK(*py2 == 1);
    CHECK(*px2 == 3);



}

TEST_SUITE_END();

/* tests for ghost.c */
TEST_SUITE_BEGIN("Ghost tests");

// tests for sees_pacman
TEST_CASE("A test for sees_pacman") {

    //declaring varaibles to call the load_map function
    char *fp = "map.txt";
    int * m_height = &height;
    int * m_width = &width;
    load_map(fp, m_height, m_width);

    //Declaring variables to call the sees_pacman function
    int pacmanx;
    int pacmany;
    int ghostx[NUM_GHOSTS];
    int ghosty[NUM_GHOSTS];
    char see_direction;
    sees_pacman(pacmany, pacmanx, ghosty[NUM_GHOSTS], ghostx[NUM_GHOSTS]);

    //The loop checks that the same applied to both ghosts
    for(int i = 0; i < NUM_GHOSTS; i++){
        if(see_direction != SEES_NOTHING){ //if it sees pacman
            //checks if pacaman and one or both of the ghosts are at the same position
            CHECK((pacmanx == ghostx[NUM_GHOSTS] && pacmany == ghosty[NUM_GHOSTS]) == EATING_PACMAN);
            //checks if pacman and one or both ghosts are on the same row but different columns, if pacman is on the right of one of the ghosts, the ghost looks to the right
            CHECK((pacmanx > ghostx[NUM_GHOSTS] && pacmany == ghosty[NUM_GHOSTS]) == LEFT);
            //checks if pacman and one or both ghosts are on the same row but different columns, if pacman is on the left of one of the ghosts, the ghost looks to the left
            CHECK((pacmanx < ghostx[NUM_GHOSTS] && pacmany == ghosty[NUM_GHOSTS]) == RIGHT);
            //checks if pacman and one or both ghosts are on the same column but different rows, if pacman is on under one of the ghosts, the ghost looks down
            CHECK((pacmanx == ghostx[NUM_GHOSTS] && pacmany > ghosty[NUM_GHOSTS]) == UP);
            //checks if pacman and one or both ghosts are on the same column but different rows, if pacman is on top of one of the ghosts, the ghost looks up
            CHECK((pacmanx == ghostx[NUM_GHOSTS] && pacmany < ghosty[NUM_GHOSTS]) == DOWN);
        } else { // if it doesn't see pacman
            switch (see_direction) { //switch case applies depending on which direction the ghost is looking at
                case UP:
                    for (int j = 0; j < abs(ghostx[NUM_GHOSTS] - pacmanx); j++) {
                        if (is_wall(pacmany + 1, pacmanx)) {
                            CHECK(see_direction == SEES_NOTHING); //loop checks if ghost sees a wall in the UP direction, if it does, then the ghost does not see anything
                        }

                    }
                case DOWN:
                    for (int j = 0; j < abs(ghostx[NUM_GHOSTS] - pacmanx); j++) {
                        if (is_wall(pacmany - 1, pacmanx)) {
                            CHECK(see_direction == SEES_NOTHING);//loop checks if ghost sees a wall in the DOWN direction, if it does, then the ghost does not see anything
                        }

                    }
                case LEFT:
                    for (int j = 0; j < abs(ghostx[NUM_GHOSTS] - pacmanx); j++) {
                        if (is_wall(pacmany, pacmanx + 1)) {
                            CHECK(see_direction == SEES_NOTHING);//loop checks if ghost sees a wall in the LEFT direction, if it does, then the ghost does not see anything
                        }

                    }
                case RIGHT:
                    for (int j = 0; j < abs(ghostx[NUM_GHOSTS] - pacmanx); j++) {
                        if (is_wall(pacmany - 1, pacmanx)) {
                            CHECK(see_direction == SEES_NOTHING);//loop checks if ghost sees a wall in the RIGHT direction, if it does, then the ghost does not see anything
                        }

                    }
            }

        }

    }



}

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win
TEST_CASE("A test for check_win"){
    //declaring varaibles to call the load_map function
    char *fp = "map.txt";
    int * m_height = &height;
    int * m_width = &width;
    load_map(fp, m_height, m_width);

    //declaring variables to call the check_win function
    int pacmanx;
    int pacmany;
    int ghostx[NUM_GHOSTS];
    int ghosty[NUM_GHOSTS];
    check_win(pacmany, pacmanx, ghosty, ghostx);
    for (int y = 0; y < map_width; ++y) {
        for (int x = 0; x < map_height; ++x) {
            CHECK(dot_map[(y * map_width) + x] == EMPTY); //loop scans through the dot map, checks if all dots on there are eaten or an empty dot map. If dot map is empty, then the user wins
        }
    }

}

// test for check_loss
TEST_CASE("A test for check_loss"){
    //declaring variables for check_loss condition
    int pacmanx = 5;
    int pacmany = 5;
    int * ppacmanx = &pacmanx;
    int * ppacmany = &pacmany;
    int ghostx[] = {1 ,9};
    int ghosty[] = {1 ,9};
    int * pghostx = &ghostx[0];
    int * pghosty = &ghosty[0];

    //declaring varaibles to call the load_map function
    char *fp = "map.txt";
    int * m_height;
    int * m_width;
    load_map(fp, m_height, m_width);

    //checks if the function is executed, if it is but the ghost and pacman are not in the same position, then the game continues
    CHECK(check_loss(pacmany, pacmanx, ghosty, ghostx) == KEEP_GOING);

    for(int i = 0; i < 4; i++){ //this loops moves the ghost in the top corner and pacman 4 times in order to get them in the same position on the map, hence activating the losing condition
        move_actor(ppacmany, ppacmanx, LEFT, EAT_DOTS);
        move_actor(pghosty, pghostx, DOWN, REPLACE_DOTS);
    }


    CHECK(!check_loss(pacmany, pacmanx, ghosty, ghostx) == YOU_LOSE); //check_loss function is executed here, and pacman and the ghost are in the same position, activating the second ending to the game where the user loses
}

TEST_SUITE_END();




