/*
 * cardtest4.c
 * Bryan Resner
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

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
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
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
    
    // Playing the Village card always results with subtracting one card
    // from the currentPlayer's hand
    int numCardsPlayed = 1;
    
    //Putting the village card in position 2 of the currentPlayer's hand
    G.hand[currentPlayer][2] = village;
    int handpos = 2;
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    // ----------- TEST 1: ADDING CARD AND ACTION WHEN DECK HAS AT LEAST ONE CARD IN IT --------------
    printf("TEST 1: ADDING CARD AND ACTION WHEN DECK HAS AT LEAST ONE CARD IN IT\n");
    
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
    printf("Prior To Test - Current Player's Actions = %d\n", testG.numActions);
    
    cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    //Village adds one card and adds two actions
    int numCardsAdded = 1;
    int numActionsAdded = 2;
    
    int hCount = testG.handCount[currentPlayer];
    printf("After Test - Hand Count = %d, Expected = %d\n", hCount, G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    printf("After Test - Hand Ending Cards: ");
    
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    printf("After Test - Deck Cards: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    printf("After Test - Actions = %d, Expected = %d\n", testG.numActions, G.numActions + numActionsAdded);
    
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    numErrors += assertTrue(testG.coins, G.coins);
    numErrors += assertTrue(testG.numActions, G.numActions + numActionsAdded);
    
    // ----------- TEST 2: ADDING CARD AND ACTION WHEN DECK AND DISCARD ARE EMPTY --------------
    printf("TEST 2: ADDING CARD AND ACTION WHEN DECK AND DISCARD ARE EMPTY\n");
    
    //Force deck to have nothing in it.  Discard is empty from initialization
    G.deckCount[currentPlayer] = 0;
    
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
    printf("Prior To Test - Current Player's Actions = %d\n", testG.numActions);
    
    cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    //Village adds one card and adds two actions, but there is nothing to add
    //since the deck and discard pile are both empty
    numCardsAdded = 0;
    numActionsAdded = 2;
    
    hCount = testG.handCount[currentPlayer];
    printf("After Test - Hand Count = %d, Expected = %d\n", hCount, G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    printf("Ending Cards: ");
    
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    printf("After Test - Actions = %d, Expected = %d\n", testG.numActions, G.numActions + numActionsAdded);
    
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numCardsAdded);
    numErrors += assertTrue(testG.coins, G.coins);
    numErrors += assertTrue(testG.numActions, G.numActions + numActionsAdded);

    // ----------- TEST 3: ADDING CARD AND ACTION WHEN DECK AND DISCARD ARE EMPTY --------------
    printf("TEST 3: ADDING CARD AND ACTION WHEN DECK IS EMPTY BUT DISCARD IS NOT EMPTY\n");
    
    //Force deck to have nothing in it.
    G.deckCount[currentPlayer] = 0;
    
    G.discardCount[currentPlayer] = 2;
    G.discard[currentPlayer][0] = village;
    G.discard[currentPlayer][1] = silver;
    
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
    printf("Prior To Test - Current Player's Discard Count: %d\n", testG.discardCount[currentPlayer]);
    printf("Starting Cards In Current Player's Discard Pile: ");
    for (i = 0; i < testG.discardCount[currentPlayer]; i++) {
        printf("(%d) ", testG.discard[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Current Player's Coins = %d\n", testG.coins);
    printf("Prior To Test - Current Player's Actions = %d\n", testG.numActions);
    
    cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    //Village adds one card and adds two actions, but the
    //deck but not the discard pile, so we will add one card
    numCardsAdded = 1;
    numActionsAdded = 2;
    
    hCount = testG.handCount[currentPlayer];
    printf("After Test - Hand Count = %d, Expected = %d\n", hCount, G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    printf("Ending Cards: ");
    
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] + G.discardCount[currentPlayer] - numCardsAdded);
    printf("After Test - Cards In Current Player's Deck: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    // Discard will be empty
    printf("After Test - Discard Count = %d, Expected = %d\n", testG.discardCount[currentPlayer], 0);
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    printf("After Test - Actions = %d, Expected = %d\n", testG.numActions, G.numActions + numActionsAdded);
    
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + numCardsAdded - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] + G.discardCount[currentPlayer] - numCardsAdded);
    numErrors += assertTrue(testG.discardCount[currentPlayer], 0);
    numErrors += assertTrue(testG.coins, G.coins);
    numErrors += assertTrue(testG.numActions, G.numActions + numActionsAdded);
    
    if (numErrors == 0) {
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    } else {
        printf("\n ----- Assertion Failure %s -----\n", TESTCARD);
    }
    
    
    return 0;
}
