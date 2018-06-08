#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "fruit_bot.h"

void print_world(struct bot *b);

int main(void) {
    struct bot *b = fruit_bot_input(stdin);
    print_world(b);
    return 0;
}


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

char *getTradeDirectionString(int tradeDirection) {
    if (tradeDirection == TRADE_NONE) {
        return "other";
    }

    if (tradeDirection == TRADE_BUY) {
        return "buy";
    }

    if (tradeDirection == TRADE_SELL) {
        return "sell";
    }

    return "";
}

char *getUnits(struct location *loc) {
    if (strcmp(loc->fruit, "Electricity") == 0) {
        return "kJ";
    }
    return "kg";
}

int abs(int i);

int abs(int i) {
    return i > 0 ? i : -i;
}

void print_world(struct bot *b) {
    int locations = 0;
    struct location *currentLocation = b->location;

    while (currentLocation != b->location || locations == 0) {
        if (currentLocation->quantity == 0) {
            printf("%s: other\n", currentLocation->name);
        }
        else {
            printf("%s: will %s %d %s of %s for $%d\n",
                    /* X */ currentLocation->name,
                    /* will */
                   getTradeDirectionString(getTradeDirection(currentLocation)),
                   currentLocation->quantity,
                   getUnits(currentLocation),

                    /* of */
                   currentLocation->fruit,
                    /* for $ */

                   abs(currentLocation->price));
        }
        currentLocation = currentLocation->east;
        locations++;
    }
    // Put your code here to:
    // print details of all locations in the Fruit Bot world
    // starting from bot's current location and going east
}