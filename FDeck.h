#ifndef BJDECK
#define BJDECK

#include<iostream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include"CardStruct.h"


class FDeck
{
	Card deck[312];
	Card* deckPtr = &deck[0];
public:
	FDeck();
	~FDeck();
	void MakeDeck();
	void ShuffleDeck();
	Card* getDeckPtr();
	int getDeckSize();
};

#endif