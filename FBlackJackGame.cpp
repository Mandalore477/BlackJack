#pragma once
#include<iostream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "FBlackJackGame.h"


FPlayer Player;
FDealer Dealer;

FBlackJackGame::FBlackJackGame()
{

}


void FBlackJackGame::MakeDeck(Card deck[])
{
	for (int32 x = 1; x < 313; x++)
	{
		
		int32 size = x - 1;
		deck[size].value = x % 13;
		if (deck[size].value == 0)
		{
			deck[size].value = 13;
		}
		if (size % 52 < 13)
		{
			deck[size].suit = "Spades  ";
		}
		else if (size % 52 < 26)
		{
			deck[size].suit = "Hearts  ";
		}
		else if (size % 52 < 39)
		{
			deck[size].suit = "Clubs   ";
		}
		else
		{
			deck[size].suit = "Diamonds";
		}
		
		if (deck[size].value == 1)
		{
			deck[size].face = " A";
			deck[size].value = 11;
		}
		else if (deck[size].value == 2)
		{
			deck[size].face = " 2";
		}
		else if (deck[size].value == 3)
		{
			deck[size].face = " 3";
		}
		else if (deck[size].value == 4)
		{
			deck[size].face = " 4";
		}
		else if (deck[size].value == 5)
		{
			deck[size].face = " 5";
		}
		else if (deck[size].value == 6)
		{
			deck[size].face = " 6";
		}
		else if (deck[size].value == 7)
		{
			deck[size].face = " 7";
		}
		else if (deck[size].value == 8)
		{
			deck[size].face = " 8";
		}
		else if (deck[size].value == 9)
		{
			deck[size].face = " 9";
		}
		else if (deck[size].value == 10)
		{
			deck[size].face = "10";
		}
		else if (deck[size].value == 11)
		{
			deck[size].face = " J";
			deck[size].value = 10;
		}
		else if (deck[size].value == 12)
		{
			deck[size].face = " Q";
			deck[size].value = 10;
		}
		else if (deck[size].value == 13)
		{
			deck[size].face = " K";
			deck[size].value = 10;
		}
	//std::cout << deck[size].face << " " << deck[size].suit << deck[size].value << "\n";
	}
	system("pause");
	//return deck;
}

void FBlackJackGame::ShuffleDeck(Card deck[])
{
	Card holdCard;
		srand(time(NULL));
	for (int i = 0; i < 312; i++)
	{
		int randCard = rand() % 312;
		holdCard = deck[i];
		deck[i] = deck[randCard];
		deck[randCard] = holdCard;
		//std::cout << deck[i].face << " " << deck[i].suit << "\n";
	}

}

int32 FBlackJackGame::GetDeckSize() const
{
	const int32 decksize = 312;
	return deckSize;
}

int32 FBlackJackGame::GetCurrentCard()
{
	return currentCard;
}

void FBlackJackGame::SetCurrentCard()
{
	currentCard=currentCard+1;
}

void FBlackJackGame::AddCurrentCard()
{
	currentCard++;
}

void FBlackJackGame::NumberOfPlayers()
{
	std::cout << "How Many players?\n";
	std::cin >> numberOfPlayers;
}

void FBlackJackGame::ResetCurCard()
{
	currentCard = 0;
}

bool FBlackJackGame::GetIsPlay()
{
	return isPlay;
}

void FBlackJackGame::SetIsPlay(bool play)
{
	isPlay = play;
}

void FBlackJackGame::SetGame()
{
	Player.GetWinnings(Player.GetChips());
	//BJGame.NumberOfPlayers();
	ResetCurCard();
	MakeDeck(deck);
	ShuffleDeck(deck);

}

void FBlackJackGame::ResetHands(Card playerHand[], Card dealerHand[], Card playSplitHand[])
{
	Player.ResetPlayer(playerHand, playSplitHand);
	for (int32 i = 0; i < 5; i++)
	{
		dealerHand[i] = Dealer.blank;
		Dealer.SetCardInHand((0 - Dealer.GetCardInHand()));
		Dealer.ResetStay();

	}
}

void FBlackJackGame::Deal(Card Deck[], Card playerHand[], Card dealerHand[])
{
	for (int32 i = 0; i < 2; i++)
	{
		playerHand[i] = Deck[GetCurrentCard()];
		SetCurrentCard();
		dealerHand[i] = Deck[GetCurrentCard()];
		SetCurrentCard();
		//std::cout << "Player card " << playerHand[i].face << " " << playerHand[i].suit << std::endl;
		//std::cout << "Dealer card " << dealerHand[i].face << " " << dealerHand[i].suit << std::endl;

	}
	Player.DisplayPlayer(playerHand);
	Dealer.DisplayDealerPre(dealerHand);
}

void FBlackJackGame::PlayGame()
{
	while (GetCurrentCard() < 150 && !GetIsPlay())
	{
		ResetHands(playerHand, dealerHand, playSplitHand);
		Player.MakeBet();
		system("cls");

		Deal(deck, playerHand, dealerHand);
		if (Player.IsSplit(playerHand, Player.GetChips(), Player.GetBet()))
		{
			if (playerHand[0].value == 1) { playerHand[0].value = 11; }
			playSplitHand[0] = playerHand[1];
			AddCurrentCard();
			playSplitHand[1] = deck[GetCurrentCard()];
			AddCurrentCard();
			playerHand[1] = deck[GetCurrentCard()];
			system("cls");
			Player.DisplaySplit(playerHand, playSplitHand);
			Dealer.DisplayDealerPre(dealerHand);
			while (!Player.GetStay())
			{
				Player.SplitPlay(playerHand, playSplitHand, deck, GetCurrentCard());
				system("cls");
				AddCurrentCard();
				Player.DisplaySplit(playerHand, playSplitHand);
				Dealer.DisplayDealerPre(dealerHand);
			}
		}
		else
		{
			while (!Player.GetStay())
			{
				Player.Play(playerHand, deck, GetCurrentCard());
				system("cls");
				AddCurrentCard();
				Player.DisplayPlayer(playerHand);
				Dealer.DisplayDealerPre(dealerHand);
			}
		}
		while (!Dealer.GetStay())
		{
			Dealer.Hit(dealerHand, deck, GetCurrentCard());
			system("cls");
			AddCurrentCard();
			if (playSplitHand[0].value > 0)
			{
				Player.DisplaySplit(playerHand, playSplitHand);
			}
			else
			{
				Player.DisplayPlayer(playerHand);
			}
			Dealer.DisplayDealerPost(dealerHand);

		}
		system("pause");
	}
}




