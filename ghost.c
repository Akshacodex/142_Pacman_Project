// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "ghost.h"
#include "map.h"


char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x) {

    char see_direction = SEES_NOTHING;


    if (ghost_x == pacman_x && ghost_y == pacman_y) {
        return EATING_PACMAN;
    } else if (ghost_y == pacman_y && abs(ghost_x - pacman_x) > 0) {
        if (pacman_x > ghost_x) {
            see_direction = RIGHT;
        } else {
            see_direction = LEFT;
        }
    } else if (pacman_x == ghost_x && abs(ghost_y - pacman_y) > 0) {
        if (pacman_y > ghost_y) {
            see_direction = DOWN;
        } else {
            see_direction = UP;
        }
    }

    if (see_direction != SEES_NOTHING) {
        switch (see_direction) {
            case UP:
                for (int i = 1; i < abs(ghost_y - pacman_y); i++) {
                    if (!is_wall(pacman_y + i, pacman_x)) {
                        return see_direction;
                    }
                }
                break;
            case DOWN:
                for (int i = 1; i < abs(ghost_y - pacman_y); i++) {
                    if (!is_wall(pacman_y - i, pacman_x)) {
                        return see_direction;
                    }
                }
                break;
            case LEFT:
                for (int i = 1; i < abs(ghost_x - pacman_x); i++) {
                    if (!is_wall(pacman_y, pacman_x + i)) {
                        return see_direction;
                    }
                }
                break;
            case RIGHT:
                for (int i = 1; i < abs(ghost_x - pacman_x); i++) {
                    if (!is_wall(pacman_y, pacman_x - i)) {
                        return see_direction;
                    }
                }
                break;
        }
    }

//    printf("MOVING RANDOMLY\n");

    return MOVE_RANDOMLY;
}