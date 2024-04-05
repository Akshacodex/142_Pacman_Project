// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "colours.h"
#include "map.h"
#include "ghost.h"

extern char *map, *dot_map;

int w = 0, h = 1;

int move_actor(int * y, int * x, char direction, int eat_dots) {
    int prevY = *y;
    int prevX = *x;


    switch (direction) {
        case UP:
            if (*y > 0 && !is_wall(*y - 1, *x)) {
                (*y)--;
            } else {
                return MOVED_WALL;
            }
            break;
        case LEFT:
            if (*x > 0 && !is_wall(*y, *x - 1)) {
                (*x)--;
            } else {
                return MOVED_WALL;
            }
            break;
        case DOWN:
            if (*y < map_height - 1 && !is_wall(*y + 1, *x)) {
                (*y)++;
            } else {
                return MOVED_WALL;
            }
            break;
        case RIGHT:
            if (*x < map_width - 1 && !is_wall(*y, *x + 1)) {
                (*x)++;
            } else {
                return MOVED_WALL;
            }
            break;
        default:
            return MOVED_INVALID_DIRECTION;
    }

    if (eat_dots == EAT_DOTS) {
        map[*y * w + *x] = PACMAN;
        map[prevY * w + prevX] = EMPTY;
        dot_map[prevY * w + prevX] = EMPTY;
    } else {
        map[*y * w + *x] = GHOST;
        map[prevY * w + prevX] = dot_map[*y * w + *x];
    }

    return MOVED_OKAY;
}

int is_wall(int y, int x) {

    if (map[y * w + x] == 'W') {
        return YES_WALL;
    } else {
        return NOT_WALL;
    }

}

char * load_map(char * filename, int* map_height, int* map_width) {

    FILE *file = fopen (filename, "r");

    if (!file) {
        return NULL;
    }

    char characters;

    do {
        characters = getc(file);
        if (characters == '\n') {
            h++;
        }
        else if (characters == WALL || characters == GHOST || characters == DOT || characters == PACMAN){
            w++;
        }
    } while(characters != EOF);

    w /= h;
    w += 2;
    h += 2;

    rewind(file);

    map = (char *)malloc((w * h) * sizeof(char));

    dot_map = (char *)malloc((w * h) * sizeof(char));

    for (int i = 0; i < w; ++i) {
        map[i] = WALL;
    }

    int counter = 0;
    for (int y = w; y < (h - 1) * w; ++y) {
        if (y % w == 0 || (y % ((2 * w - 1) + counter * w)) == 0){
            if (y % w == 0) {
                map[y] = WALL;
            }
            if (y % ((2 * w - 1) + counter * w) == 0) {
                map[y] = WALL;
                counter++;
            }
        } else {
            fscanf(file, " %c", &map[y]);
            if (map[y] == PACMAN) {
                pacX = y % w;
                pacY = y / h;
//              printf("%d, %d", pacX, pacY);
            }
            if (map[y] == GHOST) {
                ghost_X = y % w;
                ghost_Y = y / h;
//              printf("%d, %d\n", ghost_X, ghost_Y);
            }
            if (map[y] == DOT) {
                dot_map[y] = map[y];
            } else {
                dot_map[y] = ' ';
            }
        }
    }
    for (int i = (h - 1) * w; i < h * w; ++i) {
        map[i] = WALL;
    }

    fclose(file);

    *map_height = h;
    *map_width = w;

    return map;
}

void print_map(int i, int j) {
    for (int y = 0; y < j; ++y) {
        for (int x = 0; x < i; ++x) {
            switch (map[y * i + x]) {
                case WALL:
                    change_text_colour(WHITE);
                    break;
                case GHOST:
                    change_text_colour(PINK);
                    break;
                case PACMAN:
                    change_text_colour(YELLOW);
                    break;
                case DOT:
                    change_text_colour(BLUE);
                    break;
                default:
                    change_text_colour(WHITE);
                    break;
            }
            printf("%c  ", map[(y * i) + x]);
            //printf("%d  ", y * 11 + x);
        }
        printf("\n");
    }
}