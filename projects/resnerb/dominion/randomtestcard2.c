//
//  randomtestcard2.c
//  Assignment 4
//
//  Created by Bryan Resner on 5/14/17.
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

int checkVillage(int p, struct gameState *post, int iteration, int handPos) {
    
    int i;
    int numErrors = 0;
    int numVillageFound = 0;
    int numCardsBefore = 0;
    //int numCardsAfter = 0;
    
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    //Check to make sure player's hand contains an Village card, if not we should
    //never make this call
    //NOTE: In main function we are forcing the player's hand to have an Village
    //card, but this is a test we should make sure is true
    for (i = 0; i < post->handCount[p]; i++) {
        if (post->hand[p][i] == village) {
            numVillageFound++;
        }
    }
    //assertTrueGreaterThan(numVillageFound, 0);
    
    //Count up number of cards in deck and discard pile
    numCardsBefore = post->deckCount[p] + post->discardCount[p];
    
    cardEffect(village, 0, 0, 0, post, handPos, 0);
    
    //Check to make sure the number of cards in hand increased by one card
    //that were added by playing the Village and the played card that was substracted
    //NOTE: If the original deck and discard pile had less than one card in it, then
    //the Village will not be able to add any cards
    if (numCardsBefore >= 1) {
        numErrors += assertTrueExt(post->handCount[p], pre.handCount[p] + 1 - post->playedCardCount, iteration, 116);
    }
    else {
        numErrors += assertTrueExt(post->handCount[p], pre.handCount[p] - post->playedCardCount, iteration, 119);
    }
    
    //Check that actions increased by two
    numErrors += assertTrueExt(post->numActions, pre.numActions + 2, iteration, 123);
    
    if (pre.deckCount[p] >= 1) {
        //Take cards off top of deck, do not need to use discard pile
        //Card 1
        pre.handCount[p]++;
        pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
        pre.deckCount[p]--;
        
        //Account for removing the Village card
        
        //set played card to -1
        pre.hand[p][handPos] = -1;
        
        //remove card from player's hand
        if (handPos == (pre.handCount[p] - 1)) 	//last card in hand array is played
        {
            //reduce number of cards in hand
            pre.handCount[p]--;
        }
        else if (pre.handCount[p] == 1) //only one card in hand
        {
            //reduce number of cards in hand
            pre.handCount[p]--;
        }
        else
        {
            //replace discarded card with last card in hand
            pre.hand[p][handPos] = pre.hand[p][(pre.handCount[p] - 1)];
            //set last card to -1
            pre.hand[p][pre.handCount[p] - 1] = -1;
            //reduce number of cards in hand
            pre.handCount[p]--;
        }
        memcpy(pre.playedCards, post->playedCards, sizeof(int) * MAX_DECK);
        pre.playedCardCount = post->playedCardCount;
        pre.numActions += 2;
        
    } else if (pre.discardCount[p] > 0) {
        memcpy(pre.hand[p], post->hand[p], sizeof(int) * MAX_DECK);
        pre.handCount[p] = post->handCount[p];
        
        memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
        memcpy(pre.discard[p], post->discard[p], sizeof(int) * pre.discardCount[p]);
        pre.deckCount[p] = pre.discardCount[p]-1;
        pre.discardCount[p] = 0;
        memcpy(pre.playedCards, post->playedCards, sizeof(int) * MAX_DECK);
        pre.playedCardCount = post->playedCardCount;
        pre.numActions += 2;
    }
    
    //Check played card is Village card
    
    numErrors += assertTrueExt(memcmp(&pre, post, sizeof(struct gameState)), 0, iteration, 176);
    
    return numErrors;
}

int main () {
    
    int i, j, n, p;
    int cardType;
    int cardPos;
    int numErrors = 0;
    int numVillageFound = 0;
    
    //int k[10] = {adventurer, council_room, feast, gardens, mine,
    //remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf ("Testing Village.\n");
    
    printf ("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    for (n = 0; n < 2000; n++) {
        //Initialize to zero for each iteration
        numVillageFound = 0;
        
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = (int)floor(Random() * 256);
        }
        
        //Need to initialize the playedCardCount to zero
        //We must do this because it will be updated when we play the Village card
        //The initialization above sets this to a garbage value
        G.playedCardCount = 0;
        
        p = (int)floor(Random() * 2);
        
        //Set the player's turn to one we just selected, since village is being played
        //through the cardEffect method it figures out the player from the gameState
        G.whoseTurn = p;
        
        //Set number of actions to a random number
        G.numActions = 1 + (int)floor(Random() * 10);
        
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
        G.handCount[p] = (int)floor(Random() * MAX_HAND);
        for (j = 0; j < G.handCount[p]; j++) {
            //Filling the hand with legitimate random cards
            cardType = (int)floor(Random() * 27);
            G.hand[p][j] = cardType;
            if (cardType == village) {
                numVillageFound++;
                cardPos = j;
            }
        }
        //Make sure hand contains at least one village card
        if (numVillageFound == 0) {
            //Force village into player's hand
            cardPos = (int)floor(Random() * G.handCount[p]);
            G.hand[p][cardPos] = village;
        }
        
        numErrors += checkVillage(p, &G, n, cardPos);
    }
    
    if (numErrors == 0) {
        printf("\n >>>>> SUCCESS: Random Testing Of %s Complete <<<<<\n\n", TESTCARD);
    } else {
        printf("\n !!!!! Random Testing Failed %s (Number Errors Found: %d) !!!!!\n", TESTCARD, numErrors);
    }
    
    return 0;
}
