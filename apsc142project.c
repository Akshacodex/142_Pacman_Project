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
int pacX, pacY;



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

    load_map("map.txt", &map_height, &map_width);

    // printf("Map dimensions: %d x %d\n", map_width, map_height);

    print_map(map_width, map_height);

    // printf("%d, %d", pacX, pacY);

    char direction;
    while (1) {

        printf("Enter direction (w, a, s, d): ");
        scanf(" %c", &direction);

        int result = move_actor(&pacY, &pacX, direction, 0);

        if (result == MOVED_OKAY) {

            print_map(map_width, map_height);

        } else if (result == MOVED_WALL) {
            printf("Pacman cannot move in to a wall DUMBASS!\na");
        } else if (result == MOVED_INVALID_DIRECTION) {
            printf("Do you live under a rock? The options are W,A,S,D.\n");
        }


    }

    free(map);

    return NO_ERROR;
}