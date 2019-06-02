#ifndef DEALER
#define DEALER
#include<iostream>
#include"FBlackJackGame.h"
#include"FDeck.h"



class FDealer
{
private:
	bool stay;
	bool bust;
	int handTotal;
	int value;
	int cardInHand;
	bool playerIsActive;
	bool blackJack;

public:
	FDealer();
	~FDealer();
	
	void Hit(Card hand[], Card *deckPtr, int currentCard);
	int CalculateValue(Card hand[]);
	int GetCardInHand();
	void SetCardInHand(int value);
	void DisplayDealerPre(Card hand[]);
	void DisplayDealerPost(Card hand[]);
	bool CheckInsurance(Card hand[]);
	bool IsDealerBust();
	bool GetStay();
	void ResetStay();
	bool IsBlackJack();
	void SetBlackJack(bool blackJack);

	Card blank;
	Card hand[5];

};

#endif