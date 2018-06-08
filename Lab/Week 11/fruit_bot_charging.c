#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "fruit_bot.h"

int nearest_electricity(struct bot *b);

int main(int argc, char *argv[]) {
    struct bot *me = fruit_bot_input(stdin);

    int distance = nearest_electricity(me);
    printf("Distance to nearest available electricity is %d\n", distance);

    return 0;
}


// return distance to nearest electricity
// if nearest electricity is west return negative int
// if nearest electricity is current location return 0

int nearest_electricity(struct bot *b) {


//
//    Note you need to check that the location sells Electricity and that it has some kJ left to sell.
//
//            If the bot is at a location that has electricity for sale, it should print 0.
//      If the nearest location eastwards. It should print a positive integer.
//            If the nearest location is westwards. It should print a negative integer.
//            The main function in fruit_bot_charging.c has this code:
    struct location *currentPosition = b->location;
    int nearestEast = 0;
    int found = 0;
    while (!found && (currentPosition != b->location || nearestEast == 0)) {
        if (strcmp(currentPosition->fruit, "Electricity") == 0 && currentPosition->quantity > 0) {
            found = 1;
        } else {
            currentPosition = currentPosition->east;
            nearestEast++;
        }
    }

    currentPosition = b->location;
    int nearestWest = 0;
    found = 0;
    while (!found && (currentPosition != b->location || nearestWest == 0)) {
        if (strcmp(currentPosition->fruit, "Electricity") == 0 && currentPosition->quantity > 0) {
            found = 1;
        } else {
            currentPosition = currentPosition->west;
            nearestWest++;
        }
    }

    return nearestEast < nearestWest ? nearestEast : -nearestWest;
}
