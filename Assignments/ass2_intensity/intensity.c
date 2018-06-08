// intensity.c
// Assignment 2, COMP1511 18s1: Intensity
//
// This program by Andrew Jin-Meng Wong (z5206677) on 21/04/2018
//

/*
 * // Progress Log / Change Log //
 * DD/MM/YYYY | HHMM | Entry
 * -----------|------|-------------
 * 21/04/2018 | 1703 | Started assignment
 *            | 2039 | Finish basic implementation of game function logic
 *            | 2048 | Fix card discard function
 * 22/04/2018 | 1610 | Fix logic to not play a calf on first turn if a calf has not been played yet
 *            |      | Refactored calf card checking into `isCalf`
 * 23/04/2018 | 1142 | Improve program logic
 * 24/04/2018 | 0041 | Refactored code into functions
 *            | 2329 | Optimised code given the confirmation that the game rules are fixed
 * 25/04/2018 | 1547 | Improved logic
 *            | 1654 | Code documentation and code cleaning
 * 29/04/2018 | 1812 | Rewrote game logic. Testing for efficiency now. => 81%
 *            | 1952 | Jokes, efficiency dropped to 73%... R E V E R T
 * 08/05/2018 | 1329 | Add extra logic to play cards more smartly and with risk factors.
 * 09/05/2018 | 1003 | Fix logic bug (plays 47 in [47, 48])
 *            | 1827 | Clean code and documentation overhaul
 * 13/05/2018 | 0214 | Final code documentation
 *            | 1627 | Disable playing 40..46 on first turn (player was losing by being forced to play a 47)
 * -----------|------|-------------
 */


// 13/05/2018
// Intensity Game Statistics
// ======================================
// For 1013 games...
// Pos     Score   Percentage
// 1st     807     79%
// 2nd     99      9%
// 3rd     62      6%
// 4th     45      4%
// ======================================
// In the last 60 games...
// Pos     Score   Percentage
// 1st     48      80%
// 2nd     5       8%
// 3rd     3       5%
// 4th     4       6%
// ======================================

// 09/05/2018
// Intensity Game Statistics
// ======================================
// For 1016 games...
// Pos     Score   Percentage
// 1st     836     82%
// 2nd     75      7%
// 3rd     64      6%
// 4th     41      4%
// ======================================
// In the last 60 games...
// Pos     Score   Percentage
// 1st     60      78%
// 2nd     10      13%
// 3rd     5       6%
// 4th     1       1%
// ======================================
// Player 0x2

// 25/04/2018
// Intensity Game Statistics
// ======================================
// For 134593 games...
// Pos     Score   Percentage
// 1st     108872  81%
// 2nd     10524   7%
// 3rd     9004    6%
// 4th     6193    4%
// ======================================
// In the last 60 games...
// Pos     Score   Percentage
// 1st     45      75%
// 2nd     4       6%
// 3rd     8       13%
// 4th     3       5%
// ======================================
// >> bd2db2e1

#include <stdio.h>
#include <assert.h>

/* PROVIDED DEFINES */

#define ACTION_PLAYER_NAME    0
#define ACTION_DISCARD        1
#define ACTION_PLAY_CARD      2
#define ACTION_UNIT_TESTS     3

#define N_CARDS              40
#define N_CARDS_INITIAL_HAND 10
#define N_PLAYERS             4
#define N_CARDS_DISCARDED     3

#define CARD_MIN             10
#define CARD_MAX             49

/* PROVIDED FUNCTION PROTOTYPES */

void print_player_name(void);

void choose_discards(void);

void choose_card_to_play(void);

void run_unit_tests(void);

/* DEFINES */

#define SAFETY_RISK_FACTOR 1

#define CARDS_PER_ROUND N_PLAYERS

#define CARD_NONE 0
#define CARD_BUFFALO 47

#define CARD_CALF_START 30
#define CARD_CALF_END 39

#define CARD_SUIT_1X 1
#define CARD_SUIT_2X 2
#define CARD_SUIT_3X 3
#define CARD_SUIT_4X 4

#define TURN_FIRST 0
#define TURN_SECOND 1
#define TURN_THIRD 2
#define TURN_LAST 3

#define TRUE 1
#define FALSE 0

