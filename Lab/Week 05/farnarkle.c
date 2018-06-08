// COMP1511 Farnarkling lab exercises
//
// This program by Andrew Wong (z5206677) on 26/03/2018

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define N_TILES 4
#define MAX_TILE 8
#define MAX_TURNS 100

// ADD YOUR #defines (if any) here


// You have to write these functions
int count_farnarkles(int tiles1[N_TILES], int tiles2[N_TILES]);

int count_arkles(int tiles1[N_TILES], int tiles2[N_TILES]);

void play_farnarkle(int hidden_tiles[]);

void farnarkle_ai(int turn, int previous_guesses[MAX_TURNS][N_TILES], int
farnarkles[MAX_TURNS], int arkles[MAX_TURNS], int guess[N_TILES]);


// Don't change these functions
int test_farnarkle_ai(int hidden_tiles[]);

void print_two_tile_sequences(int tiles1[N_TILES], int tiles2[N_TILES]);

void read_two_tile_sequences(int tiles1[N_TILES], int tiles2[N_TILES]);

int read_tiles(int tiles[N_TILES]);

void print_tiles(int tiles[N_TILES]);

void set_tiles_to_pseudo_random_values(int tiles[N_TILES]);

// ADD PROTOTYPES FOR ANY FUNCTIONS YOU CREATE HERE

// DO NOT CHANGE THIS FUNCTION
// This main function won't be marked as part of the lab
// It tests the functions you have to write.
// Do not change this main function.  If it does not work with
// your functions you have misunderstood the lab.

int main(void) {
    int call_which_function = 0;

    printf("Enter 0 to call count_farnarkles()\n");
    printf("Enter 1 to call count_arkles()\n");
    printf("Enter 2 to call play_farnarkle()\n");
    printf("Enter 3 to call test_ai_farnarkle_player()\n");
    printf("Call which function: ");
    scanf("%d", &call_which_function);

    if (call_which_function == 0) {
        int tiles1[N_TILES], tiles2[N_TILES];
        read_two_tile_sequences(tiles1, tiles2);
        int farnarkles = count_farnarkles(tiles1, tiles2);
        printf("count_farnarkles returned %d for\n", farnarkles);
        print_two_tile_sequences(tiles1, tiles2);
    } else if (call_which_function == 1) {
        int tiles1[N_TILES], tiles2[N_TILES];
        read_two_tile_sequences(tiles1, tiles2);
        int arkles = count_arkles(tiles1, tiles2);
        printf("count_arkles returned %d for\n", arkles);
        print_two_tile_sequences(tiles1, tiles2);
    } else if (call_which_function == 2) {
        int hidden_tiles[N_TILES];
        set_tiles_to_pseudo_random_values(hidden_tiles);
        play_farnarkle(hidden_tiles);
    } else if (call_which_function == 3) {
        int hidden_tiles[N_TILES];
        printf("Enter hidden tiles: ");
        assert(read_tiles(hidden_tiles) == N_TILES);
        test_farnarkle_ai(hidden_tiles);
    }

    return 0;
}

// return number of farnarkles
int count_farnarkles(int tiles1[N_TILES], int tiles2[N_TILES]) {

    // PUT YOUR CODE HERE
    // NOTE DO NOT CHANGE tiles1 or tiles2

    /* A tile is counted as an Farnarkle if it has the same number
       as the tile in the same position in the hidden sequence. */

    // We will define `tiles1` as the user's tiles
    // and define `tiles2` as the reference tiles

    int found = 0;
    int counter = 0;
    while (counter < N_TILES) {
        if (tiles1[counter] == tiles2[counter]) {
            found++;
        }
        counter++;
    }
    return found;
}

// return number of arkles
int count_arkles(int tiles1[N_TILES], int tiles2[N_TILES]) {

    // PUT YOUR CODE HERE
    // NOTE DO NOT CHANGE tiles1 or tiles2

    // Recursive searching


    int _tiles2[N_TILES];
    int i = 0;
    while (i < N_TILES) {
        _tiles2[i] = tiles2[i];
        i++;
    }

    int found = 0;
    int counter = 0;
    int counter2;
    while (counter < N_TILES) {
        counter2 = 0;
        while (counter2 < N_TILES) {
            if (tiles1[counter] == _tiles2[counter2] && tiles1[counter2] != _tiles2[counter2] &&
                tiles1[counter] != _tiles2[counter]) {

                _tiles2[counter2] = -_tiles2[counter2];
                counter2 = N_TILES;
                found++;
            }

            counter2++;
        }
        counter++;
    }
    return found;
}

// play_farnarkle is given a sequence hidden tiles
// It reads guesses from a human player,
// printing the number of farnarkles and arkles for each guess,
// until the human player guesses the sequence.

