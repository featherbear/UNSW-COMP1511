#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "fruit_bot.h"

void print_player_name(void);

void print_move(struct bot *b);

int main(int argc, char *argv[]) {
    struct bot *me = fruit_bot_input(stdin);
    if (me == NULL) {
        print_player_name();
    } else {
        print_move(me);
    }

    return 0;
}

void print_player_name(void) {
    printf("West McWesty");

}

// print_move - should print a single line indicating
//              the move you bot wishes to make
//
// This line should contain only the word Move, Sell or Buy
// followed by a single integer







#define TRADE_SELL -1
#define TRADE_NONE 0
#define TRADE_BUY 1


int getTradeDirection(struct location *loc) {
    if (loc->price < 0) {
        return TRADE_SELL;
    }

    if (loc->price > 0) {
        return TRADE_BUY;
    }

    return TRADE_NONE;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

#include <math.h>

void print_move(struct bot *b) {

    struct location *loc = b->location;
    int batteryDifference = b->battery_capacity - b->battery_level;
    if (batteryDifference > 0
        && strcmp(loc->fruit, "Electricity") == 0
        && loc->quantity > 0) {
        printf("Buy %d\n", batteryDifference);
        return;
    }

    if (loc->quantity > 0
        && strcmp(loc->fruit, "Apples") == 0
        && getTradeDirection(loc) == TRADE_SELL
        && b->fruit_kg == 0) {
        printf("Buy %d\n", min(loc->quantity, b->maximum_fruit_kg));
        return;

    }
    if (strcmp(loc->fruit, "Apples") == 0
        && b->fruit != NULL
        && strcmp(b->fruit, "Apples") == 0
        && getTradeDirection(loc) == TRADE_BUY
        && loc->quantity > 0
        && b->fruit_kg > 0) {
        printf("Sell %d\n", min(loc->quantity, b->fruit_kg));
        return;
    }

    printf("Move -%d\n", b->maximum_move);
    return;


    // ADD YOUR CODE HERE
}
