// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

extern char *map, *dot_map;
extern int width, height;

int move_actor(int * y, int * x, char direction, int eat_dots) {


    return MOVED_OKAY;
}

int is_wall(int y, int x) {


    return NOT_WALL;
}

char * load_map(char * filename, int* map_height, int* map_width) {

    FILE *file = fopen("map.txt", "r");

    if (!file) {
        exit(0);
    }

    int w = 0, h = 1;
    char characters;

    do {
        characters = getc(file);
        if (characters == '\n') {
            h++;
        }
        else if (characters == 'W' || characters == 'G' || characters== '.' || characters=='P'){
            w++;
        }
    } while(characters != EOF);

    w /= h;
    w += 2;
    h += 2;

    fseek(file, 0, SEEK_SET);

    char *real_map = (char *)malloc((w * h) * sizeof(char));

    for (int i = 0; i < w; ++i) {
        real_map[i] = 'W';
    }

    int counter = 0;
    for (int y = w; y < (h - 1) * w; ++y) {
        if (y % w == 0 || (y % ((2 * w - 1) + counter * w)) == 0){
            if (y % w == 0) {
                real_map[y] = 'W';
            }
            if (y % ((2 * w - 1) + counter * w) == 0) {
                real_map[y] = 'W';
                counter++;
            }
        } else {
            fscanf(file, " %c", &real_map[y]);
        }
    }
    for (int i = (h - 1) * w; i < h * w; ++i) {
        real_map[i] = 'W';
    }

    fclose(file);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            printf("%c  ",real_map[y * w + x]);
            // printf("%d  ", y * 11 + x);
        }
        printf("\n");
    }

    return real_map;

    return NULL;
}