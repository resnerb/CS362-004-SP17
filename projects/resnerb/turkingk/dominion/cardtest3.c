#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define TESTCARD "steward"

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
	effect = cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	assert(effect == 0);
	printf("steward returned success of 0\n");
	printf("Test1 Passed.\n");

	//-------------TEST 2--------------
	printf("\nStarting test 2\n\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	printf("Starting number of cards in hand:%d\n",numHandCards(&testG));

	effect = cardEffect(steward, 1, choice2, choice3, &testG, handpos, &bonus);
	printf("Current number of cards in hand:%d\n",numHandCards(&testG));
	printf("Expected number of cards in hand is 6.\n");

	assert(numHandCards(&testG) == 6);
	printf("Test2 Passed.\n");

	//-------------TEST 3--------------
	printf("\nStarting test 3\n\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	printf("Starting number of coins in hand:%d\n",testG.coins);

	effect = cardEffect(steward, 2, choice2, choice3, &testG, handpos, &bonus);
	printf("Current number of coins:%d\n",testG.coins);
	printf("Expected number of coins 6.\n");

	assert(testG.coins == 6);
	printf("Test3 Passed.\n");

	//-------------TEST 4--------------
	printf("\nStarting test 4\n\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	printf("Starting number of cards in hand:%d\n",numHandCards(&testG));

	effect = cardEffect(steward, 0, choice2, choice3, &testG, handpos, &bonus);
	printf("Current number of cards in hand:%d\n",numHandCards(&testG));
	printf("Expected number of cards in hand is 2.\n");

	assert(numHandCards(&testG) == 2);
	printf("Test4 Passed.\n");

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}

