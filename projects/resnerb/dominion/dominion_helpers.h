#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int playAdventurer(struct gameState *state, int *drawntreasure,
                   int currentPlayer, int *temphand);
int playSmithy(struct gameState *state, int currentPlayer, int handPos);
int playSeaHag(struct gameState *state, int currentPlayer);
int playSteward(struct gameState *state, int currentPlayer, int handPos,
                int choice1, int choice2, int choice3);
int playMinion(struct gameState *state, int currentPlayer, int handPos,
               int choice1, int choice2);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);


#endif
