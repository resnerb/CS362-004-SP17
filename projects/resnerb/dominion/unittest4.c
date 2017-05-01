/*
 * unittest4.c
 * Bryan Resner
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "handCard"

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
    
    int i, j;
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
    
    // ----------- TEST 1: CHECKING THAT handCard RETURNS APPROPRIATE CARDS IN THE HAND --------------
    printf("TEST 1: CHECKING THAT handCard RETURNS APPROPRIATE CARDS IN THE HAND\n");
    
    //For first test we will check for the initialize state for each player.
    
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < testG.numPlayers; i++) {
        printf("Whose Turn = %d, Expected = %d\n", i, testG.whoseTurn);
        numErrors += assertTrue(i, testG.whoseTurn);
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Cards In Player %d's Hand: \n", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("Card %d: From Hand %d, From handCard() %d\n", j, testG.hand[i][j], handCard(j, &testG));
            numErrors += assertTrue(testG.hand[i][j], handCard(j, &testG));
        }
        printf(";\n");
        
        //Ending turn for this player
        printf("Ending Player %d's Turn\n", i);
        endTurn(&testG);
        
        printf("Player %d's Hand Count After Turn Ends: %d\n", i, testG.handCount[i]);
        printf("Ending Cards In Player %d's Hand: \n", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("Card %d: From Hand %d, From handCard() %d\n", j, testG.hand[i][j], handCard(j, &testG));
            numErrors += assertTrue(testG.hand[i][j], handCard(j, &testG));
        }
        printf(";\n");
        
    }
    
    // ----------- TEST 2: CHECKING THAT handCard RETURNS APPROPRIATE CARDS IN THE HAND AFTER PLAYING SMITHY CARD --------------
    printf("TEST 2: CHECKING THAT handCard RETURNS APPROPRIATE CARDS IN THE HAND AFTER PLAYING SMITHY CARD\n");
    
    int handpos;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < testG.numPlayers; i++) {
        //Going to play smithy card so add to player's hand
        testG.hand[i][0] = smithy;
        handpos = 0;
        
        printf("Whose Turn = %d, Expected = %d\n", i, testG.whoseTurn);
        numErrors += assertTrue(i, testG.whoseTurn);
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Cards In Player %d's Hand: \n", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("Card %d: From Hand %d, From handCard() %d\n", j, testG.hand[i][j], handCard(j, &testG));
            numErrors += assertTrue(testG.hand[i][j], handCard(j, &testG));
        }
        printf(";\n");
        
        //Play smithy card to cause hand, deck, and discard to change
        playSmithy(&testG, i, handpos);
        printf("Player %d's Hand Count After Playing Smithy: %d\n", i, testG.handCount[i]);
        printf("Cards In Player %d's Hand: \n", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("Card %d: From Hand %d, From handCard() %d\n", j, testG.hand[i][j], handCard(j, &testG));
            numErrors += assertTrue(testG.hand[i][j], handCard(j, &testG));
        }
        printf(";\n");
        
        //Ending turn for this player
        printf("Ending Player %d's Turn\n", i);
        endTurn(&testG);
        
        printf("Player %d's Hand Count After Turn Ends: %d\n", i, testG.handCount[i]);
        printf("Ending Cards In Player %d's Hand: \n", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("Card %d: From Hand %d, From handCard() %d\n", j, testG.hand[i][j], handCard(j, &testG));
            numErrors += assertTrue(testG.hand[i][j], handCard(j, &testG));
        }
        printf(";\n");
    }
    

    
    if (numErrors == 0) {
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);
    } else {
        printf("\n ----- Assertion Failure %s -----\n", TESTUNIT);
    }
    
    
    return 0;
}
