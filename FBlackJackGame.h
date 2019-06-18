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



class FBlackJackGame
{
private:
	int deckSize;
	int currentCard;
	Card blank;
	bool isPlay;
	Card deck[312];
	Card playerHand[5];
	Card dealerHand[5];
	Card playSplitHand[5];
	bool quit;


public:
	FBlackJackGame();// constructor
	FBlackJackGame(SDL_Renderer *renderer, Sprite *background);

	Uint32			deltaT = 75;			// defines delay in time for updating game loop
	Uint32			updatedTime = 0;			// used to determine if frame rate interval has elapsed

	Sprite *playerCards[5] = { nullptr ,nullptr,nullptr,nullptr,nullptr };
	Sprite *splitCards[5] = { nullptr ,nullptr,nullptr,nullptr,nullptr };
	Sprite *dealerCards[5] = { nullptr ,nullptr,nullptr,nullptr,nullptr };

	Sprite *background = nullptr;
	BJGraphics *cardSheet = nullptr;
	Sprite *hitButton = nullptr;
	Sprite *stayButton = nullptr;
	Sprite *doDownButton = nullptr;
	Sprite *surrenButton = nullptr;
	Sprite *bet100 = nullptr;
	Sprite *bet1000 = nullptr;
	
	SDL_Renderer *renderer = NULL;


	void DrawScreen();

	int GetCurrentCard();
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
	
	SDL_Event event;
	
	int numberOfPlayers;
};

#endif