/* FUNCTION PROTOTYPES */

int getSuit(int card);

int getUnitValue(int card);

int isBuffalo(int card);

int isCalf(int card);

int arrayHasCard(int card, int *array, int arrayLength);

int arrayHasCalves(int *array, int arrayLength);

int arrayCountCardsOfSuit(int suit, int *array, int arrayLength);

int cardHasBeenPlayed(int card,
                      int *cardsHistory, int cardsHistoryCount,
                      int *cardsPlayed, int cardsPlayedCount);

int arrayHighestCardOfSuitUntil(int suit, int maximum, int *array, int arrayLength);

int arrayHighestCardOfSuit(int suit, int *array, int arrayLength);

int tryHighestNotBuffalo(int *array, int arrayLength);

int tryLowestNotBuffalo(int *array, int arrayLength);

// You should not need to change this main function

int main(void) {
    int which_action = 0;
    scanf("%d", &which_action);
    if (which_action == ACTION_PLAYER_NAME) {
        print_player_name();
    } else if (which_action == ACTION_DISCARD) {
        choose_discards();
    } else if (which_action == ACTION_PLAY_CARD) {
        choose_card_to_play();
    } else {
        run_unit_tests();
    }
    return 0;
}

void print_player_name(void) {
    printf("0xB");
    // printf("0x4F7295"); // Hex for 5206677!
}

// Get the suit of a card
int getSuit(int card) {
    // The suit of a card is given by the first digit of the card
    // We can divide by 10 to get this value
    return card / 10;
}

int getUnitValue(int card) {
    // The unit value of a card is given by the last digit of the card
    // We can get this value by finding the modulus 10 of that card
    return card % 10;
}

// Check if a card is a buffalo
int isBuffalo(int card) {
    return card == CARD_BUFFALO;
}

// Check if a card is a calf
int isCalf(int card) {
    // A card is a calf if it has a value between CALF_CARD_START and CARD_CALF_END (inclusive)
    return CARD_CALF_START <= card && card <= CARD_CALF_END;
}

// Check if a card is in an array
int arrayHasCard(int card, int *array, int arrayLength) {
    // Iterate through all the items in the array, and return TRUE if a certain card is found
    int cardIndex;
    for (cardIndex = 0; cardIndex < arrayLength; cardIndex++) {
        if (array[cardIndex] == card) {
            return TRUE;
        }
    }
    return FALSE;
}

// Check if a calf exists in a given array
int arrayHasCalves(int *array, int arrayLength) {
    // Iterate through all the items in the array, and return TRUE if a calf card is found
    int cardIndex;
    for (cardIndex = 0; cardIndex < arrayLength; cardIndex++) {
        if (isCalf(array[cardIndex])) {
            return TRUE;
        }
    }
    return FALSE;
}

// Count the number of cards in an array that match a certain suit
int arrayCountCardsOfSuit(int suit, int *array, int arrayLength) {
    int count = 0;

    int cardIndex;
    for (cardIndex = 0; cardIndex < arrayLength; cardIndex++) {
        if (getSuit(array[cardIndex]) == suit) {
            count++;
        }
    }

    return count;
}

// Check if a certain card has been played
// that is - that the card exists either in the game history, or the round history
int cardHasBeenPlayed(int card,
                      int *cardsHistory, int cardsHistoryCount,
                      int *cardsPlayed, int cardsPlayedCount) {
    return arrayHasCard(card, cardsHistory, cardsHistoryCount) || arrayHasCard(card, cardsPlayed, cardsPlayedCount);
}

// Find the highest card in an array that is less than a certain card
int arrayHighestCardOfSuitUntil(int suit, int maximum, int *array, int arrayLength) {
    int highest = CARD_NONE;

    int cardIndex;
    for (cardIndex = 0; cardIndex < arrayLength; cardIndex++) {
        // Update the highest card, if the current card is in the same suit and has a value lower than a certain value
        if (getSuit(array[cardIndex]) == suit
            && array[cardIndex] > highest
            && array[cardIndex] <= maximum) {
            highest = array[cardIndex];
        }
    }

    return highest;
}

