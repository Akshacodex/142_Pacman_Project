// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

#include "map.h"

extern char * map, * dot_map;

int check_win(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {

    // Looping through the Dot map
    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            // Checking if there are any dots left in the dot map after each move of the Pacman
            if (dot_map[y * map_width + x] == DOT) {
                return KEEP_GOING;
            }
        }
    }
    return YOU_WIN;
}

int check_loss(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {

    // Looping through the ghosts
    for (int i = 0; i < NUM_GHOSTS; i++) {
        // If Pacman position overlaps with a ghost's position
        if (ghosts_y[i] == pacman_y && ghosts_x[i] == pacman_x) {
            // Update the map to remove the Pacman from the map and place the ghost at Pacman position
            map[pacman_y * map_width + pacman_x] = EMPTY;
            map[ghosts_y[i] * map_width + ghosts_x[i]] = GHOST;
            return YOU_LOSE;
        }
    }
    return KEEP_GOING;
}

