/*
 * unittest1.c
 * Bryan Resner
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "fullDeckCount"

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
    int currentCard;
    int numCardsFound;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    // Counter to track number of assert errors encountered without stopping
    // the execution of the test
    int numErrors = 0;
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    printf("----------------- Unit Test: %s ----------------\n", TESTUNIT);
    
    // ----------- TEST 1: COUNTING NUMBER OF ESTATE & COPPER FOR EACH PLAYER AT START OF GAME --------------
    printf("TEST 1: COUNTING NUMBER OF ESTATE & COPPER FOR EACH PLAYER AT START OF GAME\n");
    
    //Full deck count takes three parameters: player, card to check for, and the gameState.
    //For first test we will check for the initialize state for each player.
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < testG.numPlayers; i++) {
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Starting Cards In Player %d's Hand: ", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("(%d) ", testG.hand[i][j]);
        }
        printf(";\n");
        printf("Player %d's Deck Count: %d\n", i, testG.deckCount[i]);
        printf("Starting Cards In Player %d's Deck: ", i);
        for (j = 0; j < testG.deckCount[i]; j++) {
            printf("(%d) ", testG.deck[i][j]);
        }
        printf(";\n");
        //Test for copper
        currentCard = copper;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Copper Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, 7);
        //Test for estate
        currentCard = estate;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Estate Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, 3);
        //Test for card other than copper or estate
        currentCard = smithy;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Smithy Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, 0);
    }
    
    // ----------- TEST 2: REPLACE 2 CARDS IN DECK WITH VILLAGE & GOLD --------------
    printf("TEST 2: REPLACE 2 CARDS IN DECK WITH VILLAGE & GOLD\n");
    
    //Full deck count takes three parameters: player, card to check for, and the gameState.
    //For second test replace a couple cards in the deck with village and gold.
    
    int numCopper = 0;
    int numEstate = 0;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < testG.numPlayers; i++) {
        numCopper = 0;
        numEstate = 0;
        testG.deck[i][0] = village;
        testG.deck[i][3] = gold;
        
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Starting Cards In Player %d's Hand: ", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("(%d) ", testG.hand[i][j]);
            if (testG.hand[i][j] == copper) {
                ++numCopper;
            }
            else if (testG.hand[i][j] == estate) {
                ++numEstate;
            }
        }
        printf(";\n");
        printf("Player %d's Deck Count: %d\n", i, testG.deckCount[i]);
        printf("Starting Cards In Player %d's Deck: ", i);
        for (j = 0; j < testG.deckCount[i]; j++) {
            printf("(%d) ", testG.deck[i][j]);
            if (testG.deck[i][j] == copper) {
                ++numCopper;
            }
            else if (testG.deck[i][j] == estate) {
                ++numEstate;
            }
        }
        printf(";\n");
        //Test for copper
        currentCard = copper;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Copper Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, numCopper);
        //Test for estate
        currentCard = estate;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Estate Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, numEstate);
        //Test for village
        currentCard = village;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Village Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, 1);
        //Test for gold
        currentCard = gold;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Gold Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, 1);
        //Test for some other kind of card
        currentCard = duchy;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Duchy Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, 0);
    }
    
    // ----------- TEST 3: ADD 2 CARDS TO THE DISCARD PILE --------------
    printf("TEST 3: ADD 2 CARDS TO THE DISCARD PILE\n");
    
    //Full deck count takes three parameters: player, card to check for, and the gameState.
    //For third test we will add two cards to the discard pile; steward and gold.

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < testG.numPlayers; i++) {
        numCopper = 0;
        numEstate = 0;
        
        testG.deck[i][0] = village;
        testG.deck[i][3] = gold;
        testG.discardCount[i] = 2;
        testG.discard[i][0] = steward;
        testG.discard[i][1] = gold;
        
        printf("Player %d's Hand Count: %d\n", i, testG.handCount[i]);
        printf("Starting Cards In Player %d's Hand: ", i);
        for (j = 0; j < testG.handCount[i]; j++) {
            printf("(%d) ", testG.hand[i][j]);
            if (testG.hand[i][j] == copper) {
                ++numCopper;
            }
            else if (testG.hand[i][j] == estate) {
                ++numEstate;
            }
        }
        printf(";\n");
        printf("Player %d's Deck Count: %d\n", i, testG.deckCount[i]);
        printf("Starting Cards In Player %d's Deck: ", i);
        for (j = 0; j < testG.deckCount[i]; j++) {
            printf("(%d) ", testG.deck[i][j]);
            if (testG.deck[i][j] == copper) {
                ++numCopper;
            }
            else if (testG.deck[i][j] == estate) {
                ++numEstate;
            }
        }
        printf(";\n");
        printf("Player %d's Discard Count: %d\n", i, testG.discardCount[i]);
        printf("Starting Cards In Player %d's Discard: ", i);
        for (j = 0; j < testG.discardCount[i]; j++) {
            printf("(%d) ", testG.discard[i][j]);
        }
        printf(";\n");
        //Test for copper
        currentCard = copper;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Copper Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, numCopper);
        //Test for estate
        currentCard = estate;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Estate Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, numEstate);
        //Test for village
        currentCard = village;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Village Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, 1);
        //Test for gold
        currentCard = gold;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Gold Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, 2);
        //Test for steward
        currentCard = steward;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Steward Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, 1);
        //Test for some other kind of card
        currentCard = duchy;
        numCardsFound = fullDeckCount(i, currentCard, &testG);
        printf("Number of Duchy Found: %d ", numCardsFound);
        numErrors += assertTrue(numCardsFound, 0);
    }
    
    if (numErrors == 0) {
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);
    } else {
        printf("\n ----- Assertion Failure %s -----\n", TESTUNIT);
    }
    
    
    return 0;
}
