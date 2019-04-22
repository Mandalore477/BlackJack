#pragma once
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
	
public:
	FPlayer();
	~FPlayer();
	void Play(Card hand[], Card deck[],int currentCard);
	void SplitPlay(Card hand[], Card splitHand[], Card deck[], int currentCard);
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
	void Hit(Card hand[], Card deck[], int currentCard,int cardInHand);
	void SplitHit(Card splitHand[], Card deck[], int currentCard, int cardInHand);
	bool IsPlayerBust();
	bool IsSplitBust();
	bool GetSplitHandBust();
	void DoubleDownOpt(Card hand[],Card deck[],int currentCard, int cardInHand);
	void SplitDoubleDownOpt(Card splitHand[],Card deck[],int currentCard,int splitCardInHand);
	int GetSplitValue();
	int GetSplitBet();
	bool IsPlayBJ();


	Card blank;
	Card hand[5];
	Card splitHand[5];



};

