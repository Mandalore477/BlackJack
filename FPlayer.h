#pragma once
#include"FBlackJackGame.h"
#include<iostream>
#include<string>



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
	int chips;
	int bet;
	bool isSplit;
	bool splitStay;
	bool splitBust;
	int splitCardInHand;
	int splitValue;
	
public:
	FPlayer();
	~FPlayer();
	void Play(Card hand[], Card deck[],int currentCard);
	void SplitPlay(Card hand[], Card splitHand[], Card deck[], int currentCard);
	int CalculateValue(Card hand[]);
	int GetCardInHand(Card hand[]);
	void SetCardInHand(int value);
	void MakeBet();
	int GetBet();
	void GetWinnings(int winnings);
	void DisplayPlayer(Card hand[]);
	void DisplaySplit(Card hand[], Card splitHand[]);
	bool IsSplit(Card hand[],int chips, int bet);
	int GetChips();
	void ReBet();

	bool GetStay();
	void Hit(Card hand[], Card deck[], int currentCard);
	bool IsPlayerBust();
	bool GetSplitHandBust();
	void DoubleDownOpt(Card hand[],Card deck[],int currentCard);
	int GetSplitValue();


	Card blank;
	Card hand[5];
	Card splitHand[5];



};

