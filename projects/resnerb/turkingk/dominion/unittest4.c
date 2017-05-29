#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FUNC "fullDeckCount"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	int returnval,testcount;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", FUNC);
    testcount =0;
    // ----------- TEST --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test %d\n\n",++testcount);
    returnval = fullDeckCount(0,copper,&testG);
    printf("expecting copper count > 0\n");
    printf("current copper count: %d\n",returnval);
    assert(returnval == 7);
    printf("Test%d Passed.\n",testcount);

    // ----------- TEST --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test %d\n\n",++testcount);
    returnval = fullDeckCount(0,curse,&testG);
    printf("expecting curse count 0\n");
    printf("current curse count: %d\n",returnval);
    assert(returnval == 0);
    printf("Test%d Passed.\n",testcount);

    // ----------- TEST --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[0] =1;
    testG.deck[0][0] = 0;

    printf("\nStarting test %d\n\n",++testcount);
    returnval = fullDeckCount(0,0,&testG);
    printf("expecting card count 1\n");
    printf("current card count: %d\n",returnval);
    assert(returnval == 1);
    printf("Test%d Passed.\n",testcount);

    // ----------- TEST --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[0] =1;
    testG.deck[0][0] = 0;

    testG.handCount[0] =1;
    testG.hand[0][0] = 0;

    printf("\nStarting test %d\n\n",++testcount);
    returnval = fullDeckCount(0,0,&testG);
    printf("expecting card count 2\n");
    printf("current card count: %d\n",returnval);
    assert(returnval == 2);
    printf("Test%d Passed.\n",testcount);

    // ----------- TEST --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[0] =1;
    testG.deck[0][0] = 0;

    testG.handCount[0] =1;
    testG.hand[0][0] = 0;

    testG.discardCount[0] =2;
    testG.discard[0][0] = 0;
    testG.discard[0][1] = 0;

    printf("\nStarting test %d\n\n",++testcount);
    returnval = fullDeckCount(0,0,&testG);
    printf("expecting card count 4\n");
    printf("current card count: %d\n",returnval);
    assert(returnval == 4);
    printf("Test%d Passed.\n",testcount);



	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", FUNC);

	return 0;
}