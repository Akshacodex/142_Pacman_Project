// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "ghost.h"
#include "map.h"


char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x) {

    int ghostPosition = ghost_y * map_width + ghost_x;
    int PacmanPosition = pacman_y * map_width + pacman_x;

    char see_direction = SEES_NOTHING;

    if (ghostPosition == PacmanPosition) {
        return EATING_PACMAN;
    } else if (ghost_y == pacman_y && abs(ghost_x - pacman_x) > 0) {
        if (pacman_x > ghost_x) {
            see_direction = LEFT;
        } else {
            see_direction = RIGHT;
        }
    } else if (pacman_x == ghost_x && abs(ghost_y - pacman_y) > 0) {
        if (pacman_y > ghost_y) {
            see_direction = DOWN;
        } else {
            see_direction = UP;
        }
    }

    if (see_direction != SEES_NOTHING) { // Check if see_direction has been set
        switch (see_direction) {
            case UP:
                for (int i = 1; i < abs(ghost_y - pacman_y); i++) { // Corrected abs calculation
                    if (!is_wall(pacman_y + i, pacman_x)) { // Corrected coordinates
                        return see_direction; // Return see_direction if no wall found
                    }
                }
                break;
            case DOWN:
                for (int i = 1; i < abs(ghost_y - pacman_y); i++) { // Corrected abs calculation
                    if (!is_wall(pacman_y - i, pacman_x)) { // Corrected coordinates
                        return see_direction; // Return see_direction if no wall found
                    }
                }
                break;
            case LEFT:
                for (int i = 1; i < abs(ghost_x - pacman_x); i++) { // Corrected abs calculation
                    if (!is_wall(pacman_y, pacman_x + i)) { // Corrected coordinates
                        return see_direction; // Return see_direction if no wall found
                    }
                }
                break;
            case RIGHT:
                for (int i = 1; i < abs(ghost_x - pacman_x); i++) { // Corrected abs calculation
                    if (!is_wall(pacman_y, pacman_x - i)) { // Corrected coordinates
                        return see_direction; // Return see_direction if no wall found
                    }
                }
                break;
        }
    }


    printf("MOVING RANDOMLY\n");

    switch (rand() % 4) {
        case 0:
            see_direction = UP;
            break;
        case 1:
            see_direction = DOWN;
            break;
        case 2:
            see_direction = LEFT;
            break;
        case 3:
            see_direction = RIGHT;
            break;
    }

    return see_direction;

}