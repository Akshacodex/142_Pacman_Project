// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

// don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and ghost.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "ghost.h"

// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
// dot_map is a pointer to a dynamically allocated map for keeping track of what dots are left
char *map = NULL, *dot_map = NULL;
// width and height store the width and height of map, NOT counting outer walls
int map_width, map_height;
// Variables used to store the coordinates of Pacman
int pacX = -1, pacY = -1;
// Variable to store the direction of actors movement in move_actor function
char direction;
// Arrays to store the coordinates of every ghosts
int ghost_X[MAX_GHOSTS], ghost_Y[MAX_GHOSTS];



/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PACMAN when no pacman is found on the map
 *   ERR_NO_GHOSTS when fewer than 2 ghosts are found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */
int main(void) {

    //  The setbuf line is here so that print statements appears before the user input statements
    setbuf(stdout, NULL);

    // Loading the map from the file
    load_map(MAP_NAME, &map_height, &map_width);

    // Checking if there's a Pacman on the map
    if (pacY == -1 || pacX == -1 || pacX >= map_width || pacY >= map_height) {
        return ERR_NO_PACMAN;
    }

    // Checking to make sure if the number of ghosts on the map equal MAX_GHOSTS
    int ghost_found = 0;
    for (int i = 0; i < map_height * map_width; i++) {
        if (map[i] == GHOST) {
            ghost_found++;
        }
    }
    if (ghost_found < MAX_GHOSTS) {
        return ERR_NO_GHOSTS;
    }

    // Printing the initial map
    print_map(map_width, map_height);

    // Game Loop Setting the run variable to 1 to make it an infinite loop
    int run = 1;
    while (run) {

        // Gets the direction from the user without the user needing to press enter
        direction = getch();

        // Moving the pacman using the direction we received from the user
        int move_result = move_actor(&pacY, &pacX, direction, EAT_DOTS);

        // Checking if the move result is okay
        if (move_result == MOVED_WALL) {
            // Pacman cannot move into a wall
        } else if (move_result == MOVED_INVALID_DIRECTION) {
            // Invalid input entered
        }

        // A loop used to move all ghosts
        for (int i = 0; i < MAX_GHOSTS; i++) {
            char ghost_direction = sees_pacman(pacY, pacX, ghost_Y[i], ghost_X[i]);
            move_actor(&ghost_Y[i], &ghost_X[i], ghost_direction, 0);
        }

        // Printing the updated map
        print_map(map_width, map_height);

        // Checking for game over conditions
        if (check_win(pacY, pacX, ghost_Y, ghost_X)) {
            // Setting run to 0 to exit the game loop
            run = 0;
            printf("Congratulations! You win!");

        } else if(check_loss(pacY, pacX, ghost_Y, ghost_X)) {
            // Setting run to 0 to exit the game loop
            run = 0;
            printf("Sorry, you lose.");

        }

    }

    // Freeing allocated memory
    free(map);
    free(dot_map);

    return NO_ERROR;
}

