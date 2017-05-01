/*
 * unittest3.c
 * Bryan Resner
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "whoseTurn"

int assertTrue(int lhs, int rhs) {
    if (lhs != rhs) {
        printf("----- ASSERT TRUE FAILED -----\n");
        printf("Value LHS: %d\n", lhs);
        printf("Value RHS: %d\n", rhs);
        return 1;
    }
    else {
        return 0;
    }
}

int assertTrueMult(int lhs, int rhs1, int rhs2, int rhs3) {
    if (lhs != rhs1 && lhs != rhs2 && lhs != rhs3) {
        printf("----- ASSERT TRUE FAILED -----\n");
        printf("Value LHS: %d, ", lhs);
        printf("Value RHS1: %d, ", rhs1);
        printf("Value RHS2: %d, ", rhs2);
        printf("Value RHS3: %d \n", rhs3);
        return 1;
    }
    else {
        return 0;
    }
}

int assertFalse(int lhs, int rhs) {
    if (lhs == rhs) {
        printf("----- ASSERT FALSE FAILED -----\n");
        printf("Value LHS: %d\n", lhs);
        printf("Value RHS: %d\n", rhs);
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    
    int i;
    int seed = 1000;
    int numPlayers = 2;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    // Counter to track number of assert errors encountered without stopping
    // the execution of the test
    int numErrors = 0;
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    printf("----------------- Unit Test: %s ----------------\n", TESTUNIT);
    
    // ----------- TEST 1: CHECKING THAT whoseTurn RETURNS CORRECT PLAYER FOR 2 PLAYER GAME --------------
    printf("TEST 1: CHECKING THAT whoseTurn RETURNS CORRECT PLAYER FOR 2 PLAYER GAME\n");
    
    //Full deck count takes three parameters: player, card to check for, and the gameState.
    //For first test we will check for the initialize state for each player.

    int currentPlayer;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < 12; i++) {
        if (i % 2 == 0) {
            currentPlayer = 0;
        }
        else {
            currentPlayer = 1;
        }
        printf("Iteration %d: Whose Turn = %d, Expected = %d\n", i, currentPlayer, whoseTurn(&testG));
        numErrors += assertTrue(currentPlayer, whoseTurn(&testG));
        //Ending turn for this player
        printf("Ending Player %d's Turn\n", i);
        endTurn(&testG);
    }
    
    // ----------- TEST 2: CHECKING THAT whoseTurn RETURNS CORRECT PLAYER FOR 3 PLAYER GAME --------------
    printf("TEST 2: CHECKING THAT whoseTurn RETURNS CORRECT PLAYER FOR 3 PLAYER GAME\n");
    
    //Full deck count takes three parameters: player, card to check for, and the gameState.
    //For first test we will check for the initialize state for each player.
    
    numPlayers = 3;
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < 12; i++) {
        if (i % 3 == 0) {
            currentPlayer = 0;
        }
        else if (i % 3 == 1){
            currentPlayer = 1;
        }
        else {
            currentPlayer = 2;
        }
        printf("Iteration %d: Whose Turn = %d, Expected = %d\n", i, currentPlayer, whoseTurn(&testG));
        numErrors += assertTrue(currentPlayer, whoseTurn(&testG));
        //Ending turn for this player
        printf("Ending Player %d's Turn\n", i);
        endTurn(&testG);
    }
    
    // ----------- TEST 3: CHECKING THAT whoseTurn RETURNS CORRECT PLAYER FOR 4 PLAYER GAME --------------
    printf("TEST 3: CHECKING THAT whoseTurn RETURNS CORRECT PLAYER FOR 4 PLAYER GAME\n");
    
    //Full deck count takes three parameters: player, card to check for, and the gameState.
    //For first test we will check for the initialize state for each player.
    
    numPlayers = 4;
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < 12; i++) {
        if (i % 4 == 0) {
            currentPlayer = 0;
        }
        else if (i % 4 == 1){
            currentPlayer = 1;
        }
        else if (i % 4 == 2){
            currentPlayer = 2;
        }
        else {
            currentPlayer = 3;
        }
        printf("Iteration %d: Whose Turn = %d, Expected = %d\n", i, currentPlayer, whoseTurn(&testG));
        numErrors += assertTrue(currentPlayer, whoseTurn(&testG));
        //Ending turn for this player
        printf("Ending Player %d's Turn\n", i);
        endTurn(&testG);
    }
    
    if (numErrors == 0) {
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);
    } else {
        printf("\n ----- Assertion Failure %s -----\n", TESTUNIT);
    }
    
    
    return 0;
}
