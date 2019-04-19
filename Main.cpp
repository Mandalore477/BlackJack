#include <iostream> // input and output
#include "FBlackJackGame.h"
#include <string>
#include "FPlayer.h"
#include "FDealer.h"

// to make the syntax unreal friendly
using FString = std::string;
using int32 = int;

FBlackJackGame BJGame;
FPlayer Player;
FDealer Dealer;

void Deal(Card Deck[], Card playerHand[], Card dealerHand[]);
void ResetHands(Card playerHand[], Card dealerHand[]);
void SplitPlayer(Card hand[], Card deck[], Card dealerHand[]);

int main()
{
	Card deck[312];
	//BJGame.NumberOfPlayers();
	BJGame.ResetCurCard();
	BJGame.MakeDeck(deck);
	BJGame.ShuffleDeck(deck);
	Card playerHand[5];
	Card dealerHand[5];
	Player.GetWinnings(1000);
	
	while (BJGame.GetCurrentCard() < 150 && !BJGame.GetIsPlay())
	{
		ResetHands(playerHand, dealerHand);
		Player.MakeBet();
		system("cls");
		
		Deal(deck, playerHand, dealerHand);
		Player.SetCardInHand(2);
		Player.Split(playerHand, Player.GetChips(), Player.GetBet());
		if (Player.IsSplit())
		{
			SplitPlayer(playerHand, deck, dealerHand);
		}
		while (!Player.GetStay())
		{
			Player.Play(playerHand, deck, BJGame.GetCurrentCard());
			system("cls");
			BJGame.AddCurrentCard();
			Player.DisplayPlayer(playerHand);
			Dealer.DisplayDealerPre(dealerHand);
		}
		while (!Dealer.GetStay())
		{
			Dealer.Hit(dealerHand, deck, BJGame.GetCurrentCard());
			system("cls");
			BJGame.AddCurrentCard();
			Player.DisplayPlayer(playerHand);
			Dealer.DisplayDealerPost(dealerHand);
		
		}
		system("pause");
	}
	return 0;
}

void ResetHands(Card playerHand[], Card dealerHand[])
{
	for (int32 i = 0; i < 5; i++)
	{
		playerHand[i] = Player.blank;
		dealerHand[i] = Dealer.blank;
		Player.ResetSplit();
		Player.SetCardInHand((0 - Player.GetCardInHand()));
		Dealer.SetCardInHand((0 - Dealer.GetCardInHand()));
		Dealer.ResetStay();

	}
}

void Deal(Card Deck[], Card playerHand[], Card dealerHand[])
{
	for (int32 i = 0; i < 2; i++)
	{
		playerHand[i] = Deck[BJGame.GetCurrentCard()];
		BJGame.SetCurrentCard();
		dealerHand[i] = Deck[BJGame.GetCurrentCard()];
		BJGame.SetCurrentCard();
		//std::cout << "Player card " << playerHand[i].face << " " << playerHand[i].suit << std::endl;
		//std::cout << "Dealer card " << dealerHand[i].face << " " << dealerHand[i].suit << std::endl;
	
	}
	Player.DisplayPlayer(playerHand);
	Dealer.DisplayDealerPre(dealerHand);
}

void SplitPlayer(Card hand[],Card deck[],Card dealerHand[])
{
	FPlayer SplitPlay;
	for (int32 i = 0; i < 5; i++)
	{
		SplitPlay.hand[i] = SplitPlay.blank;
	}
	SplitPlay.hand[0] = hand[1];
	hand[1] = SplitPlay.blank;
	SplitPlay.hand[1] = deck[BJGame.GetCurrentCard()];
	BJGame.SetCurrentCard();
	Player.ReBet();
	SplitPlay.DisplayPlayer(SplitPlay.hand);
	Dealer.DisplayDealerPre(dealerHand);
	SplitPlay.Play(SplitPlay.hand, deck, BJGame.GetCurrentCard());
	Player.AddSplitResult(SplitPlay.CalculateValue(SplitPlay.hand));


}
//
//void Result()
//{
//	if (!Player.IsPlayerBust||Player.GetSplitNum()>0)
//	{
//
//	}
//	if (Player.IsPlayerBust() && Dealer.IsDealerBust())
//	{
//
//	}
//}