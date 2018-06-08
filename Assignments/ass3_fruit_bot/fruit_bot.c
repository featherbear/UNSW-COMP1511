// fruit_bot.c
// Assignment 3, COMP1511 18s1: Fruit Bot
//
// This program by Andrew Jin-Meng Wong (z5206677) on 16/05/2018

///home/cs1511/bin/fruit_bot_referee --no_valgrind fruit_bot.c -w large | tail -n 5 | head -n 1

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "fruit_bot.h"

#define DEBUG 1
#define debug(fmt, ...) do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

void print_player_name(void);

void print_move(struct bot *me);

void run_unit_tests(void);

/* DEFINES */
#define TRUE 1
#define FALSE 0

#define TRADE_DIRECTION_SELLER -1
#define TRADE_DIRECTION_NONE 0
#define TRADE_DIRECTION_BUYER 1

#define NAME_NOTHING "Nothing"
#define NAME_ELECTRICITY "Electricity"
#define NAME_ANYTHING "Anything"


/* FUNCTION PROTOTYPES */

void sell(int quantity);

void buy(int quantity);

void moveBy(int distance);

void moveTo(struct location *origin, struct location *destination);

int checkElectricity(struct bot *me, struct location *origin, struct location *destination,
                     struct location **locations, int locationsCount);

int locationBuys(char *fruit, struct location *location);

int locationSells(char *fruit, struct location *location);

int findBuyers(char *item, struct location **locations, int locationsCount, struct location **results);

int findSellers(char *item, struct location **locations, int locationsCount, struct location **results);

struct location *findClosestBuyer(char *item, struct location *currentLocation,
                                  struct location **locations, int locationsCount);

struct location *findClosestSeller(char *item, struct location *currentLocation,
                                   struct location **locations, int locationsCount);

int countBotsInLocation(struct location *location);

int quantitySellable(char *fruit, struct location **locations, int locationsCount);

int isAFruit(char *string);

int arrayHasString(char *string, char array[][MAX_NAME_CHARS], int arrayLength);

int getTradeDirection(struct location *location);

int getDistance(struct location *origin, struct location *destination);

int getDistanceAbs(struct location *origin, struct location *destination);

int abs(int a);

int min(int a, int b);




/* FUNCTIONS */

// Prints the command to sell
void sell(int quantity) {
    printf("Sell %d\n", quantity);
}

// Prints the command to buy
void buy(int quantity) {
    printf("Buy %d\n", quantity);
}

// Prints the command to move, given a certain distance
void moveBy(int distance) {
    printf("Move %d\n", distance);
}

// Prints the command to move, given a starting and ending location
void moveTo(struct location *origin, struct location *destination) {
    moveBy(getDistance(origin, destination));
}

// Checks the bot's remaining electricity and purchases electricity if necessary
// Returns TRUE if the function makes a move, else FALSE
int checkElectricity(struct bot *me, struct location *origin, struct location *destination,
                     struct location **locations, int locationsCount) {

    // Find the bot's remaining electricity level as a percentage
    double electricity = (double) me->battery_level / me->battery_capacity;
    int approximateDistancePerMove = locationsCount / 4;
    int maxCapacity = (int) (0.75 * me->battery_capacity);

    struct location *electricityClosestOrigin = findClosestSeller(NAME_ELECTRICITY, origin, locations, locationsCount);

    // Check if an electricity seller exists, and if the bot requires electricity
    if (electricityClosestOrigin
        && electricity < 0.65
        && me->turns_left > 2
        && me->battery_level < approximateDistancePerMove * me->turns_left) {

        // If the current place sells electricity, then buy enough to get to about 75%
        if (locationSells(NAME_ELECTRICITY, origin)) {
            buy(maxCapacity - me->battery_level);
            return TRUE;
        }

        // If the bot's electricity is critically low, prioritise recharging
        if (electricity < 0.3 && me->turns_left > 3 &&
            getDistanceAbs(origin, electricityClosestOrigin) <= me->battery_level) {
            moveTo(origin, electricityClosestOrigin);
            return TRUE;
        }

        struct location *electricityClosestDestination = findClosestSeller(NAME_ELECTRICITY, destination,
                                                                           locations, locationsCount);
        // If there is an electricity seller along the way to the destination, then stop there first
        if (electricity < 0.5
            && abs(getDistance(origin, destination) + getDistance(destination, electricityClosestDestination)) <
               getDistanceAbs(origin, destination) + getDistanceAbs(destination, electricityClosestDestination)) {
            moveTo(origin, electricityClosestDestination);
            return TRUE;
        }
    }
    return FALSE;
}