// Find the highest card of a certain suit in an array
int arrayHighestCardOfSuit(int suit, int *array, int arrayLength) {
    return arrayHighestCardOfSuitUntil(suit, suit * 10 + 9, array, arrayLength);
}

// Return the highest card in an array - if it is a buffalo, try not to play it
int tryHighestNotBuffalo(int *array, int arrayLength) {
    if (isBuffalo(array[arrayLength - 1]) && arrayLength > 1) {
        // If the last card is a buffalo, and there is more than one card, return the second last card
        return array[arrayLength - 2];
    } else {
        // Otherwise, return the last card
        return array[arrayLength - 1];
    }
}

// Return the lowest card in an array - if it is a buffalo, try not to play it
int tryLowestNotBuffalo(int *array, int arrayLength) {
    if (isBuffalo(array[0]) && arrayLength > 1) {
        // If the first card is a buffalo, and there is more than one card, return the second card
        return array[1];
    } else {
        // Otherwise, return the first card
        return array[0];
    }
}

// Read the cards in our hand, and discard three cards
void choose_discards() {
    int cardCounter_One;
    int cardCounter_two;

    // Read in the player's hand into an array
    int myCards[N_CARDS_INITIAL_HAND] = {0};
    for (cardCounter_One = 0; cardCounter_One < N_CARDS_INITIAL_HAND; cardCounter_One++) {
        scanf("%d", &myCards[cardCounter_One]);
    }

    // Pick the three highest cards with the highest unit value
    int cardsToDiscard[N_CARDS_DISCARDED] = {0};
    for (cardCounter_One = 0; cardCounter_One < N_CARDS_DISCARDED; cardCounter_One++) {

        int highestCard = 0;
        for (cardCounter_two = 0; cardCounter_two < N_CARDS_INITIAL_HAND; cardCounter_two++) {
            // Flag for if a card has already been chosen to be discarded
            int cardAlreadyDiscarded = arrayHasCard(myCards[cardCounter_two], cardsToDiscard, N_CARDS_DISCARDED);

            // Flag for if the current card has an equal or higher unit value than the current highest card
            int cardHasSameOrHigherUnit = getUnitValue(myCards[cardCounter_two]) >= getUnitValue(highestCard);

            // If a card has not been discarded, has a higher unit value, and is not a buffalo card, update the highest
            if (!cardAlreadyDiscarded && cardHasSameOrHigherUnit && !isBuffalo(myCards[cardCounter_two])) {
                highestCard = myCards[cardCounter_two];
            }
        }
        // Discard the highest card
        cardsToDiscard[cardCounter_One] = highestCard;
    }

    // If the buffalo card is the only 4X card in our hand, then discard it
    if (arrayHasCard(CARD_BUFFALO, myCards, N_CARDS_INITIAL_HAND)
        && arrayCountCardsOfSuit(CARD_SUIT_4X, myCards, N_CARDS_INITIAL_HAND) == 1) {
        cardsToDiscard[2] = CARD_BUFFALO;
    }

    // Print the three cards to discard
    printf("%d %d %d\n", cardsToDiscard[0], cardsToDiscard[1], cardsToDiscard[2]);
}


