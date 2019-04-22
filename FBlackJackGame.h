#pragma once
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include"CardStruct.h"
#include"FPlayer.h"
#include"FDealer.h"

// to make the syntax unreal friendly

using int32 = int;




class FBlackJackGame
{
private:
//	Card deck[deckSize];
	int32 deckSize;
	int32 currentCard;
	Card blank;
	bool isPlay;
	Card deck[312];
	Card playerHand[5];
	Card dealerHand[5];
	Card playSplitHand[5];


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
	void SetGame();
	void Deal(Card Deck[], Card playerHand[], Card dealerHand[]);
	void ResetHands(Card playerHand[], Card dealerHand[], Card playSplitHand[]);
	void PlayGame();
	
	
	int32 numberOfPlayers;
};