// Check if a location is still buying a certain fruit
// Does not consider "Anything"
int locationBuys(char *fruit, struct location *location) {
    return ((strcmp(location->fruit, fruit) == 0)                   // fruit matches
            && getTradeDirection(location) == TRADE_DIRECTION_BUYER // location is a buyer
            && location->quantity > 0);                             // location is still buying
}

// Check if a location is still selling a certain fruit
int locationSells(char *fruit, struct location *location) {
    return (strcmp(location->fruit, fruit) == 0                      // fruit matches
            && getTradeDirection(location) == TRADE_DIRECTION_SELLER // location is a seller
            && location->quantity > 0);                              // location is still selling
}

// Search the world for buyers of a certain fruit. Returns the number of locations found
int findBuyers(char *item, struct location **locations, int locationsCount, struct location **results) {
    int resultsCount = 0;

    int locationCounter;
    for (locationCounter = 0; locationCounter < locationsCount; locationCounter++) {
        // If a location buys a certain fruit, store that location and increase the results counter
        if (locationBuys(item, locations[locationCounter])) {
            results[resultsCount] = locations[locationCounter];
            resultsCount++;
        }
    }

    return resultsCount;
}

// Search the world for sellers of a certain fruit. Returns the number of locations found
int findSellers(char *item, struct location **locations, int locationsCount, struct location **results) {
    int resultsCount = 0;

    int locationCounter;
    for (locationCounter = 0; locationCounter < locationsCount; locationCounter++) {
        // If a location sells a certain fruit, store that location and increase the results counter
        if (locationSells(item, locations[locationCounter])) {
            results[resultsCount] = locations[locationCounter];
            resultsCount++;
        }
    }

    return resultsCount;
}

// Search the world for buyers of a certain fruit, and returns the buyer with the closest distance from the origin
struct location *findClosestBuyer(char *item, struct location *currentLocation,
                                  struct location **locations, int locationsCount) {

    struct location *buyers[MAX_LOCATIONS];
    int buyersCount = findBuyers(item, locations, locationsCount, buyers);

    struct location *nearestLocation = NULL;
    int nearestMagnitude = -1;

    int buyerCounter;
    for (buyerCounter = 0; buyerCounter < buyersCount; buyerCounter++) {
        int distance = getDistanceAbs(currentLocation, buyers[buyerCounter]);
        if (distance < nearestMagnitude || nearestMagnitude == -1) {
            nearestLocation = buyers[buyerCounter];
            nearestMagnitude = distance;
        }
    }

    return nearestLocation;
}

// Search the world for sellers of a certain fruit, and returns the seller with the closest distance from the origin
struct location *findClosestSeller(char *item, struct location *currentLocation,
                                   struct location **locations, int locationsCount) {

    struct location *sellers[MAX_LOCATIONS];
    int sellersCount = findSellers(item, locations, locationsCount, sellers);

    struct location *nearestLocation = NULL;
    int nearestMagnitude = -1;

    int sellerCounter;
    for (sellerCounter = 0; sellerCounter < sellersCount; sellerCounter++) {
        int distance = getDistanceAbs(currentLocation, sellers[sellerCounter]);
        if (distance < nearestMagnitude || nearestMagnitude == -1) {
            nearestLocation = sellers[sellerCounter];
            nearestMagnitude = distance;
        }
    }

    return nearestLocation;
}

// Return the number of bots in a given location
int countBotsInLocation(struct location *location) {
    int count = 0;

    struct bot_list *cur = location->bots;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }

    return count;
}

