#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FUNC "isGameOver"

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

	int currcoins,returnval;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", FUNC);

    // ----------- TEST 1 --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test 1\n\n");
    returnval = isGameOver(&testG);
    printf("expecting return value 0\n");
    assert(returnval == 0);
    printf("Test1 Passed.\n");

    // ----------- TEST 2 --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test 2\n\n");
    testG.supplyCount[province] =0;
    returnval = isGameOver(&testG);
    printf("expecting return value 1\n");
    assert(returnval == 1);
    printf("Test2 Passed.\n");

    // ----------- TEST 3 --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test 3\n\n");
    testG.supplyCount[0] =0;
    testG.supplyCount[2] =0;
    testG.supplyCount[5] =0;
    returnval = isGameOver(&testG);
    printf("expecting return value 1\n");
    assert(returnval == 1);
    printf("Test3 Passed.\n");

    // ----------- TEST 4 --------------
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nStarting test 4\n\n");
    testG.supplyCount[0] =0;
    testG.supplyCount[5] =0;
    returnval = isGameOver(&testG);
    printf("expecting return value 0\n");
    assert(returnval == 0);
    printf("Test4 Passed.\n");


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", FUNC);

	return 0;
}