// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

#include "map.h"

extern char * map, * dot_map;
extern int map_height;
extern int map_width;

int check_win(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {

    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            if (dot_map[y * map_width + x] == DOT) {
                return KEEP_GOING;
            }
        }
    }
    return YOU_WIN;
}


int check_loss(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    for (int i = 0; i < NUM_GHOSTS; i++) {
        if (ghosts_y[i] == pacman_y && ghosts_x[i] == pacman_x) {
            map[pacman_y * map_width + pacman_x] = EMPTY;

            map[ghosts_y[i] * map_width + ghosts_x[i]] = GHOST;
            return YOU_LOSE;
        }
    }
    return KEEP_GOING;
}

