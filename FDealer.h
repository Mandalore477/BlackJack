#pragma once
#include<iostream>
#include"FBlackJackGame.h"



class FDealer
{
private:
	bool stay;
	bool bust;
	int handTotal;
	int value;
	int cardInHand;
	bool playerIsActive;

public:
	FDealer();
	~FDealer();
	
	void Hit(Card hand[], Card deck[], int currentCard);
	int CalculateValue(Card hand[]);
	int GetCardInHand();
	void SetCardInHand();
	void DisplayDealerPre(Card hand[]);
	void DisplayDealerPost(Card hand[]);
	bool CheckInsurance(Card hand[]);
	bool IsDealerBust();

	Card blank;
	Card hand[];

};