void choose_card_to_play(void) {
    // FUNCTION FLOW
    /*
     * 01 | Get the number of cards in the hand - can be used to calculate the current round
     * 02 | Get the number of cards played in the round - can be used to calculate the player's turn number
     * 03 | * Get the player's table position - Not used in the game strategy
     * 04 | Get the cards in the player's hand
     * 05 | Get the cards played in the round
     * 06 | Get the cards played in the previous rounds
     * 07 | * Get the cards that were discarded - Not used in the game strategy
     * 08 | * Get the cards that were received - Not used in the game strategy
     * 09 | Count the number of calves in the player's hands
     * 10 | Execute game strategy
     *
     */

    // GAME STRATEGY
    /*
     * If the player has the first turn in the round:
     * - For the first two rounds, play the highest non-penalty cards up to 29, as everyone else should have suit card
     * \-- Only play a 48 or 49 if the player holds the buffalo card (47)
     * - If a player has calves, and they can start the round with a calf, play the highest safe calf they hold
     * - Otherwise:
     * \-- Play the lowest non-calf card
     * \-- Play the buffalo if the only other cards in the 4X suit are 48 or 49
     *
     *
     * If the player has the second / third / fourth turn in the round:
     * - Find the round suit
     * - Find the highest card of the round suit that has been played
     * - Check if the player has cards that match the round suit
     * - Check if the player has cards that match and are lower than the current highest card of that suit
     * - Check if the current round is a penalty round (calves or buffalo is in play)
     * - If the player has cards that match the round suit:
     * \-- If the player has the last turn:
     *   \-- Play the highest safe card, or highest non-penalty card if not possible
     *   \-- Play the buffalo card if held, and if a higher card (48..49) has been played
     * \-- Otherwise play the lowest suitable card
     * - Otherwise play the buffalo, highest calf, or highest card in the player's hand
     */

    int cardCounter_one;
    int cardCounter_two;

    // Get number of cards in hand
    int myCardsCount;
    scanf("%d", &myCardsCount);

    // Calculate the current round number
    int roundNumber = N_CARDS_INITIAL_HAND - myCardsCount;

    // Get number of cards played this round
    int cardsPlayedCount;
    scanf("%d", &cardsPlayedCount);

    // The number of cards played is equivalent to the turn!
    // If 0 card(s) have been played, we have the 1st turn          (playerTurn = 0)
    // If 1 card(s) have been played, we have the 2nd turn          (playerTurn = 1)
    // If 2 card(s) have been played, we have the 3rd turn          (playerTurn = 2)
    // If 3 card(s) have been played, we have the 4th (last) turn   (playerTurn = 3)
    int playerTurn = cardsPlayedCount;

    // Get player position
    int tablePosition;
    scanf("%d", &tablePosition);

    // Get the cards in hand
    int myCards[N_CARDS_INITIAL_HAND] = {0};
    for (cardCounter_one = 0; cardCounter_one < myCardsCount; cardCounter_one++) {
        scanf("%d", &myCards[cardCounter_one]);
    }

    // Get the cards already played this round
    int cardsPlayed[CARDS_PER_ROUND] = {0};
    for (cardCounter_one = 0; cardCounter_one < cardsPlayedCount; cardCounter_one++) {
        scanf("%d", &cardsPlayed[cardCounter_one]);
    }

    // Get the cards played in all of the previous rounds
    int cardsHistoryCount = roundNumber * CARDS_PER_ROUND;
    int cardsHistory[N_CARDS] = {0};
    for (cardCounter_one = 0; cardCounter_one < cardsHistoryCount; cardCounter_one++) {
        scanf("%d", &cardsHistory[cardCounter_one]);
    }

    // Get the three cards that were initially discarded
    int cardsDiscarded[N_CARDS_DISCARDED] = {0};
    for (cardCounter_one = 0; cardCounter_one < N_CARDS_DISCARDED; cardCounter_one++) {
        scanf("%d", &cardsDiscarded[cardCounter_one]);
    }

    // Get the three cards that were initially received
    int cardsReceived[N_CARDS_DISCARDED] = {0};
    for (cardCounter_one = 0; cardCounter_one < N_CARDS_DISCARDED; cardCounter_one++) {
        scanf("%d", &cardsReceived[cardCounter_one]);
    }

    // Create the variable that will store the card to return
    int cardToPlay = CARD_NONE;

    // Find and count the calves in our hand

    // Note: Not using `arrayCountCardsOfSuit` as the calves which have been found need to be extracted
    int calvesInHand[N_CARDS_INITIAL_HAND] = {0};
    int calvesInHandCount = 0;
    for (cardCounter_one = 0; cardCounter_one < myCardsCount; cardCounter_one++) {
        if (isCalf(myCards[cardCounter_one])) {
            calvesInHand[calvesInHandCount] = myCards[cardCounter_one];
            calvesInHandCount++;
        }
    }






    // Check if the player has the first turn in the round
    if (playerTurn == TURN_FIRST) {

        // For the first two rounds (round 0 and round 1), it is expected that every player will have at least one card
        // that matches the suit which they must play, therefore play the highest cards in the player's hands.
        if (roundNumber <= 1) {
            // Try to choose the highest card in the player's hand from 10..29
            for (cardCounter_one = CARD_SUIT_1X * 10; cardCounter_one < CARD_SUIT_3X * 10; cardCounter_one++) {
                if (arrayHasCard(cardCounter_one, myCards, myCardsCount)) {
                    cardToPlay = cardCounter_one;
                }
            }

            if (arrayHasCard(CARD_BUFFALO, myCards, myCardsCount)) {
                if (arrayHasCard(48, myCards, myCardsCount)) {
                    cardToPlay = 48;
                }
                if (arrayHasCard(49, myCards, myCardsCount)) {
                    cardToPlay = 49;
                }
            }
        }


        // Check if it is permissible to play a calf card as the first card in the round
        // If this is allowed, and the player has a calf card, attempt to play it
        if (cardToPlay == CARD_NONE) {
            if (calvesInHandCount > 0
                && arrayCountCardsOfSuit(CARD_SUIT_3X, cardsHistory, cardsHistoryCount) < 9
                && arrayHasCalves(cardsHistory, cardsHistoryCount)) {

                // If the amount of remaining turns this round is more than the amount of uncertain cards,
                // then we can partially assume that one player will have a higher card than ours.
                // ALTHOUGH, we need to keep in mind that one player might have all of the higher cards.
                // To compensate for this, a risk factor will be implemented

                // Iterate through all the cards, and count the number of uncertain cards before and after that card
                for (cardCounter_one = 0; cardCounter_one < calvesInHandCount; cardCounter_one++) {
                    // Count the number of uncertain cards from 30..calf-1
                    int uncertainCardsBefore = 0;
                    for (cardCounter_two = CARD_CALF_START;
                         cardCounter_two < calvesInHand[cardCounter_one]; cardCounter_two++) {
                        if (!(arrayHasCard(cardCounter_two, myCards, myCardsCount)
                              || arrayHasCard(cardCounter_two, cardsHistory, cardsHistoryCount))) {
                            uncertainCardsBefore++;
                        }
                    }

                    // Count the number of uncertain cards from calf+1..39
                    int uncertainCardsAfter = 0;
                    for (cardCounter_two = calvesInHand[cardCounter_one] + 1;
                         cardCounter_two <= calvesInHand[cardCounter_one]; cardCounter_two++) {
                        if (!(arrayHasCard(cardCounter_two, myCards, myCardsCount)
                              || arrayHasCard(cardCounter_two, cardsHistory, cardsHistoryCount))) {
                            uncertainCardsAfter++;
                        }
                    }

                    if (uncertainCardsBefore < CARDS_PER_ROUND - 1 - SAFETY_RISK_FACTOR && uncertainCardsAfter > 0) {
                        cardToPlay = calvesInHand[cardCounter_one];
                    }
                }
            } else {
                // A calf hasn't been played before, or the player does not have any calf cards
                // The player cannot start with a calf card unless it is their only option

                // Play the first non-calf card in the player's hand
                for (cardCounter_one = 0;
                     cardToPlay == CARD_NONE && cardCounter_one < myCardsCount; cardCounter_one++) {
                    if (!isCalf(myCards[cardCounter_one])) {
                        cardToPlay = myCards[cardCounter_one];
                    }
                }

                // If the player holds the buffalo card, try to choose 48..49
                // Or, if the player holds the buffalo card, all cards below the buffalo in the 4X have been played, play 47
                if (arrayHasCard(CARD_BUFFALO, myCards, myCardsCount)) {
                    // Count the number of cards from 40..46 that are in other player's hands
                    int uncertainCards = 0;
                    for (cardCounter_one = 40; cardCounter_one < CARD_BUFFALO; cardCounter_one++) {
                        if (!arrayHasCard(cardCounter_one, myCards, myCardsCount)
                            && !arrayHasCard(cardCounter_one, cardsHistory, cardsHistoryCount)) {
                            uncertainCards++;
                        }
                    }

                    // If all the cards from 40..46 have been played, and the player does not have 48..49, play the 47.
                    if (uncertainCards == 0) {
                        if ((!cardHasBeenPlayed(48, cardsHistory, cardsHistoryCount, cardsPlayed, cardsPlayedCount)
                             && !arrayHasCard(48, myCards, myCardsCount))
                            ||
                            (!cardHasBeenPlayed(49, cardsHistory, cardsHistoryCount, cardsPlayed, cardsPlayedCount)
                             && !arrayHasCard(49, myCards, myCardsCount))) {
                            cardToPlay = CARD_BUFFALO;
                        }
                    }
                }
            }
        }
    } else {
        // The player has the second / third / fourth turn in the round

        // Find the round suit
        int roundSuit = getSuit(cardsPlayed[0]);

        // Find the highest card played that belongs to the round suit
        int highestCard = arrayHighestCardOfSuit(roundSuit, cardsPlayed, cardsPlayedCount);

        // Find and count the number of cards in the player's hand that belong to the round suit
        int suitableCardsCount = 0;
        int suitableCards[N_CARDS_INITIAL_HAND] = {0};
        for (cardCounter_one = 0; cardCounter_one < myCardsCount; cardCounter_one++) {
            if (getSuit(myCards[cardCounter_one]) == roundSuit) {
                suitableCards[suitableCardsCount] = myCards[cardCounter_one];
                suitableCardsCount++;
            }
        }

        // Find and count the number of cards in the player's hand that belong
        // to the round suit and are lower than the current highest card
        int betterCardsCount = 0;
        int betterCards[N_CARDS_INITIAL_HAND] = {0};
        for (cardCounter_one = 0; cardCounter_one < suitableCardsCount; cardCounter_one++) {
            if (suitableCards[cardCounter_one] < highestCard) {
                betterCards[betterCardsCount] = suitableCards[cardCounter_one];
                betterCardsCount++;
            }
        }

        // Flag if the current round contains the buffalo or cards, and is therefore a penalty round
        int isPenaltyRound = arrayHasCalves(cardsPlayed, cardsPlayedCount)
                             || arrayHasCard(CARD_BUFFALO, cardsPlayed, cardsPlayedCount);



        // Check if the player has cards that match the round suit, and is therefore forced to play one of them
        if (suitableCardsCount > 0) {

            if (playerTurn == TURN_LAST && !isPenaltyRound && suitableCards[suitableCardsCount - 1] != CARD_BUFFALO) {
                // If the player has the last turn in a non-penalty round, play their highest suitable non-buffalo card
                cardToPlay = tryHighestNotBuffalo(suitableCards, suitableCardsCount);
            } else if (betterCardsCount > 0) {
                // If the player has cards in the round suit that is lower than the current highest, play their highest
                cardToPlay = betterCards[betterCardsCount - 1];

                if (roundSuit == CARD_SUIT_4X
                    && arrayHasCard(CARD_BUFFALO, myCards, myCardsCount)
                    && highestCard > 47) {
                    cardToPlay = CARD_BUFFALO;
                }
            } else {
                // Fallback scenario to play the lowest suitable card
                cardToPlay = tryLowestNotBuffalo(suitableCards, suitableCardsCount);

                // Iterate through all the suitable cards, and count the number of uncertain cards leading to that card
                for (cardCounter_one = 0; cardCounter_one < suitableCardsCount; cardCounter_one++) {
                    int uncertainCards = 0;
                    cardCounter_two = roundSuit * 10;

                    // Count the number of uncertain cards
                    while (cardCounter_two < suitableCards[cardCounter_one]) {
                        if (!(arrayHasCard(cardCounter_two, myCards, myCardsCount)
                              || cardHasBeenPlayed(cardCounter_two,
                                                   cardsHistory, cardsHistoryCount,
                                                   cardsPlayed, cardsPlayedCount))) {
                            uncertainCards++;
                        }
                        cardCounter_two++;
                    }

                    if (uncertainCards < CARDS_PER_ROUND - cardsPlayedCount - 1 - SAFETY_RISK_FACTOR) {
                        cardToPlay = suitableCards[cardCounter_one];
                    }
                }
            }

        } else {
            // The player has no cards in their hand matching the round suit
            // Therefore the player can play any card in their hand

            if (arrayHasCard(CARD_BUFFALO, myCards, myCardsCount)) {
                // Play the buffalo card if the player holds it
                cardToPlay = CARD_BUFFALO;
            } else if (calvesInHandCount > 0) {
                // Play the highest calf card if the player holds at least one.
                cardToPlay = calvesInHand[calvesInHandCount - 1];
            } else {
                // Otherwise, play the highest card in the player's hand
                cardToPlay = myCards[myCardsCount - 1];
            }
        }
    }

    // Fall back scenario, pick the lowest card.
    if (cardToPlay == CARD_NONE) {
        cardToPlay = myCards[0];
    }

    printf("%d\n", cardToPlay);
}

