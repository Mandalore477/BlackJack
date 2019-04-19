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
	int splitResults[96][2];
	int splitNum;
	int splitWins = 0;
	int splitPush = 0;
	int splitLosses = 0;
	bool isSplit;
	
public:
	FPlayer();
	~FPlayer();
	void Play(Card hand[], Card deck[],int currentCard);
	int CalculateValue(Card hand[]);
	int GetCardInHand();
	void SetCardInHand(int value);
	void MakeBet();
	int GetBet();
	void GetWinnings(int winnings);
	void DisplayPlayer(Card hand[]);
	void Split(Card hand[],int chips, int bet);
	int GetChips();
	void ReBet();
	void CheckSplitResults(int dealerValue,bool dealerBust);
	void AddSplitResult(int value);
	int GetSplitNum();
	void AddSplitNum();
	void ResetSplit();
	bool GetStay();
	void Hit(Card hand[], Card deck[], int currentCard);
	bool IsPlayerBust();
	void DoubleDownOpt(Card hand[],Card deck[],int currentCard);
	bool IsSplit();

	Card blank;
	Card hand[5];
	Card splitHand[5];



};

