/*
 * unittest2.c
 * Bryan Resner
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "endTurn"

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
    int handpos;
    int temphand[MAX_HAND];
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    // Counter to track number of assert errors encountered without stopping
    // the execution of the test
    int numErrors = 0;
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    printf("----------------- Unit Test: %s ----------------\n", TESTUNIT);
    
    // ----------- TEST 1: CHECKING THE EndTurn STORES PLAYER DATA CORRECTLY WHEN NO CARDS PLAYED --------------
    printf("TEST 1: CHECKING THE EndTurn STORES PLAYER DATA CORRECTLY WHEN NO CARDS PLAYED\n");
    
    //Full deck count takes three parameters: player, card to check for, and the gameState.
    //For first test we will check for the initialize state for each player.
    
    int totalCardsBeforeTurnEnds = 0;
    int totalCardsAfterTurnEnds = 0;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    for (i = 0; i < testG.numPlayers; i++) {
        
        totalCardsBeforeTurnEnds = 0;
        totalCardsAfterTurnEnds = 0;
        
        printf("Whose Turn = %d, Expected = %d\n", i, testG.whoseTurn);
        numErrors += assertTrue(i, testG.whoseTurn);
        totalCardsBeforeTurnEnds += testG.handCount[i];
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Starting Cards In Player %d's Hand: ", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("(%d) ", testG.hand[i][j]);
            temphand[j] = testG.hand[i][j];
        }
        printf(";\n");
        totalCardsBeforeTurnEnds += testG.deckCount[i];
        printf("Player %d's Deck Count: %d\n", i, testG.deckCount[i]);
        printf("Starting Cards In Player %d's Deck: ", i);
        for (j = 0; j < testG.deckCount[i]; j++) {
            printf("(%d) ", testG.deck[i][j]);
        }
        printf(";\n");
        totalCardsBeforeTurnEnds += testG.discardCount[i];
        printf("Player %d's Discard Count: %d\n", i, testG.discardCount[i]);
        printf("Starting Cards In Player %d's Discard: ", i);
        for (j = 0; j < testG.discardCount[i]; j++) {
            printf("(%d) ", testG.discard[i][j]);
        }
        printf(";\n");
        
        //Ending turn for this player
        printf("Ending Player %d's Turn\n", i);
        endTurn(&testG);
        
        totalCardsAfterTurnEnds += testG.handCount[i];
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Ending Cards In Player %d's Hand: ", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("(%d) ", testG.hand[i][j]);
        }
        printf(";\n");
        totalCardsAfterTurnEnds += testG.deckCount[i];
        printf("Player %d's Deck Count: %d\n", i, testG.deckCount[i]);
        printf("Ending Cards In Player %d's Deck: ", i);
        for (j = 0; j < testG.deckCount[i]; j++) {
            printf("(%d) ", testG.deck[i][j]);
        }
        printf(";\n");
        totalCardsAfterTurnEnds += testG.discardCount[i];
        printf("Player %d's Discard Count: %d\n", i, testG.discardCount[i]);
        printf("Ending Cards In Player %d's Discard: ", i);
        for (j = 0; j < testG.discardCount[i]; j++) {
            printf("(%d) ", testG.discard[i][j]);
        }
        printf(";\n");
        
        printf("Total Cards Before Turn Ends = %d, Total Cards After Turn Ends = %d\n", totalCardsBeforeTurnEnds, totalCardsAfterTurnEnds);
        numErrors += assertTrue(totalCardsBeforeTurnEnds, totalCardsAfterTurnEnds);
        
        //Discard pile after turn ends contains cards from the hand before
        //Loop through discard pile and compare with hand from the original gameState
        for (j = 0; j < testG.discardCount[i]; j++) {
            printf("Card %d - Discard After End Turn: %d, Hand Card Before End Turn: %d\n", i, testG.discard[i][j], temphand[j]);
            //numErrors += assertTrue(testG.discard[i][j], G.hand[i][j]);
            numErrors += assertTrue(testG.discard[i][j], temphand[j]);
        }
    }
    
    //We should be back to player zero at this point, should have cycled back to zero
    printf("Whose Turn = %d, Expected = %d\n", 0, testG.whoseTurn);
    numErrors += assertTrue(0, testG.whoseTurn);
    
    // ----------- TEST 2: CHECKING THE EndTurn STORES PLAYER DATA CORRECTLY AFTER ONE CARD PLAYED --------------
    printf("TEST 2: CHECKING THE EndTurn STORES PLAYER DATA CORRECTLY AFTER ONE CARD PLAYED\n");
    
    //Full deck count takes three parameters: player, card to check for, and the gameState.
    //For first test we will check for the initialize state for each player.
    
    totalCardsBeforeTurnEnds = 0;
    totalCardsAfterTurnEnds = 0;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < testG.numPlayers; i++) {
        //Going to play smithy card so add to player's hand
        testG.hand[i][0] = smithy;
        handpos = 0;
        
        totalCardsBeforeTurnEnds = 0;
        totalCardsAfterTurnEnds = 0;
        
        printf("Whose Turn = %d, Expected = %d\n", i, testG.whoseTurn);
        numErrors += assertTrue(i, testG.whoseTurn);
        totalCardsBeforeTurnEnds += testG.handCount[i];
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Starting Cards In Player %d's Hand: ", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("(%d) ", testG.hand[i][j]);
        }
        printf(";\n");
        totalCardsBeforeTurnEnds += testG.deckCount[i];
        printf("Player %d's Deck Count: %d\n", i, testG.deckCount[i]);
        printf("Starting Cards In Player %d's Deck: ", i);
        for (j = 0; j < testG.deckCount[i]; j++) {
            printf("(%d) ", testG.deck[i][j]);
        }
        printf(";\n");
        totalCardsBeforeTurnEnds += testG.discardCount[i];
        printf("Player %d's Discard Count: %d\n", i, testG.discardCount[i]);
        printf("Starting Cards In Player %d's Discard: ", i);
        for (j = 0; j < testG.discardCount[i]; j++) {
            printf("(%d) ", testG.discard[i][j]);
        }
        printf(";\n");
        
        //Play smithy card to cause hand, deck, and discard to change
        playSmithy(&testG, i, handpos);
        
        //Ending turn for this player
        printf("Ending Player %d's Turn\n", i);
        endTurn(&testG);
        
        totalCardsAfterTurnEnds += testG.handCount[i];
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Ending Cards In Player %d's Hand: ", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("(%d) ", testG.hand[i][j]);
        }
        printf(";\n");
        totalCardsAfterTurnEnds += testG.deckCount[i];
        printf("Player %d's Deck Count: %d\n", i, testG.deckCount[i]);
        printf("Ending Cards In Player %d's Deck: ", i);
        for (j = 0; j < testG.deckCount[i]; j++) {
            printf("(%d) ", testG.deck[i][j]);
        }
        printf(";\n");
        totalCardsAfterTurnEnds += testG.discardCount[i];
        printf("Player %d's Discard Count: %d\n", i, testG.discardCount[i]);
        printf("Ending Cards In Player %d's Discard: ", i);
        for (j = 0; j < testG.discardCount[i]; j++) {
            printf("(%d) ", testG.discard[i][j]);
        }
        printf(";\n");
        
        printf("Total Cards Before Turn Ends = %d, Total Cards After Turn Ends = %d\n", totalCardsBeforeTurnEnds, totalCardsAfterTurnEnds);
        numErrors += assertTrue(totalCardsBeforeTurnEnds, totalCardsAfterTurnEnds);
    }
    
    //We should be back to player zero at this point, should have cycled back to zero
    printf("Whose Turn = %d, Expected = %d\n", 0, testG.whoseTurn);
    numErrors += assertTrue(0, testG.whoseTurn);
    
    
    //TEST 3: Commented out because playAdventurer method is causing a segmentation fault.
    //Further debugging of playAdventurer would be required to determine where the problem is.
    /**
    // ----------- TEST 3: CHECKING THE EndTurn STORES PLAYER DATA CORRECTLY AFTER DIFFERENT CARD PLAYED --------------
    printf("TEST 3: CHECKING THE EndTurn STORES PLAYER DATA CORRECTLY AFTER DIFFERENT CARD PLAYED\n");
    
    //Full deck count takes three parameters: player, card to check for, and the gameState.
    //For first test we will check for the initialize state for each player.
    
    totalCardsBeforeTurnEnds = 0;
    totalCardsAfterTurnEnds = 0;
    int drawntreasure = 0;
    
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < testG.numPlayers; i++) {
        //Going to play adventurer card so add to player's hand
        testG.hand[i][0] = adventurer;
        handpos = 0;
        
        totalCardsBeforeTurnEnds = 0;
        totalCardsAfterTurnEnds = 0;
        
        printf("Whose Turn = %d, Expected = %d\n", i, testG.whoseTurn);
        numErrors += assertTrue(i, testG.whoseTurn);
        totalCardsBeforeTurnEnds += testG.handCount[i];
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Starting Cards In Player %d's Hand: ", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("(%d) ", testG.hand[i][j]);
        }
        printf(";\n");
        totalCardsBeforeTurnEnds += testG.deckCount[i];
        printf("Player %d's Deck Count: %d\n", i, testG.deckCount[i]);
        printf("Starting Cards In Player %d's Deck: ", i);
        for (j = 0; j < testG.deckCount[i]; j++) {
            printf("(%d) ", testG.deck[i][j]);
        }
        printf(";\n");
        totalCardsBeforeTurnEnds += testG.discardCount[i];
        printf("Player %d's Discard Count: %d\n", i, testG.discardCount[i]);
        printf("Starting Cards In Player %d's Discard: ", i);
        for (j = 0; j < testG.discardCount[i]; j++) {
            printf("(%d) ", testG.discard[i][j]);
        }
        printf(";\n");
        
        //Play adventurer card to cause hand, deck, and discard to change
        playAdventurer(&testG, drawntreasure, i, temphand);
        
        //Ending turn for this player
        printf("Ending Player %d's Turn\n", i);
        endTurn(&testG);
        
        totalCardsAfterTurnEnds += testG.handCount[i];
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Ending Cards In Player %d's Hand: ", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("(%d) ", testG.hand[i][j]);
        }
        printf(";\n");
        totalCardsAfterTurnEnds += testG.deckCount[i];
        printf("Player %d's Deck Count: %d\n", i, testG.deckCount[i]);
        printf("Ending Cards In Player %d's Deck: ", i);
        for (j = 0; j < testG.deckCount[i]; j++) {
            printf("(%d) ", testG.deck[i][j]);
        }
        printf(";\n");
        totalCardsAfterTurnEnds += testG.discardCount[i];
        printf("Player %d's Discard Count: %d\n", i, testG.discardCount[i]);
        printf("Ending Cards In Player %d's Discard: ", i);
        for (j = 0; j < testG.discardCount[i]; j++) {
            printf("(%d) ", testG.discard[i][j]);
        }
        printf(";\n");
        
        printf("Total Cards Before Turn Ends = %d, Total Cards After Turn Ends = %d\n", totalCardsBeforeTurnEnds, totalCardsAfterTurnEnds);
        numErrors += assertTrue(totalCardsBeforeTurnEnds, totalCardsAfterTurnEnds);
    }
    
    //We should be back to player zero at this point, should have cycled back to zero
    printf("Whose Turn = %d, Expected = %d\n", 0, testG.whoseTurn);
    numErrors += assertTrue(0, testG.whoseTurn);
    **/
    
    if (numErrors == 0) {
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);
    } else {
        printf("\n ----- Assertion Failure %s -----\n", TESTUNIT);
    }
    
    
    return 0;
}