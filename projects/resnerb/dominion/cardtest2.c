/*
 * cardtest2.c
 * Bryan Resner
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

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
    int currentPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    // Counter to track number of assert errors encountered without stopping
    // the execution of the test
    int numErrors = 0;
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    // Playing the Smithy card always results with subtracting one card
    // from the currentPlayer's hand
    int numCardsPlayed = 1;
    
    //Putting the smithy card in position 2 of the currentPlayer's hand
    G.hand[currentPlayer][2] = smithy;
    int handpos = 2;
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    // ----------- TEST 1: ADDING THREE CARDS WHEN DECK HAS THREE OR MORE CARDS --------------
    printf("TEST 1: ADDING THREE CARDS WHEN DECK HAS THREE OR MORE CARDS\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Prior To Test - Hand Count: %d\n", testG.handCount[currentPlayer]);
    printf("Starting Cards In Hand: ");
    for (i = 0; i < testG.handCount[currentPlayer]; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Deck Count: %d\n", testG.deckCount[currentPlayer]);
    printf("Starting Cards In Deck: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Coins = %d\n", testG.coins);
    printf("Prior To Test - Card Position In Hand = %d\n", handpos);
    
    playSmithy(&testG, currentPlayer, handpos);
    
    //Smithy is supposed to add 3 cards to currentPlayer's hand
    int numCardsAdded = 3;
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    printf("Ending Cards: ");
    int hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    numErrors += assertTrue(testG.coins, G.coins);
    
    // ----------- TEST 2: DECK ONLY HAS TWO CARDS AND DISCARD PILE IS EMPTY --------------
    printf("TEST 2: DECK ONLY HAS TWO CARDS AND DISCARD PILE IS EMPTY\n");
    
    G.deckCount[currentPlayer] = 2;
    G.deck[currentPlayer][0] = steward;
    G.deck[currentPlayer][1] = gold;
    
    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Prior To Test - Hand Count: %d\n", testG.handCount[currentPlayer]);
    printf("Starting Cards In Hand: ");
    for (i = 0; i < testG.handCount[currentPlayer]; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Deck Count: %d\n", testG.deckCount[currentPlayer]);
    printf("Starting Cards In Deck: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Coins = %d\n", testG.coins);
    printf("Prior To Test - Card Position In Hand = %d\n", handpos);
    
    playSmithy(&testG, currentPlayer, handpos);
    
    //Smithy is suppose to add 3 cards to currentPlayer's hand, but there are only 2 cards in the deck
    numCardsAdded = 2;
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    printf("Ending Cards: ");
    hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    numErrors += assertTrue(testG.coins, G.coins);
    
    // ----------- TEST 3: DECK ONLY HAS TWO CARDS AND DISCARD PILE HAS TWO CARDS --------------
    printf("TEST 3: DECK ONLY HAS TWO CARDS AND DISCARD PILE HAS TWO CARDS\n");
    
    G.deckCount[currentPlayer] = 2;
    G.deck[currentPlayer][0] = steward;
    G.deck[currentPlayer][1] = gold;
    
    G.discardCount[currentPlayer] = 2;
    G.discard[currentPlayer][0] = village;
    G.discard[currentPlayer][1] = silver;
    
    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Prior To Test - Hand Count: %d\n", testG.handCount[currentPlayer]);
    printf("Starting Cards In Hand: ");
    for (i = 0; i < testG.handCount[currentPlayer]; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Deck Count: %d\n", testG.deckCount[currentPlayer]);
    printf("Starting Cards In Deck: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Discard Count: %d\n", testG.discardCount[currentPlayer]);
    printf("Starting Cards In Discard: ");
    for (i = 0; i < testG.discardCount[currentPlayer]; i++) {
        printf("(%d) ", testG.discard[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Coins = %d\n", testG.coins);
    printf("Prior To Test - Card Position In Hand = %d\n", handpos);
    
    playSmithy(&testG, currentPlayer, handpos);
    
    //Smithy is suppose to add 3 cards to currentPlayer's hand, but there are only 2 cards in the deck,
    //but there are also two cards in the discard
    numCardsAdded = 3;
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    printf("Ending Cards: ");
    hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] + G.discardCount[currentPlayer] - numCardsAdded);
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Discard Count = %d, Expected = %d\n", testG.discardCount[currentPlayer], 0);
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] + G.discardCount[currentPlayer] - numCardsAdded);
    numErrors += assertTrue(testG.discardCount[currentPlayer], 0);
    numErrors += assertTrue(testG.coins, G.coins);
    
    if (numErrors == 0) {
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    } else {
        printf("\n ----- Assertion Failure %s -----\n", TESTCARD);
    }
    
    
    return 0;
}
