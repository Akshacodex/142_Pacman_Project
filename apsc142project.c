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
int pacX = -1, pacY = -1;
char direction;
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
    setbuf(stdout, NULL);

    load_map(MAP_NAME, &map_height, &map_width);

    if (pacY == -1 || pacX == -1 || pacX >= map_width || pacY >= map_height) {

        printf("No pacman found on the map.\n");
        return ERR_NO_PACMAN;

    }
    else if (ghost_Y == -1 || ghost_X == -1 || ghost_X >= map_width || ghost_Y >= map_height) {

        printf("No Ghost found on the map.\n");
        return ERR_NO_GHOSTS;
    }

//     printf("Map dimensions: %d x %d\n", map_width, map_height);

//    printf("w:%d h:%d\n", map_width, map_height);

    print_map(map_width, map_height);

    // printf("%d, %d", pacX, pacY);

    int run = 1;
    while (run) {

//        printf("Enter direction: ");
        direction = getch();
//        printf("%c", direction);
        printf("\n");

        int result = move_actor(&pacY, &pacX, direction, EAT_DOTS);

        if (result == MOVED_WALL) {
//            printf("Pacman cannot move in to a wall, DUMBNESS!\n");
        } else if (result == MOVED_INVALID_DIRECTION) {
//            printf("Do you live under a rock? The options are W,A,S,D.\n");
        }

        for (int i = 0; i < MAX_GHOSTS; i++) {
            char ghost_direction = sees_pacman(pacY, pacX, ghost_Y[i], ghost_X[i]);
            move_actor(&ghost_Y[i], &ghost_X[i], ghost_direction, 0);
        }

//        printf("%c\n", ghost_direction);

//        printf("%d\n",ghost_Y[1]);

        print_map(map_width, map_height);


        if (check_win(pacY, pacX, ghost_Y, ghost_X)) {
            run = 0;
            printf("Congratulations! You win!");

        } else if(check_loss(pacY, pacX, ghost_Y, ghost_X)) {
            run = 0;
            printf("Boohoo, you lose");

        }

    }

    free(map);
    free(dot_map);

    return NO_ERROR;
}