// UNIT TESTING
/*
 * Checking for the expected correct operation of functions that are used in the card picking logic
 * 01 | getSuit: Return the suit of a card
 * 02 | getUnitValue: Return the unit value of a card
 * 03 | isBuffalo: Return TRUE only for the buffalo card
 * 04 | isCalf: Return TRUE only if the card is a calf card
 * 05 | arrayHasCard: Return TRUE only if an array contains a certain card
 * 06 | arrayHasCalves: Return TRUE if an array contains at least one calf card
 * 07 | arrayCountCardsOfSuit: Returns the number of cards of a certain suit in a given array
 * 08 | cardHasBeenPlayed: Return TRUE if a card exists in the game history, or the round history
 * 09 | arrayHighestCardOfSuitUntil: Return the highest card of a given suit in an array until a certain limit
 * 10 | arrayHighestCardOfSuit: Return the highest card of a given suit in an array
 * 11 | tryHighestNotBuffalo: Return the highest card in an array, or the second highest if the highest is a buffalo
 * 12 | tryLowestNotBuffalo: Return the lowest card in an array, or the second lowest if the lowest is a buffalo
 */
void run_unit_tests(void) {
    // 01 | Check that getSuit functions as expected
    assert(getSuit(10) == CARD_SUIT_1X);
    assert(getSuit(19) == CARD_SUIT_1X);
    assert(getSuit(20) == CARD_SUIT_2X);
    assert(getSuit(29) == CARD_SUIT_2X);
    assert(getSuit(30) == CARD_SUIT_3X);
    assert(getSuit(39) == CARD_SUIT_3X);
    assert(getSuit(40) == CARD_SUIT_4X);
    assert(getSuit(49) == CARD_SUIT_4X);

    assert(getSuit(47) == getSuit(48));


    // 02 | Check that getUnitValue functions as expected
    assert(getUnitValue(10) == 0);
    assert(getUnitValue(11) == 1);
    assert(getUnitValue(12) == 2);
    assert(getUnitValue(13) == 3);
    assert(getUnitValue(14) == 4);
    assert(getUnitValue(25) == 5);
    assert(getUnitValue(36) == 6);
    assert(getUnitValue(47) == 7);

    assert(getUnitValue(10) == getUnitValue(20));
    assert(getUnitValue(10) != getUnitValue(19));


    // 03 | Check that isBuffalo functions as expected
    assert(isBuffalo(46) == FALSE);
    assert(isBuffalo(48) == FALSE);

    assert(isBuffalo(CARD_BUFFALO) == TRUE);
    assert(isBuffalo(47) == TRUE);


    // 04 | Check that isCalf functions as expected
    assert(isCalf(29) == FALSE);
    assert(isCalf(40) == FALSE);

    assert(isCalf(30) == TRUE);
    assert(isCalf(31) == TRUE);
    assert(isCalf(32) == TRUE);
    assert(isCalf(33) == TRUE);
    assert(isCalf(34) == TRUE);
    assert(isCalf(35) == TRUE);
    assert(isCalf(36) == TRUE);
    assert(isCalf(37) == TRUE);
    assert(isCalf(38) == TRUE);
    assert(isCalf(39) == TRUE);


    const int arrayLength = 5;


    // 05 | Check that arrayHasCard functions as expected
    int arrayWithBuffalo[arrayLength] = {20, 21, 22, 23, CARD_BUFFALO};
    assert(arrayHasCard(49, arrayWithBuffalo, arrayLength) == FALSE);
    assert(arrayHasCard(CARD_BUFFALO, arrayWithBuffalo, arrayLength) == TRUE);


    // 06 | Check that arrayHasCalves functions as expected
    int arrayWithoutCalves[arrayLength] = {20, 21, 22, 23, 24};
    assert(arrayHasCalves(arrayWithoutCalves, arrayLength) == FALSE);

    int arrayWithCalf[arrayLength] = {20, 21, 22, 23, 30};
    int arrayWithCalves[arrayLength] = {20, 21, 22, 30, 31};
    assert(arrayHasCalves(arrayWithCalf, arrayLength) == TRUE);
    assert(arrayHasCalves(arrayWithCalves, arrayLength) == TRUE);


    // 07 | Check that arrayCountCardsOfSuit functions as expected
    int arrayWithAllCalves[arrayLength] = {30, 31, 32, 33, 34};
    assert(arrayCountCardsOfSuit(CARD_SUIT_3X, arrayWithAllCalves, arrayLength) == 5);
    assert(arrayCountCardsOfSuit(CARD_SUIT_1X, arrayWithAllCalves, arrayLength) == 0);
    assert(arrayCountCardsOfSuit(CARD_SUIT_2X, arrayWithAllCalves, arrayLength) == 0);
    assert(arrayCountCardsOfSuit(CARD_SUIT_4X, arrayWithAllCalves, arrayLength) == 0);

    assert(arrayCountCardsOfSuit(CARD_SUIT_1X, arrayWithBuffalo, arrayLength) == 0);
    assert(arrayCountCardsOfSuit(CARD_SUIT_2X, arrayWithBuffalo, arrayLength) == 4);
    assert(arrayCountCardsOfSuit(CARD_SUIT_3X, arrayWithBuffalo, arrayLength) == 0);
    assert(arrayCountCardsOfSuit(CARD_SUIT_4X, arrayWithBuffalo, arrayLength) == 1);


    // 08 | Check that cardHasBeenPlayed functions as expected
    int cardHistory[arrayLength] = {10, 11, 12, 13, 14};
    int cardsPlayed[arrayLength] = {15, 16, 17, 18, 19};
    assert(cardHasBeenPlayed(14, cardHistory, arrayLength, cardsPlayed, arrayLength) == TRUE);
    assert(cardHasBeenPlayed(20, cardHistory, arrayLength, cardsPlayed, arrayLength) == FALSE);


    // 09 | Check that arrayHighestCardOfSuitUntil functions as expected
    int arrayHighestCard_test[arrayLength] = {21, 28, 39, 23, 26};
    assert(arrayHighestCardOfSuitUntil(CARD_SUIT_2X, 29, arrayHighestCard_test, arrayLength) == 28);
    assert(arrayHighestCardOfSuitUntil(CARD_SUIT_2X, 28, arrayHighestCard_test, arrayLength) == 28);
    assert(arrayHighestCardOfSuitUntil(CARD_SUIT_2X, 27, arrayHighestCard_test, arrayLength) == 26);
    assert(arrayHighestCardOfSuitUntil(CARD_SUIT_3X, 39, arrayHighestCard_test, arrayLength) == 39);
    assert(arrayHighestCardOfSuitUntil(CARD_SUIT_3X, 38, arrayHighestCard_test, arrayLength) == CARD_NONE);


    // 10 | Check that arrayHighestCardOfSuit functions as expected
    assert(arrayHighestCardOfSuit(CARD_SUIT_2X, arrayHighestCard_test, arrayLength) == 28);
    assert(arrayHighestCardOfSuit(CARD_SUIT_3X, arrayHighestCard_test, arrayLength) == 39);


    // 11 | Check that tryHighestNotBuffalo functions as expected
    int arrayWithOnlyBuffalo[1] = {CARD_BUFFALO};
    assert(tryHighestNotBuffalo(arrayWithOnlyBuffalo, 1) == CARD_BUFFALO);

    int arrayWithBuffaloHighest[2] = {20, CARD_BUFFALO};
    assert(tryHighestNotBuffalo(arrayWithOnlyBuffalo, 1) == CARD_BUFFALO);
    assert(tryHighestNotBuffalo(arrayWithBuffaloHighest, 2) == 20);


    // 12 | Check that tryLowestNotBuffalo functions as expected
    int arrayWithBuffaloLowest[2] = {CARD_BUFFALO, 48};
    assert(tryLowestNotBuffalo(arrayWithOnlyBuffalo, 1) == CARD_BUFFALO);
    assert(tryLowestNotBuffalo(arrayWithBuffaloLowest, 2) == 48);
}