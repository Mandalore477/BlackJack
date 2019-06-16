#ifndef BJPLAYER
#define BJPLAYER
#include<iostream>
#include<string>
#include"CardStruct.h"


class FPlayer
{
private:

	bool bust;
	bool stay;
	int handTotal;
	int value;
	int cardInHand;
	bool playerIsActive;
	FString playerName;
	int chips = 1000;
	int bet;
	bool isSplit;
	bool splitStay;
	bool splitBust;
	int splitCardInHand;
	int splitValue;
	int splitBet;
	bool playBlackJack;
	char response;
	
public:
	FPlayer();
	FPlayer(Uint32 deltaT, Uint32 updatedTime, SDL_Renderer *renderer,Sprite *background, Sprite *playerCards[5], Sprite *dealerCards[5], Sprite *splitCards[5], Sprite *hitButton, Sprite *stayButton,
		Sprite *doDownButton,Sprite *surrenButton);
	~FPlayer();

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
	SDL_Renderer *renderer = NULL;
	
	void Play(Card hand[], Card *deckPtr,int currentCard);
	void SplitPlay(Card hand[], Card splitHand[], Card *deckPtr, int currentCard);
	int CalculateValue(Card hand[]);
	int GetCardInHand(Card hand[]);
	void MakeBet();
	int GetBet();
	void GetWinnings(int winnings);
	void DisplayPlayerPre();
	void DisplayPlayer(Card hand[]);
	void DisplaySplit(Card hand[], Card splitHand[]);
	bool IsSplit(Card hand[],int chips, int bet);
	int GetChips();
	void ReBet();
	void ResetPlayer(Card hand[], Card splitHand[]);

	bool GetStay();
	void Hit(Card hand[], Card *deckPtr, int currentCard,int cardInHand);
	void SplitHit(Card splitHand[], Card *deckPtr, int currentCard, int cardInHand);
	bool IsPlayerBust();
	bool IsSplitBust();
	bool GetSplitHandBust();
	void DoubleDownOpt(Card hand[],Card *deckPtr,int currentCard, int cardInHand);
	void SplitDoubleDownOpt(Card splitHand[],Card *deckPtr,int currentCard,int splitCardInHand);
	int GetSplitValue();
	int GetSplitBet();
	bool IsPlayBJ();

	void SetButtonVisible(bool hitButton, bool stayButton, bool doDownButton, bool surrenButton);
	void DrawScreen();
	bool ClickHit();
	bool ClickStay();
	bool ClickDoDown();
	bool ClickSurren();


	Card blank;
	Card hand[5];
	Card splitHand[5];



};

#endif 