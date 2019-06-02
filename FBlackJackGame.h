#ifndef FBLACKJACKGAME
#define FBLACKJACKGAME
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include"CardStruct.h"
#include"FPlayer.h"
#include"FDealer.h"
#include"FDeck.h"

// to make the syntax unreal friendly

using int32 = int;




class FBlackJackGame
{
private:
	int32 deckSize;
	int32 currentCard;
	Card blank;
	bool isPlay;
	Card deck[312];
	Card playerHand[5];
	Card dealerHand[5];
	Card playSplitHand[5];
	bool quit;


public:
	FBlackJackGame();// constructor

	int32 GetCurrentCard();
	void SetCurrentCard();
	void AddCurrentCard();
	void NumberOfPlayers();
	void ResetCurCard();
	void Insurance();
	bool GetIsPlay();
	void SetIsPlay(bool play);
	void SetGame();
	void Deal(Card playerHand[], Card dealerHand[]);
	void ResetHands(Card playerHand[], Card dealerHand[], Card playSplitHand[]);
	void PlayGame();
	void Results();
	void DealerPlay();
	bool CheckPush(Card hand[]);
	bool CheckWin(Card hand[]);
	bool GetQuit();
	void PrintIntro();
	void Smiley();
	
	
	int32 numberOfPlayers;
};

#endif