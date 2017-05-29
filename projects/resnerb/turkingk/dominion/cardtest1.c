#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define TESTCARD "smithy"

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

	int effect;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 --------------
	printf("\nStarting test 1\n\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	effect = cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	assert(effect == 0);
	printf("smithy returned success of 0\n");

	//-------------TEST 2--------------
	printf("Test1 Passed.\n");

	printf("\nStarting test 2\n\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	printf("Starting number of cards in hand:%d\n",numHandCards(&testG));

	effect = cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Current number of cards in hand:%d\n",numHandCards(&testG));
	printf("Expected number of cards in hand is 7.\n");

	assert(numHandCards(&testG) == 7);
	printf("Test2 Passed.\n");
    //----------------- END TEST 1 ------------------

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}

