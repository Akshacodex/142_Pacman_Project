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

    char *real_map = (char *)malloc(121 * sizeof(char));

    for (int i = 0; i < 11; ++i) {
        real_map[i] = 'W';
    }
    int counter = 0;
    for (int y = 11; y < 121 - 11; ++y) {
        if(y%11 == 0 || (y%(21+counter*11)) == 0){
            if (y % 11 == 0) {
                real_map[y] = 'W';
            }
            if (y % (21 + counter * 11) == 0) {
                real_map[y] = 'W';
                counter++;
            }
        }else{
            fscanf(file, "%c  ", &real_map[y]);
        }
    }
    for (int i = 110; i < 121; ++i) {
        real_map[i] = 'W';
    }

    fclose(file);

    for (int y = 0; y < 11; ++y) {
        for (int x = 0; x < 11; ++x) {
            printf("%c  " ,real_map[y * 11 + x]);
            //printf("%d  ", y * 11 + x);
        }
        printf("\n");

    }

    fclose(file);

    return real_map;

    return NULL;
}