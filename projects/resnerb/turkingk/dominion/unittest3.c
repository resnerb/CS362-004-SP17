#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FUNC "gainCard"

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

	int returnval;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", FUNC);

    // ----------- TEST 1 --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test 1\n\n");
    returnval = gainCard(0,&testG,0,0);
    printf("expecting return value 0\n");
    assert(returnval == 0);
    printf("Test1 Passed.\n");

    // ----------- TEST 2 --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test 2\n\n");
    gainCard(0,&testG,1,0);
    printf("expecting card 0 added to deck\n");
    assert(testG.deck[0][testG.deckCount[0] -1] == 0);
    printf("Test2 Passed.\n");

    // ----------- TEST 3 --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test 3\n\n");
    gainCard(0,&testG,2,0);
    printf("expecting card 0 added to hand\n");
    assert(testG.hand[0][testG.handCount[0] -1] == 0);
    printf("Test3 Passed.\n");

    // ----------- TEST 4 --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test 4\n\n");
    gainCard(0,&testG,0,0);
    printf("expecting card 0 added to discard\n");
    assert(testG.discard[0][testG.discardCount[0] -1] == 0);
    printf("Test4 Passed.\n");

    // ----------- TEST 5 --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test 5\n\n");
    printf("starting supply count of card 0 is: %d\n",testG.supplyCount[0]);
    gainCard(0,&testG,0,0);
    printf("expecting supply count of card 0 is: 9\n");
    assert(testG.supplyCount[0]==9);
    printf("Test5 Passed.\n");

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", FUNC);

	return 0;
}