void play_farnarkle(int hidden_tiles[N_TILES]) {
    // PUT YOUR CODE HERE
    int turn = 1;
    int win = 0;

    int guess[N_TILES];

    while (!win) {
        printf("Enter guess for turn %d: ", turn);
        read_tiles(guess);
        int farnarkles = count_farnarkles(guess, hidden_tiles);
        int arkles = count_arkles(guess, hidden_tiles);
        printf("%d farnarkles, %d arkles\n", farnarkles, arkles);
        if (farnarkles == N_TILES) {
            win = 1;
        }
        turn++;
    }
    printf("You win\n");
}

// farnarkle_ai is given
//
// turn: the turn number
// previous_guesses: an array of turn - 1 previous guesses
// farnarkles: an array of turn - 1 farnarkle counts for previous guesses
// arkles: an array of turn - 1 arkle counts for previous guesses
//
// it should choose a suitable guess and store it in the array guess

void farnarkle_ai(int turn,
                  int previous_guesses[MAX_TURNS][N_TILES],
                  int farnarkles[MAX_TURNS], int arkles[MAX_TURNS],
                  int guess[N_TILES]) {


    int thisTurnIndex = turn - 1;
    int lastTurnIndex = turn - 2;
    int lastlastTurnIndex = turn - 3;

    if (turn == 1) {
        // Set up the first guess as 1 1 1 1 1 1 1 1
        int i = 0;
        while (i < N_TILES) {
            guess[i] = i % (MAX_TILE + 1) + 1;
            i++;
        }
    } else {
        // Clone the last turn
        int i = 0;
        while (i < N_TILES) {
            guess[i] = previous_guesses[lastTurn][i];
            i++;
        }


        int lastFarnarkles = farnarkles[lastTurnIndex];
        int lastArkles = arkles[lastTurnIndex];


        int relativeFarnarkles = lastFarnarkles;
        int relativeArkles = lastArkles;

        if (turn == 2) {


        } else {
            int found[N_TILES] = {0};
            relativeFarnarkles -= farnarkles[lastlastTurn];
            relativeArkles -= arkles[lastlastTurn];


            if (relativeFarnarkles < 0) {
                printf("\n\nWE SCREWED UP\n\n");
            }

                // Rearranger
            else if (relativeArkles >= 0 && lastArkles > 0) {
                int switchMap[N_TILES];

                if (N_TILES - lastArkles - lastFarnarkles >= 2) {
                    int i = 1;
                    int offset = 1;
                    while (i < N_TILES) {
                        if (!found[i]) {
                            while (found[(i + offset) % MAX_TILE]) offset++;
                            switchMap[i] = (i + offset) % MAX_TILE;
                        }

                        i++;
                    }

                } else {
                    // Only one number left
                    int i = 0;
                    while (i < N_TILES) {
                        if (!found[i]) {
                            guess[i]++;
                        }
                        i++;
                    }
                }

            }

                // Successful rearrange
            else if (relativeFarnarkles > 0) {
                // Got a match, now find the change

                if (relativeFarnarkles == 1) {
                    int i = 0;
                    while (i < N_TILES) {
                        if (previous_guesses[lastTurnIndex][i] ==
                            previous_guesses[lastlastTurnIndex][i]) { found[i] = 1; }
                        i++;
                    }
                }
            else {
                // Nope, increment
                int i = 0;
                while (i < N_TILES) {
                    guess[i] = guess[i] % (MAX_TILE + 1) + 1;
                    i++;
                }
            }
//
        }

//        if (lastFarnarkles > 0) {
//            // Our Farnkarkle count increased, good job!
//        }
//        else if (lastFarnarkles < 0)
//
//

    }















//    int lastTurn = turn - 2;
//
//    if (turn == 1) {

//    } else {
//
//
//        // PREVIOUS TURN ANALYSIS
//        int relativeFarnarkles;
//        relativeFarnarkles = farnarkles[lastTurn] - (lastTurn - 1 >= 0 ? farnarkles[lastTurn - 1] : 0);
//
//        int relativeArkles;
//        relativeArkles = arkles[lastTurn] - (lastTurn - 1 >= 0 ? arkles[lastTurn - 1] : 0);
//
//        if (relativeFarnarkles > 0) {
//            // Our last move resulted in a success
//        }
//
//        if (relativeFarnarkles < 0) {
//            // ABORT
//        }
//
//
//        if (relativeArkles > 0) {
//            // Our last move resulted somewhat in a success
//        }
//
//        if (relativeArkles < 0 && relativeFarnarkles == -relativeArkles) {
//            // We just lost a number
//        }
//
//        // NEW TURN HERE //
//
//        if (relativeFarnarkles + relativeArkles == N_TILES) {
//            assert(0); // found them all, now shuffle...
//
//        } else if (guess[0] < MAX_TILE) {
//            if (relativeFarnarkles < 0) {
//                int i = 0;
//                while (i < N_TILES) {
//                    guess[i] = previous_guesses[lastTurn-1][i];
//                    i++;            }}
//            else if (relativeArkles > 0 || (relativeArkles == 0 && relativeFarnarkles > 0)) {
//                printf("\nRelative!!!\n");
//                int lastSlot = (lastTurn) % (N_TILES-1) + 1;
//                int slot = (turn-1) % (N_TILES-1) + 1;
//                printf("  guess[%d] = guess[0] = %d;\n", slot, guess[0]);
//                guess[slot] = guess[0];
//                // We had a match, keep the same number in case there are duplicates
//            } else {
//                guess[0]++;
//            }
//        }
////        if (turn <= MAX_TILE) {
////            int i = 0;
////            while (i < N_TILES) {
////                guess[i] = turn;
////                i++;
////            }
////        }
//    }
//
////    if (turn > 1) {
//
////
////
////        if (_farnarkles == 0 && _arkles == 0) {
////            // none of the previous values were any part of the answer, ignore all used values
////
////        }
////    }
//
//
//    // PUT YOUR CODE HERE

}

// DO NOT CHANGE THE FUNCTIONS BELOW HERE

// DO NOT CHANGE THIS FUNCTION
void print_two_tile_sequences(int tiles1[N_TILES], int tiles2[N_TILES]) {
    printf("Sequence 1: ");
    print_tiles(tiles1);
    printf("\n");
    printf("Sequence 2: ");
    print_tiles(tiles2);
    printf("\n");
}

// DO NOT CHANGE THIS FUNCTION
void read_two_tile_sequences(int tiles1[N_TILES], int tiles2[N_TILES]) {
    printf("Enter tile sequence 1: ");
    assert(read_tiles(tiles1) == N_TILES);
    printf("Enter tile sequence 2: ");
    assert(read_tiles(tiles2) == N_TILES);
}

// DO NOT CHANGE THIS FUNCTION
// read N_TILES tiles into array tiles
// returns number of tiles successfully read
int read_tiles(int tiles[N_TILES]) {
    int i = 0;
    while (i < N_TILES) {
        if (scanf("%d", &tiles[i]) != 1) {
            return i;
        }
        if (tiles[i] < 1 || tiles[i] > MAX_TILE) {
            return i;
        }
        i = i + 1;
    }
    return i;
}

// DO NOT CHANGE THIS FUNCTION
// print tiles on a single line
void print_tiles(int tiles[N_TILES]) {
    int i = 0;
    while (i < N_TILES) {
        printf("%d", tiles[i]);
        if (i < N_TILES - 1) {
            printf(" ");
        }
        i = i + 1;
    }
}

// DO NOT CHANGE THIS FUNCTION
void set_tiles_to_pseudo_random_values(int tiles[N_TILES]) {
    // seed (initialize) pseudo-random number generate with current time in seconds
    srand(time(NULL));

    int i = 0;
    while (i < N_TILES) {
        // rand() returns a pseudo-random integer in ranger 0 to RAND_MAX inclusive
        // convert to an integer in the range 1..MAX_TILE_template
        tiles[i] = rand() % MAX_TILE + 1;
        i = i + 1;
    }
}

// DO NOT CHANGE THIS FUNCTION

// test_farnarkle_ai is given a sequence of hidden tiles
// It calls the function farnarkle_ai to make a guess
// printing the number of farnarkles and arkles for each guess,
// until farnarkle_ai guesses the sequence.
// number of turns taken is returned

int test_farnarkle_ai(int hidden_tiles[N_TILES]) {
    int guesses[MAX_TURNS][N_TILES] = {{0}};
    int farnarkles[MAX_TURNS] = {0};
    int arkles[MAX_TURNS] = {0};
    int turn_limit = MAX_TILE * N_TILES;

    int turn = 0;
    while (turn <= turn_limit) {

        int i = 0;
        while (i < N_TILES) {
            guesses[turn][i] = -1;
            i = i + 1;
        }

        printf("Turn %d: farnarkle AI guess is: ", turn + 1);
        fflush(stdout); // help debugging

        farnarkle_ai(turn + 1, guesses, farnarkles, arkles, guesses[turn]);

        print_tiles(guesses[turn]);
        printf(" = ");

        int j = 0;
        while (j < N_TILES) {
            if (guesses[turn][j] < 1 || guesses[turn][j] > MAX_TILE) {
                printf("Invalid guess\nGame ended\n");
                return 0;
            }
            j = j + 1;
        }

        farnarkles[turn] = count_farnarkles(hidden_tiles, guesses[turn]);
        arkles[turn] = count_arkles(hidden_tiles, guesses[turn]);

        printf("%d farnarkles, %d arkles\n", farnarkles[turn], arkles[turn]);

        if (farnarkles[turn] == N_TILES) {
            printf("Farnarkle AI took %d turns to guess the tiles.\n", turn + 1);
            return turn + 1;
        }
        turn = turn + 1;
    }
    printf("Turn limit of %d turns exceeded\nGame ended\n", turn_limit);
    return turn + 1;

}
