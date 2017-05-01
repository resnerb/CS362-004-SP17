/*
 * cardtest3.c
 * Bryan Resner
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "sea_hag"

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
    int currentPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    // Counter to track number of assert errors encountered without stopping
    // the execution of the test
    int numErrors = 0;
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    // Playing the Sea Hag card always results with subtracting one card
    // from the currentPlayer's hand
    int numCardsPlayed = 1;
    
    //Putting the sea hag card in position 2 of the currentPlayer's hand
    G.hand[currentPlayer][2] = sea_hag;
    int handpos = 2;
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    // ----------- TEST 1: ADDING CURSE CARD TO OTHER PLAYERS --------------
    printf("TEST 1: ADDING CURSE CARD TO OTHER PLAYERS\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Prior To Test - Current Player's Hand Count: %d\n", testG.handCount[currentPlayer]);
    printf("Starting Cards In Current Player's Hand: ");
    for (i = 0; i < testG.handCount[currentPlayer]; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Current Player's Deck Count: %d\n", testG.deckCount[currentPlayer]);
    printf("Starting Cards In Current Player's Deck: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Current Player's Coins = %d\n", testG.coins);
    
    printf("Prior To Test - Other Player's Deck:\n");
    for (i = 0; i < testG.numPlayers; i++) {
        if (i != currentPlayer) {
            printf("Player %d - Initial Deck Count: %d\n", i, testG.deckCount[i]);
            printf("Initial Deck Contents: ");
            for (j = 0; j < testG.deckCount[i]; j++) {
                printf("(%d) ", testG.deck[i][j]);
            }
            printf(";\n");
        }
    }
    
    playSeaHag(&testG, currentPlayer);
    
    //SeaHag does not change currentPlayer's hand, but adds curse card to top of other player's deck
    int numCardsAdded = 0;
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    printf("After Test - Hand Ending Cards: ");
    int hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    printf("After Test - Deck Ending Cards: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    numErrors += assertTrue(testG.coins, G.coins);
    
    printf("Other Player's Deck After Test:\n");
    for (i = 0; i < testG.numPlayers; i++) {
        if (i != currentPlayer) {
            printf("Player %d - Final Deck Count: %d\n", i, testG.deckCount[i]);
            printf("Final Deck Contents: ");
            for (j = 0; j < testG.deckCount[i]; j++) {
                printf("(%d) ", testG.deck[i][j]);
            }
            printf(";\n");
            printf("Top Card In Player %d's Deck: %d\n", i, testG.deck[i][testG.deckCount[i] - 1]);
            printf("Curse Card Is: %d\n", curse);
            numErrors += assertTrue(testG.deckCount[i], G.deckCount[i]);
            numErrors += assertTrue(testG.deck[i][testG.deckCount[i] - 1], curse);
        }
    }
    
    // ----------- TEST 2: ADDING CURSE CARD TO OTHER PLAYERS FOR MORE THAN 2 PLAYERS --------------
    printf("TEST 2: ADDING CURSE CARD TO OTHER PLAYERS FOR MORE THAN 2 PLAYERS\n");
    
    //Have to initialize game again with more players this time (numPlayers = 4)
    numPlayers = 4;
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    //Putting the sea hag card in position 2 of the currentPlayer's hand
    G.hand[currentPlayer][2] = sea_hag;
    handpos = 2;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Prior To Test - Current Player's Hand Count: %d\n", testG.handCount[currentPlayer]);
    printf("Starting Cards In Current Player's Hand: ");
    for (i = 0; i < testG.handCount[currentPlayer]; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Current Player's Deck Count: %d\n", testG.deckCount[currentPlayer]);
    printf("Starting Cards In Current Player's Deck: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Current Player's Coins = %d\n", testG.coins);
    
    printf("Prior To Test - Other Player's Deck:\n");
    for (i = 0; i < testG.numPlayers; i++) {
        if (i != currentPlayer) {
            printf("Player %d - Initial Deck Count: %d\n", i, testG.deckCount[i]);
            printf("Initial Deck Contents: ");
            for (j = 0; j < testG.deckCount[i]; j++) {
                printf("(%d) ", testG.deck[i][j]);
            }
            printf(";\n");
        }
    }
    
    playSeaHag(&testG, currentPlayer);
    
    //SeaHag does not change currentPlayer's hand, but adds curse card to top of other player's deck
    numCardsAdded = 0;
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    printf("After Test - Hand Ending Cards: ");
    hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    printf("After Test - Deck Ending Cards: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    numErrors += assertTrue(testG.coins, G.coins);
    
    printf("Other Player's Deck After Test:\n");
    for (i = 0; i < testG.numPlayers; i++) {
        if (i != currentPlayer) {
            printf("Player %d - Final Deck Count: %d\n", i, testG.deckCount[i]);
            printf("Final Deck Contents: ");
            for (j = 0; j < testG.deckCount[i]; j++) {
                printf("(%d) ", testG.deck[i][j]);
            }
            printf(";\n");
            printf("Top Card In Player %d's Deck: %d\n", i, testG.deck[i][testG.deckCount[i] - 1]);
            printf("Curse Card Is: %d\n", curse);
            numErrors += assertTrue(testG.deckCount[i], G.deckCount[i]);
            numErrors += assertTrue(testG.deck[i][testG.deckCount[i] - 1], curse);
        }
    }
    
    if (numErrors == 0) {
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    } else {
        printf("\n ----- Assertion Failure %s -----\n", TESTCARD);
    }
    
    
    return 0;
}
