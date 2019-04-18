#pragma once
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// to make the syntax unreal friendly
using FString = std::string;
using int32 = int;

struct Card
{
	int32 value = 0;
	FString suit = " ";
	FString face = " ";
};





class FBlackJackGame
{
private:
//	Card deck[deckSize];
	int32 deckSize;
	int32 currentCard;
	Card blank;
	bool isPlay;


public:
	FBlackJackGame();// constructor
	void MakeDeck(Card deck[]);
	void ShuffleDeck(Card deck[]);
	int32 GetDeckSize() const;
	int32 GetCurrentCard();
	void SetCurrentCard();
	void AddCurrentCard();
	void NumberOfPlayers();
	void ResetCurCard();
	bool GetIsPlay();
	void SetIsPlay(bool play);
	
	
	int32 numberOfPlayers;
};

