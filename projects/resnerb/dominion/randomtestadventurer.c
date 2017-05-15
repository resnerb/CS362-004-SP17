//
//  randomtestadventurer.c
//  Assignment 4
//
//  Created by Bryan Resner on 5/13/17.
//
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

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

int assertTrueExt(int lhs, int rhs, int iteration, int lineNum) {
    if (lhs != rhs) {
        printf("----- ASSERT TRUE FAILED on Iteration %d at line %d: Value LHS: %d, Value RHS: %d \n", iteration, lineNum, lhs, rhs);
        //printf("Value LHS: %d\n", lhs);
        //printf("Value RHS: %d\n", rhs);
        return 1;
    }
    else {
        return 0;
    }
}

int assertTrueGreaterThan(int lhs, int rhs) {
    if (lhs <= rhs) {
        printf("----- ASSERT TRUE GREATER THAN FAILED -----\n");
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

int checkPlayAdventurer(int p, struct gameState *post, int iteration, int handPos) {
    int i;
    int numErrors = 0;
    int numAdventurersFound = 0;
    int numTreasuresDDOriginal = 0;
    int numTreasuresDDFinal = 0;
    int numTreasuresHandOriginal = 0;
    int numTreasuresHandFinal = 0;
    int drawnTreasure = 0;
    int tempHand[MAX_HAND];
    
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    //Counting up number of treasure cards in deck and discard piles
    for (i = 0; i < post->deckCount[p]; i++) {
        if (post->deck[p][i] == copper || post->deck[p][i] == silver || post->deck[p][i] == gold) {
            numTreasuresDDOriginal++;
        }
    }
    for (i = 0; i < post->discardCount[p]; i++) {
        if (post->discard[p][i] == copper || post->discard[p][i] == silver || post->discard[p][i] == gold) {
            numTreasuresDDOriginal++;
        }
    }
    
    //Counting up number of treasure cards in player's hand before Adventurer
    //card is played
    for (i = 0; i < post->handCount[p]; i++) {
        if (post->hand[p][i] == copper || post->hand[p][i] == silver || post->hand[p][i] == gold) {
            numTreasuresHandOriginal++;
        }
    }
    
    //Check to make sure player's hand contains an Adventurer card, if not we should
    //never make this call
    //NOTE: In main function we are forcing the player's hand to have an adventurer
    //card, but this is a test we should make sure is true
    for (i = 0; i < post->handCount[p]; i++) {
        if (post->hand[p][i] == adventurer) {
            numAdventurersFound++;
        }
    }
    assertTrueGreaterThan(numAdventurersFound, 0);
    
    playAdventurer(post, &drawnTreasure, p, tempHand, handPos);
    
    //Look through deck and look through discard pile and see how many treasure
    //cards are in each. Then compare to pre and post gameState to see if the difference
    //is correct.
    
    //Check to make sure the number of cards in hand increased by drawnTreasure cards
    //that were added and the played card that was substracted
    //NOTE: playAdventurer does not discard the Adventurer card, which it should do, so
    //this should cause an error
    numErrors += assertTrueExt(post->handCount[p], pre.handCount[p] + drawnTreasure - post->playedCardCount, iteration, 138);
    
    for (i = 0; i < post->handCount[p]; i++) {
        if (post->hand[p][i] == copper || post->hand[p][i] == silver || post->hand[p][i] == gold) {
            numTreasuresHandFinal++;
        }
    }
    
    //Check to make sure the increase in hand size was due to adding treasure cards
    numErrors += assertTrueExt(numTreasuresHandOriginal + drawnTreasure, numTreasuresHandFinal, iteration, 147);
    
    //Counting up number of treasure cards in deck and discard piles after
    //playAdventurer called
    for (i = 0; i < post->deckCount[p]; i++) {
        if (post->deck[p][i] == copper || post->deck[p][i] == silver || post->deck[p][i] == gold) {
            numTreasuresDDFinal++;
        }
    }
    for (i = 0; i < post->discardCount[p]; i++) {
        if (post->discard[p][i] == copper || post->discard[p][i] == silver || post->discard[p][i] == gold) {
            numTreasuresDDFinal++;
        }
    }
    
    //Check to make sure number of treasure cards in deck and discard went down by
    //the number that were put into the hand
    numErrors += assertTrueExt(numTreasuresDDOriginal - drawnTreasure, numTreasuresDDFinal, iteration, 164);
    
    //Check to make sure the difference between the deck + discard before we called
    //playAdventurer is equal to drawnTreasure after calling playAdventurer
    numErrors += assertTrueExt(pre.discardCount[p] + pre.deckCount[p] - drawnTreasure, post->discardCount[p] + post->deckCount[p], iteration, 168);
    
    return numErrors;
}

int main () {
    
    int i, j, n, p, cardType, cardPos;
    int numErrors = 0;
    int numAdventurersFound = 0;
    
    //int k[10] = {adventurer, council_room, feast, gardens, mine,
	       //remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf ("Testing playAdventurer.\n");
    
    printf ("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    for (n = 0; n < 2000; n++) {
        
        //Inititalize counter for each iteration
        numAdventurersFound = 0;
        
        //Initialize random game state
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = (int)floor(Random() * 256);
        }
        
        //Need to initialize the playedCardCount to zero
        //We must do this because it will be updated when we play the adventurer card
        //The initialization above sets this to a garbage value
        G.playedCardCount = 0;
        
        p = (int)floor(Random() * 2);
        
        G.deckCount[p] = (int)floor(Random() * MAX_DECK);
        for (j = 0; j < G.deckCount[p]; j++) {
            //Filling the deck with legitimate random cards
            G.deck[p][j] = (int)floor(Random() * 27);
        }
        
        G.discardCount[p] = (int)floor(Random() * MAX_DECK);
        for (j = 0; j < G.discardCount[p]; j++) {
            //Filling the discard with legitimate random cards
            G.discard[p][j] = (int)floor(Random() * 27);
        }
        
        //Hand count must have at least one card in it, namely the adventurer card
        G.handCount[p] = 1 + (int)floor(Random() * MAX_HAND);
        for (j = 0; j < G.handCount[p]; j++) {
            //Filling the hand with legitimate random cards
            cardType = (int)floor(Random() * 27);
            G.hand[p][j] = cardType;
            if (cardType == adventurer) {
                numAdventurersFound++;
                cardPos = j;
            }
        }
        
        //Make sure hand contains at least one adventurer card
        if (numAdventurersFound == 0) {
            //Force adventurer into player's hand
            cardPos = (int)floor(Random() * G.handCount[p]);
            G.hand[p][cardPos] = adventurer;
        }
        numErrors += checkPlayAdventurer(p, &G, n, cardPos);
    }
    
    if (numErrors == 0) {
        printf("\n >>>>> SUCCESS: Random Testing Of %s Complete <<<<<\n\n", TESTCARD);
    } else {
        printf("\n !!!!! Random Testing Failed %s (Number Errors Found: %d) !!!!!\n", TESTCARD, numErrors);
    }
    
    return 0;
}
