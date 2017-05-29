CFLAGS = -Wall -fpic -coverage -lm

all: playdom player testDrawCard testBuyCard badTestDrawCard cardtestall unittestall

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

cardtest1:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest1.c rngs.o -o cardtest1 -lm -g
cardtest2:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest2.c rngs.o -o cardtest2 -lm -g
cardtest3:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest3.c rngs.o -o cardtest3 -lm -g
cardtest4:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest4.c rngs.o -o cardtest4 -lm -g
cardtest5:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest5.c rngs.o -o cardtest5 -lm -g
cardtestall: cardtest1 cardtest2 cardtest3 cardtest4 cardtest5

unittest1:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest1.c rngs.o -o unittest1 -lm -g
unittest2:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest2.c rngs.o -o unittest2 -lm -g
unittest3:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest3.c rngs.o -o unittest3 -lm -g
unittest4:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest4.c rngs.o -o unittest4 -lm -g
unittestall: unittest1 unittest2 unittest3 unittest4

unittestresults.out: unittest1 unittest2 unittest3 unittest4
	./cardtest1 > unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	./cardtest5 >> unittestresult.out
	./unittest1 >> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
	rm cardtest1 cardtest2 cardtest3 cardtest4 cardtest5
	rm unittest1 unittest2 unittest3 unittest4