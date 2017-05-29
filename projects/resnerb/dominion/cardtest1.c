/*
 * cardtest1.c
 * Bryan Resner
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

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
    int temphand[MAX_HAND];
    int drawntreasure=0;
    int cardDrawn;
    
    // Counter to track number of assert errors encountered without stopping
    // the execution of the test
    int numErrors = 0;
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    // Playing the Adventurer card always results with subtracting one card
    // from the currentPlayer's hand
    int numCardsPlayed = 1;
    
    //Putting the adventurer card in position 2 of the currentPlayer's hand
    G.hand[currentPlayer][2] = adventurer;
    int handpos = 2;
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    printf("Adventurer card is positioned in the middle of currentPlayer's hand\n");
    
    // ----------- TEST 1: ADDING TWO TREASURE CARDS --------------
    printf("TEST 1: ADDING TWO TREASURE CARDS WHEN DECK CONTAINS AT LEAST TWO TREASURE CARDS\n");
    //The initializeGame() puts five cards in currentPlayer's hand and five cards
    //into currentPlayer's deck. Seven of the ten cards are copper, so the deck
    //has to have at least two copper's in it.
    
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
    
    drawntreasure=0;
    //playAdventurer(&testG, &drawntreasure, currentPlayer, temphand, handpos);
    adventurer_CARD(&testG, currentPlayer, temphand, handpos, &drawntreasure);

    //Since not sure how the deck was organized from the initializeGame() method,
    //don't know for sure how many cards were revealed in the deck before we got
    //the 2 treasure cards we know are in the deck, so won't check the deck count
    //after this test - we have other tests that will set and check the deck
    //after we play the Adventurer card
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    printf("Ending Cards: ");
    int hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("Checking Cards Added To Hand Are Treasure Cards: \n");
    int topCard = testG.hand[currentPlayer][hCount - 1];
    printf("Top Card In Hand: %d", topCard);
    printf("   Which is: ");
    if (topCard == copper) {
        printf("COPPER\n");
    } else if (topCard == silver) {
        printf("SILVER\n");
    } else if (topCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    int secondTopCard = testG.hand[currentPlayer][hCount - 2];
    printf("Second To Top Card In Hand: %d", secondTopCard);
    printf("   Which is: ");
    if (secondTopCard == copper) {
        printf("COPPER\n");
    } else if (secondTopCard == silver) {
        printf("SILVER\n");
    } else if (secondTopCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    printf("After Test - DrawnTreasure = %d, Expected = %d\n", drawntreasure, 2);
    
    numErrors += assertTrue(drawntreasure, 2);
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - drawntreasure);
    numErrors += assertTrue(testG.coins, G.coins);
    numErrors += assertTrueMult(topCard, copper, silver, gold);
    numErrors += assertTrueMult(secondTopCard, copper, silver, gold);
    
    // ----------- TEST 2: SET LOCATION OF TREASURE CARDS TO BE TOP TWO IN DECK --------------
    printf("TEST 2: SET LOCATION OF TREASURE CARDS TO BE TOP TWO IN DECK\n");
    
    G.deck[currentPlayer][0] = smithy;
    G.deck[currentPlayer][1] = estate;
    G.deck[currentPlayer][2] = village;
    G.deck[currentPlayer][3] = copper;
    G.deck[currentPlayer][4] = silver;
    
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
    
    drawntreasure=0;
    //playAdventurer(&testG, &drawntreasure, currentPlayer, temphand, handpos);
    adventurer_CARD(&testG, currentPlayer, temphand, cardDrawn, &drawntreasure);
    
    //Based on the deck setup the number of cards revealed is 2
    int numRevealed = 2;
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    printf("Ending Cards: ");
    hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numRevealed);
    printf("Ending Cards: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("Checking Cards Added To Hand Are Treasure Cards: \n");
    topCard = testG.hand[currentPlayer][hCount - 1];
    printf("Top Card In Hand: %d", topCard);
    printf("   Which is: ");
    if (topCard == copper) {
        printf("COPPER\n");
    } else if (topCard == silver) {
        printf("SILVER\n");
    } else if (topCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    secondTopCard = testG.hand[currentPlayer][hCount - 2];
    printf("Second To Top Card In Hand: %d", secondTopCard);
    printf("   Which is: ");
    if (secondTopCard == copper) {
        printf("COPPER\n");
    } else if (secondTopCard == silver) {
        printf("SILVER\n");
    } else if (secondTopCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    printf("After Test - DrawnTreasure = %d, Expected = %d\n", drawntreasure, 2);
    
    numErrors += assertTrue(drawntreasure, 2);
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numRevealed);
    numErrors += assertTrue(testG.coins, G.coins);
    numErrors += assertTrueMult(topCard, copper, silver, gold);
    numErrors += assertTrueMult(secondTopCard, copper, silver, gold);
    
    // ----------- TEST 3: SET LOCATION OF TREASURE CARDS TO BE BOTTOM TWO IN DECK --------------
    printf("TEST 3: SET LOCATION OF TREASURE CARDS TO BE BOTTOM TWO IN DECK\n");
    
    G.deck[currentPlayer][0] = copper;
    G.deck[currentPlayer][1] = silver;
    G.deck[currentPlayer][2] = smithy;
    G.deck[currentPlayer][3] = estate;
    G.deck[currentPlayer][4] = village;
    
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
    
    drawntreasure=0;
    //playAdventurer(&testG, &drawntreasure, currentPlayer, temphand, handpos);
    adventurer_CARD(&testG, currentPlayer, temphand, handpos, &drawntreasure);
    
    //Based on the deck setup the number of cards revealed is 5
    numRevealed = 5;
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    printf("Ending Cards: ");
    hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numRevealed);
    printf("Ending Cards: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("Checking Cards Added To Hand Are Treasure Cards: \n");
    topCard = testG.hand[currentPlayer][hCount - 1];
    printf("Top Card In Hand: %d", topCard);
    printf("   Which is: ");
    if (topCard == copper) {
        printf("COPPER\n");
    } else if (topCard == silver) {
        printf("SILVER\n");
    } else if (topCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    secondTopCard = testG.hand[currentPlayer][hCount - 2];
    printf("Second To Top Card In Hand: %d", secondTopCard);
    printf("   Which is: ");
    if (secondTopCard == copper) {
        printf("COPPER\n");
    } else if (secondTopCard == silver) {
        printf("SILVER\n");
    } else if (secondTopCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    printf("After Test - DrawnTreasure = %d, Expected = %d\n", drawntreasure, 2);
    
    numErrors += assertTrue(drawntreasure, 2);
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numRevealed);
    numErrors += assertTrue(testG.coins, G.coins);
    numErrors += assertTrueMult(topCard, copper, silver, gold);
    numErrors += assertTrueMult(secondTopCard, copper, silver, gold);
    
    // ----------- TEST 4: SET LOCATION OF TREASURE CARDS TO BE BOTTOM AND MIDDLE IN DECK --------------
    printf("TEST 4: SET LOCATION OF TREASURE CARDS TO BE BOTTOM AND MIDDLE IN DECK\n");
    
    G.deck[currentPlayer][0] = copper;
    G.deck[currentPlayer][1] = smithy;
    G.deck[currentPlayer][2] = silver;
    G.deck[currentPlayer][3] = estate;
    G.deck[currentPlayer][4] = village;
    
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
    
    drawntreasure=0;
    //playAdventurer(&testG, &drawntreasure, currentPlayer, temphand, handpos);
    adventurer_CARD(&testG, currentPlayer, temphand, handpos, &drawntreasure);
    
    //Based on the deck setup the number of cards revealed is 5
    numRevealed = 5;
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    printf("Ending Cards: ");
    hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numRevealed);
    printf("Ending Cards: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("Checking Cards Added To Hand Are Treasure Cards: \n");
    topCard = testG.hand[currentPlayer][hCount - 1];
    printf("Top Card In Hand: %d", topCard);
    printf("   Which is: ");
    if (topCard == copper) {
        printf("COPPER\n");
    } else if (topCard == silver) {
        printf("SILVER\n");
    } else if (topCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    secondTopCard = testG.hand[currentPlayer][hCount - 2];
    printf("Second To Top Card In Hand: %d", secondTopCard);
    printf("   Which is: ");
    if (secondTopCard == copper) {
        printf("COPPER\n");
    } else if (secondTopCard == silver) {
        printf("SILVER\n");
    } else if (secondTopCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    printf("After Test - DrawnTreasure = %d, Expected = %d\n", drawntreasure, 2);
    
    numErrors += assertTrue(drawntreasure, 2);
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numRevealed);
    numErrors += assertTrue(testG.coins, G.coins);
    numErrors += assertTrueMult(topCard, copper, silver, gold);
    numErrors += assertTrueMult(secondTopCard, copper, silver, gold);
    
    // ----------- TEST 5: SET DECK TO ONLY HAVE A SINGLE TREASURE CARD AND EMPTY DISCARD PILE--------------
    printf("TEST 5: SET DECK TO ONLY HAVE A SINGLE TREASURE CARD AND EMPTY DISCARD PILE\n");
    
    G.deck[currentPlayer][0] = duchy;
    G.deck[currentPlayer][1] = curse;
    G.deck[currentPlayer][2] = sea_hag;
    G.deck[currentPlayer][3] = gold;
    G.deck[currentPlayer][4] = feast;
    
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
    
    drawntreasure=0;
    //playAdventurer(&testG, &drawntreasure, currentPlayer, temphand, handpos);
    adventurer_CARD(&testG, currentPlayer, temphand, handpos, &drawntreasure);
    
    //Based on the deck setup with only a single treasure card in it and nothing
    //in the discard pile, the number of cards revealed is 5
    numRevealed = 5;
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    printf("Ending Cards: ");
    hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numRevealed);
    printf("Ending Cards: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("Checking Cards Added To Hand Are Treasure Cards: \n");
    topCard = testG.hand[currentPlayer][hCount - 1];
    printf("Top Card In Hand: %d", topCard);
    printf("   Which is: ");
    if (topCard == copper) {
        printf("COPPER\n");
    } else if (topCard == silver) {
        printf("SILVER\n");
    } else if (topCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    secondTopCard = testG.hand[currentPlayer][hCount - 2];
    printf("Second To Top Card In Hand: %d", secondTopCard);
    printf("   Which is: ");
    if (secondTopCard == copper) {
        printf("COPPER\n");
    } else if (secondTopCard == silver) {
        printf("SILVER\n");
    } else if (secondTopCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    printf("After Test - DrawnTreasure = %d, Expected = %d\n", drawntreasure, 1);
    
    numErrors += assertTrue(drawntreasure, 1);
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - numRevealed);
    numErrors += assertTrue(testG.coins, G.coins);
    numErrors += assertTrueMult(topCard, copper, silver, gold);
    numErrors += assertTrueMult(secondTopCard, copper, silver, gold);
    
    // ----------- TEST 6: SET DECK TO ONLY HAVE A SINGLE TREASURE CARD AND DISCARD PILE TO HAVE A SINGLE TREASURE CARD--------------
    printf("TEST 6: SET DECK TO ONLY HAVE A SINGLE TREASURE CARD AND DISCARD PILE TO HAVE A SINGLE TREASURE CARD\n");
    
    G.deck[currentPlayer][0] = duchy;
    G.deck[currentPlayer][1] = curse;
    G.deck[currentPlayer][2] = sea_hag;
    G.deck[currentPlayer][3] = gold;
    G.deck[currentPlayer][4] = feast;
    
    G.discardCount[currentPlayer] = 1;
    G.discard[currentPlayer][0] = silver;
    //G.discard[currentPlayer][1] = estate;
    
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
    printf("Starting Cards In Deck: ");
    for (i = 0; i < testG.discardCount[currentPlayer]; i++) {
        printf("(%d) ", testG.discard[currentPlayer][i]);
    }
    printf(";\n");
    printf("Prior To Test - Coins = %d\n", testG.coins);
    
    drawntreasure=0;
    //playAdventurer(&testG, &drawntreasure, currentPlayer, temphand, handpos);
    adventurer_CARD(&testG, currentPlayer, temphand, handpos, &drawntreasure);
    
    //Based on the deck setup with only a single treasure card in it and a single
    //treauser card in the discard pile, the number of cards revealed is 6
    numRevealed = 6;
    
    printf("After Test - Hand Count = %d, Expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    printf("Ending Cards: ");
    hCount = testG.handCount[currentPlayer];
    for (i = 0; i < hCount; i++) {
        printf("(%d) ", testG.hand[currentPlayer][i]);
    }
    printf(";\n");
    printf("After Test - Deck Count = %d, Expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] + G.discardCount[currentPlayer] - numRevealed);
    printf("Ending Cards: ");
    for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
        printf("(%d) ", testG.deck[currentPlayer][i]);
    }
    printf(";\n");
    printf("Checking Cards Added To Hand Are Treasure Cards: \n");
    topCard = testG.hand[currentPlayer][hCount - 1];
    printf("Top Card In Hand: %d", topCard);
    printf("   Which is: ");
    if (topCard == copper) {
        printf("COPPER\n");
    } else if (topCard == silver) {
        printf("SILVER\n");
    } else if (topCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    secondTopCard = testG.hand[currentPlayer][hCount - 2];
    printf("Second To Top Card In Hand: %d", secondTopCard);
    printf("   Which is: ");
    if (secondTopCard == copper) {
        printf("COPPER\n");
    } else if (secondTopCard == silver) {
        printf("SILVER\n");
    } else if (secondTopCard == gold) {
        printf("GOLD\n");
    } else {
        printf("Not a Treasure Card!!\n");
    }
    printf("After Test - Coins = %d, Expected = %d\n", testG.coins, G.coins);
    printf("After Test - DrawnTreasure = %d, Expected = %d\n", drawntreasure, 2);
    
    numErrors += assertTrue(drawntreasure, 2);
    numErrors += assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer] + drawntreasure - numCardsPlayed);
    numErrors += assertTrue(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] + G.discardCount[currentPlayer] - numRevealed);
    numErrors += assertTrue(testG.coins, G.coins);
    numErrors += assertTrueMult(topCard, copper, silver, gold);
    numErrors += assertTrueMult(secondTopCard, copper, silver, gold);
    
    
    if (numErrors == 0) {
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    } else {
        printf("\n ----- Assertion Failure %s -----\n", TESTCARD);
    }
    
    
    return 0;
}