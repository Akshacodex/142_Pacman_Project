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
    int nY = *y, nX = *x;


    return MOVED_OKAY;
}

int is_wall(int y, int x) {
    return NOT_WALL;
}

char * load_map(char * filename, int *map_height, int *map_width) {
    FILE *file = fopen("map.txt", "r");

    if (!file) {
        return NULL;
    }
    char *temp_map = (char *)malloc(500 * sizeof(char));
    int w = 0, h = 0;
    char characters;
    int index = 0;
    do{
        characters= getc(file);
        if (characters == "\n") {
            h++;
        }
        else if (characters == 'W' || characters == 'G' || characters== '.' || characters=='P'){
            temp_map[index] = characters;
            index++;
            w++;
        }

    }while(characters!=EOF);

    char *real_map = (char *)malloc(h*w * sizeof(char));
    for (int i =0; i < index; i++){
        real_map[i]=temp_map[i];
    }
    free(temp_map);
    return real_map;

    *map_height = h;
    *map_width = w;

    return NULL;
}