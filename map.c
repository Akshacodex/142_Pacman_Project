// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "colours.h"
#include "map.h"
#include "ghost.h"

extern char *map, *dot_map;

// Variables to store width and height of map
extern int map_width, map_height;

// Variables to store map dimensions
int w = 0, h = 1;

int move_actor(int * y, int * x, char direction, int eat_dots) {

    // Storing the previous Y and X position
    int prevY = *y;
    int prevX = *x;

    // Logic to randomly moving the Ghost
    if (direction == MOVE_RANDOMLY) {
        int valid_directions[4]; // Array used to store the valid directions
        int num_valid = 0; // Variable to count the number of valid moves the ghost can move

        // Checking and storing valid direction
        if (*y > 0 && !is_wall(*y - 1, *x)) {
            valid_directions[num_valid++] = UP;
        }
        // Checking and storing valid direction
        if (*y < map_height - 1 && !is_wall(*y + 1, *x)) {
            valid_directions[num_valid++] = DOWN;
        }
        // Checking and storing valid direction
        if (*x > 0 && !is_wall(*y, *x - 1)) {
            valid_directions[num_valid++] = LEFT;
        }
        // Checking and storing valid direction
        if (*x < map_width - 1 && !is_wall(*y, *x + 1)) {
            valid_directions[num_valid++] = RIGHT;
        }

        // Shuffling the valid directions
        for (int i = num_valid - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            int temp = valid_directions[i];
            valid_directions[i] = valid_directions[j];
            valid_directions[j] = temp;
        }

        // Choosing a random direction using rand()
        direction = valid_directions[rand() % num_valid];
    }

    // Moving the actor based on the direction received from apsc142project.c Game Loop
    switch (direction) {
        case UP:
            // Checking if there's a wall in that direction
            if (*y > 0 && !is_wall(*y - 1, *x)) {
                (*y)--;
            } else {
                return MOVED_WALL;
            }
            break;
        case LEFT:
            // Checking if there's a wall in that direction
            if (*x > 0 && !is_wall(*y, *x - 1)) {
                (*x)--;
            } else {
                return MOVED_WALL;
            }
            break;
        case DOWN:
            // Checking if there's a wall in that direction
            if (*y < map_height - 1 && !is_wall(*y + 1, *x)) {
                (*y)++;
            } else {
                return MOVED_WALL;
            }
            break;
        case RIGHT:
            // Checking if there's a wall in that direction
            if (*x < map_width - 1 && !is_wall(*y, *x + 1)) {
                (*x)++;
            } else {
                return MOVED_WALL;
            }
            break;
        default:
            // If no valid move key is inputted this would be returned making the pacman stay in the same position
            return MOVED_INVALID_DIRECTION;
    }

    // Updating the map according to the action of the Pacman and Ghost
    if (eat_dots == EAT_DOTS) {
        map[*y * w + *x] = PACMAN;
        map[prevY * w + prevX] = EMPTY;
        dot_map[*y * w + *x] = EMPTY;
    } else if(eat_dots == REPLACE_DOTS) {
        map[*y * w + *x] = GHOST;
        map[prevY * w + prevX] = dot_map[prevY * w + prevX];
    }

    return MOVED_OKAY;
}

// Function to check if a position is a wall or not
int is_wall(int y, int x) {

    if (map[y * w + x] == 'W') {
        return YES_WALL;
    } else {
        return NOT_WALL;
    }

}

char * load_map(char * filename, int* map_height, int* map_width) {

    // Opening the file for reading
    FILE *file = fopen (filename, "r");

    // Checking if file opening is successful
    if (!file) {
        return NULL;
    }

    // Checking the first character of the file
    int map_check = getc(file);

    // Checking if the file character is empty by checking if there's any character
    if (map_check == EOF) {
        // If file empty, close the file
        fclose(file);
        // Return the error code
        return (char *) ERR_NO_MAP;
    }

    // Reset the file pointer to the beginning
    rewind(file);

    // Variable used store characters to find the Width and Height of the given Map
    char characters;

    // Loop to determine map Dimensions
    do {
        // Reads characters from file
        characters = getc(file);
        // Reads if there's any newline, if so increase the height counter by 1
        if (characters == '\n') {
            h++;
        }
        // Checking for W, G, ., P and if there is increasing the width
        else if (characters == WALL || characters == GHOST || characters == DOT || characters == PACMAN){
            w++;
        }
    } while(characters != EOF); // Continue until end of file is reached

    // Calculating the map Width and Height and adding +2 to factor in the surrounding Walls
    w =(w / h) + 2;
    h += 2;

    // Reset the file pointer to the beginning
    rewind(file);

    // Allocate memory for the map
    map = (char *)malloc((w * h) * sizeof(char));

    // Allocate memory for the dot map
    dot_map = (char *)malloc((w * h) * sizeof(char));

    // Initializing the pointer with the Top surrounding walls
    for (int i = 0; i < w; ++i) {
        map[i] = WALL;
    }

    // Counter for ghosts
    int ghostCounter = 0;
    // Counter to calculate the right hand side Walls location
    int counter = 0;
    for (int y = w; y < (h - 1) * w; ++y) {
        if (y % w == 0 || (y % ((2 * w - 1) + counter * w)) == 0){
            // This is for the left hand side Walls
            if (y % w == 0) {
                map[y] = WALL;
            }
            // This if for the right hand side Walls
            if (y % ((2 * w - 1) + counter * w) == 0) {
                map[y] = WALL;
                counter++;
            }
        } else {
            // Reading characters from the file into the pointer
            fscanf(file, " %c", &map[y]);

            // Locating the Pacman position
            if (map[y] == PACMAN) {
                pacX = y % w;
                pacY = y / w;
            }

            // Locating the Ghost's location
            if (map[y] == GHOST) {
                ghost_X[ghostCounter] = y % w;
                ghost_Y[ghostCounter] = y / w;
                ghostCounter++;
            }

            // Locating a dot in the Map and setting the dot inside the dot map
            if (map[y] == DOT) {
                dot_map[y] = map[y];
            } else {
                // If it's not a dot setting the location to empty
                dot_map[y] = EMPTY;
            }
        }
    }

    // The bottom row of walls that surround the map
    for (int i = (h - 1) * w; i < h * w; ++i) {
        map[i] = WALL;
    }

    // Closing the file
    fclose(file);

    // Setting map height and width
    *map_height = h;
    *map_width = w;

    // Returning pointer to the map
    return map;
}

// Function made to print the map which would make the printing more efficient so the computer wouldn't have to read the file every time
void print_map(int i, int j) {
    // Looping through rows
    for (int y = 0; y < j; ++y) {
        // Looping through columns
        for (int x = 0; x < i; ++x) {
            // Switch used to colour the map characters
            switch (map[y * i + x]) {
                case WALL:
                    change_text_colour(BLUE);
                    break;
                case DOT:
                    change_text_colour(WHITE);
                    break;
                case GHOST:
                    change_text_colour(PINK);
                    break;
                case PACMAN:
                    change_text_colour(YELLOW);
                    break;
                default:
                    change_text_colour(WHITE);
                    break;
            }
            // Printing map characters
            printf("%c  ", map[(y * i) + x]);
        }
        // Printing new line at the end of each row
        printf("\n");
    }
}