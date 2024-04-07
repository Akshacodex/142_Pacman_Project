// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdlib.h>
#include "defines.h"
#include "ghost.h"
#include "map.h"


char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x) {

    //The ghost doesn't see pacman at first, so its seeing direction is initially set to SEES_NOTHING
    char see_direction = SEES_NOTHING;

    //if the ghost and pacman are in the same position, then pacman will be eaten
    if (ghost_x == pacman_x && ghost_y == pacman_y) {
        return EATING_PACMAN;
    } else if (ghost_y == pacman_y && abs(ghost_x - pacman_x) > 0) { //else if pacman and the ghost are on the same row but different columns
        if (pacman_x > ghost_x) { //if pacman is to the right of the ghost
            see_direction = RIGHT; //the ghost looks to the right
        } else {
            see_direction = LEFT; //or else, the ghost looks to the left
        }
    } else if (pacman_x == ghost_x && abs(ghost_y - pacman_y) > 0) { //else if pacman and the ghost are on the same column but different rows
        if (pacman_y > ghost_y) { //if pacman is under the ghost
            see_direction = DOWN; //the ghost looks down
        } else {
            see_direction = UP; //or else the ghost looks up
        }
    }

    if (see_direction != SEES_NOTHING) { //if the ghost sees pacman
        switch (see_direction) { //there are 4 possibilities when the ghost sees pacman
            case UP: //when the ghost sees pacman on top of itself
                for (int i = 1; i < abs(ghost_y - pacman_y); i++) { //loop counter counts the space between the ghost and pacman
                    if (!is_wall(pacman_y + i, pacman_x)) { //if there isn't a wall then it will look up
                        return see_direction;
                    }
                }
                break;
            case DOWN: //when the ghost sees pacman below itself
                for (int i = 1; i < abs(ghost_y - pacman_y); i++) {  //loop counter counts the space between the ghost and pacman
                    if (!is_wall(pacman_y - i, pacman_x)) { //if there isn't a wall then it will look down
                        return see_direction;
                    }
                }
                break;
            case LEFT: //when the ghost sees pacman to the left of itself
                for (int i = 1; i < abs(ghost_x - pacman_x); i++) { //loop counter counts the space between the ghost and pacman
                    if (!is_wall(pacman_y, pacman_x + i)) { //if there isn't a wall then it will look to the left
                        return see_direction;
                    }
                }
                break;
            case RIGHT: //when the ghost sees pacman to the right of itself
                for (int i = 1; i < abs(ghost_x - pacman_x); i++) { //loop counter counts the space between the ghost and pacman
                    if (!is_wall(pacman_y, pacman_x - i)) { //if there isn't a wall then it will look to the right
                        return see_direction;
                    }
                }
                break;
        }
    }

    return MOVE_RANDOMLY;