// Returns the total units of a certain fruit that can still be sold (bought by the locations)
int quantitySellable(char *fruit, struct location **locations, int locationsCount) {
    int availableQuantity = 0;

    int locationCounter;
    for (locationCounter = 0; locationCounter < locationsCount; locationCounter++) {
        if (locationBuys(fruit, locations[locationCounter])) {
            availableQuantity += locations[locationCounter]->quantity;
        }
    }

    return availableQuantity;
}

// Check if a given string is a fruit
int isAFruit(char *string) {
    return !(string == NULL                           // Ensure string is not NULL
             || strcmp(string, NAME_ELECTRICITY) == 0 // Ensure string is not "Electricity"
             || strcmp(string, NAME_NOTHING) == 0     // Ensure string is not "Nothing"
             || strcmp(string, NAME_ANYTHING) == 0);  // Ensure string is not "Anything"
}

// Check if a string is in an array
int arrayHasString(char *string, char array[][MAX_NAME_CHARS], int arrayLength) {
    if (string != NULL) {
        int index;
        for (index = 0; index < arrayLength; index++) {
            // String matches, return true
            if (strcmp(string, array[index]) == 0) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

// Checks whether a location is a seller or a buyer
int getTradeDirection(struct location *location) {
    // If a location lists a negative price, they are selling items to the bots
    if (location->price < 0) {
        return TRADE_DIRECTION_SELLER;
    }

    // If a location lists a positive price, they are buying items from the bots
    if (location->price > 0) {
        return TRADE_DIRECTION_BUYER;
    }

    // A location with a price of 0 is neither buying nor selling items
    return TRADE_DIRECTION_NONE;
}


// Find the closest signed distance between two locations
int getDistance(struct location *origin, struct location *destination) {
    struct location *currentLocation;

    // Both distances will be stored as positive integers in the function

    int distanceEast = 0;
    currentLocation = origin;
    while (currentLocation != destination) {
        distanceEast++;
        currentLocation = currentLocation->east;
    }

    int distanceWest = 0;
    currentLocation = origin;
    while (currentLocation != destination) {
        distanceWest++;
        currentLocation = currentLocation->west;
    }

    // Return the smallest distance, including signed direction
    if (distanceWest < distanceEast) {
        return -distanceWest;
    } else {
        return distanceEast;
    }
}

// Find the closest distance between two locations
int getDistanceAbs(struct location *origin, struct location *destination) {
    return abs(getDistance(origin, destination));
}

// Return the absolute value of a given number
int abs(int a) {
    return a > 0 ? a : -a;
}

// Return `a` or `b`, whichever value is lower
int min(int a, int b) {
    return a < b ? a : b;
}

// YOU SHOULD NOT NEED TO CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    if (argc > 1) {
        // supply any command-line argument to run unit tests
        run_unit_tests();
        return 0;
    }

    struct bot *me = fruit_bot_input(stdin);
    if (me == NULL) {
        print_player_name();
    } else {
        print_move(me);
    }

    return 0;
}

void print_player_name(void) {
    printf("looloo");
}

// print_move - should print a single line indicating
//              the move your bot wishes to make
//
// This line should contain only the word Move, Sell or Buy
// followed by a single integer
void print_move(struct bot *me) {
    // Count of bots in the world
    int botsCount = 0;

    // Array of unique fruits in the world
    int fruitsCount = 0;
    char fruits[MAX_FRUIT_TYPES][MAX_NAME_CHARS] = {{'\0'}};

    // Array of locations in the world
    int locationsCount = 0;
    struct location *locations[MAX_LOCATIONS];

    struct location *currentLocation = me->location;
    struct location *destination = me->location;
    while (currentLocation != destination || locationsCount == 0) {
        // Add the number of bots found in the location
        botsCount += countBotsInLocation(currentLocation);

        // Store and count the unique fruits traded in the world
        char *fruit = currentLocation->fruit;
        if (isAFruit(fruit) && !arrayHasString(fruit, fruits, fruitsCount)) {
            strcpy(fruits[fruitsCount], fruit);
            fruitsCount++;
        }

        // Store the location
        locations[locationsCount] = currentLocation;
        locationsCount++;

        // Go to the next location in the world
        currentLocation = currentLocation->east;
    }

    // If there are more then one bot(s) in the world, it is therefore a multi-bot world
    int isMulti = botsCount > 1;



    //////////////////////////////////////////////////////////////////////
    debug("Cash: $%d\n", me->cash);
    debug("Battery: %d/%d kJ\n", me->battery_level, me->battery_capacity);
    debug("Capacity: %d/%d kg\n", me->fruit_kg, me->maximum_fruit_kg);
    debug("Fruit: %s\n", isAFruit(me->fruit) ? me->fruit : "Nothing");
    debug("Location: %s\n", me->location->name);
    debug("Bots here: %d\n", countBotsInLocation(currentLocation));
    debug("Bots in world: %d\n", botsCount);
    //////////////////////////////////////////////////////////////////////

    // The bot is holding fruit - find a location to sell the fruit to
    if (me->fruit_kg > 0) {

        // Find all the buyers of the fruit that the bot holds
        struct location *buyers[MAX_LOCATIONS];
        int buyersCount = findBuyers(me->fruit, locations, locationsCount, buyers);

        double bestProfit = 0;
        struct location *buyer = NULL;

        // Find the best buyer
        int buyerCounter;
        for (buyerCounter = 0; buyerCounter < buyersCount; buyerCounter++) {
            // Calculate the profitability of a buyer
            //   PROFIT = PRICE * QUANTITY / DISTANCE
            // One is added to the distance to prevent division by zero.
            double profitability = (double) buyers[buyerCounter]->price * buyers[buyerCounter]->quantity /
                                   (getDistanceAbs(currentLocation, buyers[buyerCounter]) + 1);

            // Update the location of the best buyer if they are more profitable
            if (profitability > bestProfit) {
                bestProfit = profitability;
                buyer = buyers[buyerCounter];
            }
        }

        // If there are no buyers of a fruit, move to the closest scrapheap
        if (buyersCount == 0) {
            buyer = findClosestBuyer(NAME_ANYTHING, currentLocation, locations, locationsCount);
        }

        int distanceToBuyer = getDistance(currentLocation, buyer);
        if (distanceToBuyer == 0) {
            // Distance is zero, meaning that the bot is at the location of the buyer
            sell(min(me->fruit_kg, buyer->quantity));
        } else {
            // Buy electricity if necessary, else move to the buyer
            if (!checkElectricity(me, currentLocation, buyer, locations, locationsCount)) {
                moveTo(currentLocation, buyer);
            }
        }
        return;

    } else {
        // Bot is not holding fruit, so find the best fruit and locations to trade

        // DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG
        // Find best sellers and buyers of fruit
        if (DEBUG) {
            int fruitCounter;
            for (fruitCounter = 0; fruitCounter < fruitsCount; fruitCounter++) {
                struct location *bestBuyer = NULL;
                struct location *bestSeller = NULL;
                int locationCounter;
                for (locationCounter = 0; locationCounter < locationsCount; locationCounter++) {
                    if (locationSells(fruits[fruitCounter], locations[locationCounter])
                        && (bestSeller == NULL || (locations[locationCounter]->price > bestSeller->price))) {
                        bestSeller = locations[locationCounter];
                    }
                    if ((locationBuys(fruits[fruitCounter], locations[locationCounter]) ||
                         locationBuys(NAME_ANYTHING, locations[locationCounter]))
                        && (bestBuyer == NULL || (locations[locationCounter]->price > bestBuyer->price))) {
                        bestBuyer = locations[locationCounter];
                    }
                }
                if (bestSeller && bestBuyer) {
                    debug("      %s: Best seller and buyer is %s and %s\n",
                          fruits[fruitCounter], bestSeller->name, bestBuyer->name);
                } else {
                    debug("      %s: Can no longer trade\n", fruits[fruitCounter]);
                }
            }
        }
        // DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG

        double bestProfit = 0;
        struct location *bestBuyer = NULL;
        struct location *bestSeller = NULL;
        char *bestFruit = NAME_NOTHING;

        currentLocation = me->location;

        // Find all of the sellers of electricity
        struct location *electricitySuppliers[MAX_LOCATIONS];
        int electricitySuppliersCount = findSellers(NAME_ELECTRICITY, locations, locationsCount, electricitySuppliers);

        // Find the average price of electricity
        int electricityCostSum = 0;
        double electricityCost = 1;
        int electricitySupplierCounter;
        // Add all of the electricity prices
        for (electricitySupplierCounter = 0;
             electricitySupplierCounter < electricitySuppliersCount; electricitySupplierCounter++) {
            electricityCostSum += electricitySuppliers[electricitySupplierCounter]->price;
        }
        // Find the average price
        if (electricitySuppliersCount > 0) {
            electricityCost = (double) abs(electricityCostSum) / electricitySuppliersCount;
        }

        // Find the best buyer and best seller of the best fruit to trade
        int fruitCounter;
        for (fruitCounter = 0; fruitCounter < fruitsCount; fruitCounter++) {
            // Find the buyers of a fruit
            struct location *buyers[MAX_LOCATIONS];
            int buyersCount = findBuyers(fruits[fruitCounter], locations, locationsCount, buyers);

            // Find the sellers of a fruit
            struct location *sellers[MAX_LOCATIONS];
            int sellersCount = findSellers(fruits[fruitCounter], locations, locationsCount, sellers);

            // For each seller, find the best buyer
            int sellerCounter;
            for (sellerCounter = 0; sellerCounter < sellersCount; sellerCounter++) {
                int buyerCounter;
                for (buyerCounter = 0; buyerCounter < buyersCount; buyerCounter++) {
                    // PROFIT = sell price / buy price
                    double profitRatio = (double) buyers[buyerCounter]->price / abs(sellers[sellerCounter]->price);

                    // Total distance to move to the seller, and then move to the buyer
                    int absoluteDistance = getDistanceAbs(currentLocation, sellers[sellerCounter])
                                           + getDistanceAbs(sellers[sellerCounter], buyers[buyerCounter]);

                    // Cost of travel
                    double travelCost = absoluteDistance * electricityCost;

                    // If a buyer/seller pair is better than the previous best, update the best buyer and seller
                    if (profitRatio > 1.0 && profitRatio / travelCost > bestProfit) {
                        bestProfit = profitRatio / travelCost;
                        bestBuyer = buyers[buyerCounter];
                        bestSeller = sellers[sellerCounter];
                        bestFruit = fruits[fruitCounter];
                    }
                }
            }
        }


        int bestDistance = getDistanceAbs(currentLocation, bestSeller) + getDistanceAbs(bestSeller, bestBuyer);
        int turnsNeeded = bestDistance / me->maximum_move + (bestDistance % me->maximum_move != 0) + 2;

        if (DEBUG && bestProfit != 0) {
            debug("\n\nThe most profitable fruit is the %s, where we can move from %s to %s to %s.\nProfit ratio: %lf\nDistance: %d + %d = %d steps\n\n",
                  bestFruit, currentLocation->name, bestSeller->name, bestBuyer->name, bestProfit,
                  getDistanceAbs(currentLocation, bestSeller), getDistanceAbs(bestSeller, bestBuyer),
                  getDistanceAbs(currentLocation, bestSeller) + getDistanceAbs(bestSeller, bestBuyer));
        };

        // Check if there are no more profitable trades, or that there are not enough remaining turns
        if (bestProfit == 0 || me->turns_left < turnsNeeded) {
            debug("%s", "No more profitable trades, or not enough turns left, wasting moves now");
            moveBy(0);
            return;
        }

        // If the bot is at the best seller's location, buy fruit from the seller
        if (getDistance(currentLocation, bestSeller) == 0) {
            int competitorLimit = quantitySellable(bestFruit, locations, locationsCount);

            // Take precaution as to how much fruit the bot can buy as other bots will be selling too
            if (isMulti) {
                competitorLimit = (int) (0.75 * competitorLimit);
            }

            // Keep 10% of the bot's money for buying electricity
            int conservativeLimit = abs((int) (0.9 * me->cash / bestSeller->price));

            buy(min(competitorLimit, conservativeLimit));
        } else {
            if (!checkElectricity(me, currentLocation, bestSeller, locations, locationsCount)) {
                moveTo(currentLocation, bestSeller);
            }
        }
        return;
    }
}

/*
 * = UNIT TESTS =
 * Check each function to ensure that it returns the expected values
 * Can't perform asserts for void functions like `sell`, `buy`, `moveBy` and `moveTo`
 * `checkElectricity` also won't be tested as it just extended player logic for the void function `print_move`
 */
void run_unit_tests(void) {

    /* Create a world */
    struct location locationOne = {
            .name = "Environment Team Recycling Incentive",
            .fruit = "Trash",
            .quantity = 150,
            .price = 1,
    };

    struct location locationTwo = {
            .name = "Krispy Kreme",
            .fruit = "Doughnuts", // Yes, they're not spelt "donut".
            .quantity = 100,
            .price = -1,
            .west = &locationOne
    };

    struct bot bot;
    struct bot_list bot_list = {
            .bot = &bot,
            .next = NULL
    };

    struct location locationThree = {
            // If these suckers will pay for degrees,
            // well then they'll pay for anything! D:
            .name = "University",
            .fruit = "Anything",
            .quantity = 2000,
            .price = 100,
            .west = &locationTwo,
            .bots = &bot_list
    };

    struct location locationFour = {
            .name = "Parent's Basement",
            .fruit = "Nothing",
            .quantity = 5,
            .price = 0,
            .west = &locationThree,
            .east = &locationOne,
            .bots = NULL
    };

    locationOne.west = &locationFour;
    locationOne.east = &locationTwo;
    locationTwo.east = &locationThree;
    locationThree.east = &locationFour;

    const int locationsCount = 4;
    struct location *locations[locationsCount] = {&locationOne, &locationTwo, &locationThree, &locationFour};



    /* Begin tests */

    // function: locationBuys
    // return: TRUE if a location buys a fruit
    //         FALSE otherwise
    assert(locationBuys("Trash", &locationOne) == TRUE);
    assert(locationBuys("Trash", &locationTwo) == FALSE);
    assert(locationBuys("Trash", &locationThree) == FALSE);
    assert(locationBuys("Trash", &locationFour) == FALSE);
    /* Location two SELLS doughnuts, not buys */
    assert(locationBuys("Doughnuts", &locationTwo) == FALSE);



    // function: locationSells
    // return: TRUE if a location sells a fruit
    //         FALSE otherwise
    /* Location two is the only seller of Doughnuts */
    assert(locationSells("Doughnuts", &locationOne) == FALSE);
    assert(locationSells("Doughnuts", &locationTwo) == TRUE);
    assert(locationSells("Doughnuts", &locationThree) == FALSE);
    assert(locationSells("Doughnuts", &locationFour) == FALSE);
    /* Location one BUYS trash, not sells */
    assert(locationSells("Trash", &locationOne) == FALSE);



    // function: findBuyers
    // return: Count of buyers in the world
    /* There is only one buyer of Trash in the world */
    struct location *buyersOfTrash[locationsCount];
    assert(findBuyers("Trash", locations, locationsCount, buyersOfTrash) == 1);
    assert(strcmp(buyersOfTrash[0]->fruit, "Trash") == 0);
    /* There are no buyers of Apples in the world */
    struct location *buyersOfApples[locationsCount];
    assert(findBuyers("Apples", locations, locationsCount, buyersOfApples) == 0);



    // function: findSellers
    // return: Count of sellers in the world
    /* There is only one seller of Trash in the world */
    struct location *sellersOfDoughnuts[locationsCount];
    assert(findSellers("Doughnuts", locations, locationsCount, sellersOfDoughnuts) == 1);
    assert(strcmp(sellersOfDoughnuts[0]->fruit, "Doughnuts") == 0);
    /* There are no sellers of Apples in the world */
    struct location *sellersOfApples[locationsCount];
    assert(findSellers("Apples", locations, locationsCount, sellersOfApples) == 0);



    // function: findClosestBuyer
    // return: Location of the closest buyer of an item
    assert(findClosestBuyer("Trash", &locationOne, locations, locationsCount) == &locationOne);
    assert(findClosestBuyer("Doughnuts", &locationOne, locations, locationsCount) == NULL);
    assert(findClosestBuyer("Anything", &locationOne, locations, locationsCount) == &locationThree);



    // function: findClosestSeller
    // return: Location of the closest seller of an item
    assert(findClosestSeller("Doughnuts", &locationOne, locations, locationsCount) == &locationTwo);
    assert(findClosestSeller("Doughnuts", &locationTwo, locations, locationsCount) == &locationTwo);
    assert(findClosestSeller("Apples", &locationOne, locations, locationsCount) == NULL);



    // function: countBotsInLocation
    // return: Count of bots in a given location
    assert(countBotsInLocation(&locationThree) == 1);
    assert(countBotsInLocation(&locationFour) == 0);



    // function: quantitySellable
    // return: Number of units of a fruit left unbought
    assert(quantitySellable("Trash", locations, locationsCount) == 150);
    assert(quantitySellable("Apples", locations, locationsCount) == 0);



    // function: isAFruit
    // return: TRUE if a string is a valid fruit name
    //         FALSE otherwise
    assert(isAFruit("Apples") == TRUE);
    // NULL, Electricity, Anything and Nothing are not considered fruits
    assert(isAFruit(NULL) == FALSE);
    assert(isAFruit(NAME_ELECTRICITY) == FALSE);
    assert(isAFruit(NAME_ANYTHING) == FALSE);
    assert(isAFruit(NAME_NOTHING) == FALSE);


    // function: arrayHasString
    // return: TRUE if an array contains a string
    //         FALSE otherwise
    const int arraySize = 5;
    char array[arraySize][MAX_NAME_CHARS] = {"A", "B", "C", "D", "E"};
    assert(arrayHasString("A", array, arraySize) == TRUE);
    assert(arrayHasString("B", array, arraySize) == TRUE);
    assert(arrayHasString("C", array, arraySize) == TRUE);
    assert(arrayHasString("D", array, arraySize) == TRUE);
    assert(arrayHasString("E", array, arraySize) == TRUE);
    assert(arrayHasString("F", array, arraySize) == FALSE);
    assert(arrayHasString("", array, arraySize) == FALSE);
    assert(arrayHasString(NULL, array, arraySize) == FALSE);



    // function: getTradeDirection
    // return: TRADE_DIRECTION_SELLER if the location is a seller and still sells
    //         TRADE_DIRECTION_BUYER  if the location is a buyer and still buys
    //         TRADE_DIRECTION_NONE   otherwise
    assert(getTradeDirection(&locationOne) == TRADE_DIRECTION_BUYER);
    assert(getTradeDirection(&locationTwo) == TRADE_DIRECTION_SELLER);
    assert(getTradeDirection(&locationThree) == TRADE_DIRECTION_BUYER);
    assert(getTradeDirection(&locationFour) == TRADE_DIRECTION_NONE);



    // function: getDistance
    // return: Distance between two locations
    assert(getDistance(&locationOne, &locationOne) == 0);
    assert(getDistance(&locationOne, &locationTwo) == 1);
    assert(getDistance(&locationOne, &locationThree) == 2);
    assert(getDistance(&locationOne, &locationFour) == -1);



    // function: getDistanceAbs
    // return: Absolute value of the distance between two locations
    assert(getDistanceAbs(&locationOne, &locationOne) == 0);
    assert(getDistanceAbs(&locationOne, &locationTwo) == 1);
    assert(getDistanceAbs(&locationOne, &locationThree) == 2);
    assert(getDistanceAbs(&locationOne, &locationFour) == 1);



    // function: abs
    // return: Absolute value
    assert(abs(0) == 0);
    assert(abs(-1) == 1);
    assert(abs(1) == 1);



    // function: min
    // return: Smallest value of two inputs
    assert(min(0, 0) == 0);
    assert(min(0, 1) == 0);
    assert(min(1, 0) == 0);
    assert(min(-1, 0) == -1);
    assert(min(0, -1) == -1);
}
