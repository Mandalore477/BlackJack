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

void FBlackJackGame::ShuffleDeck()
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

void FBlackJackGame::Insurance()
{
	char response=' ';
	if (Player.GetBet() / 2 < Player.GetChips())
	{
		while (response != 'y' && response != 'n')
		{
			std::cout << "Would you like to purchase Insurance Y/N";
			std::cin >> response;
			response = tolower(response);
		}
		if (response == 'y')
		{
			Player.ReBet();
			Player.GetWinnings(Player.GetBet() / 2);
		}
	}
	else
	{
		std::cout << "Not enough chips for Insurance" << std::endl;
	}
		if (dealerHand[1].value == 10)
		{
			system("cls");
			if (response == 'y')
			{
				std::cout << "You pay Insurance bet : " << Player.GetBet() / 2 << " Chips" << std::endl;
			}
			Player.DisplayPlayer(playerHand);
			Dealer.DisplayDealerPost(dealerHand);
			std::cout << "Dealer has BlackJack"<<std::endl;
			if (response == 'y')
			{
				std::cout << "You get insurance payout for : " << Player.GetBet() << " Chips" << std::endl;
				Player.GetWinnings(Player.GetBet());
			}
			Dealer.SetBlackJack(true);
			if (Player.CalculateValue(playerHand) == 21)
			{
				std::cout << "Player Push.   You get " << Player.GetBet() << " Chips" << std::endl;
			}
			system("pause");
		}
		else
		{
			system("cls");
			if (response == 'y')
			{
				std::cout << "You pay Insurance bet : " << Player.GetBet() / 2 << " Chips" << std::endl;
			}
			Player.DisplayPlayer(playerHand);
			Dealer.DisplayDealerPre(dealerHand);
			std::cout << "Dealer does not have BlackJack" << std::endl;

		}
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
	ShuffleDeck();

}

void FBlackJackGame::ResetHands(Card playerHand[], Card dealerHand[], Card playSplitHand[])
{
	Player.ResetPlayer(playerHand, playSplitHand);
	for (int32 i = 0; i < 5; i++)
	{
		dealerHand[i] = Dealer.blank;
		Dealer.SetCardInHand((0 - Dealer.GetCardInHand()));
	}
	Dealer.ResetStay();
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
		Player.DisplayPlayerPre();
		Player.MakeBet();
		system("cls");

		Deal(deck, playerHand, dealerHand);
		if (Dealer.CheckInsurance(dealerHand))
		{
			Insurance();
		}
		if (!Dealer.IsBlackJack())
		{

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
			Results();
		}
		system("pause");
	}
}

void FBlackJackGame::Results()
{
	if (Player.IsPlayBJ() && !Dealer.IsBlackJack())
	{
		if (CheckPush(playerHand))
		{
			std::cout << "Player Push.   You get " << Player.GetBet() << " Chips" << std::endl;
		}
		else
		{
			std::cout << "Player BlackJack.   You get " << Player.GetBet()*2.5 << " Chips" << std::endl;
		}
	}
	else if (!Player.IsPlayerBust() || !Player.IsSplitBust())
	{
		DealerPlay();
		int winnings = 0;
		int winningMulti = 0;
		int splitWinMulti = 0;
		FString playerResult;
		FString splitResult;
		//player results
		if (CheckPush(playerHand))
		{
			playerResult = "Player Push.   ";
			winningMulti = 1;
		}
		else if (CheckWin(playerHand)&&!Player.IsPlayerBust())
		{
			playerResult = "Player Wins.   ";
			winningMulti = 2;
		}
		else if (Player.IsPlayerBust())
		{
			playerResult = "Player Bust.   ";
		}
		else
		{
			playerResult = "Player Lost.   ";
		}
		if (playSplitHand[0].value > 0)
		{
			//split results
			if (CheckPush(playSplitHand))
			{
				splitResult = "Split Hand Push.   ";
				splitWinMulti = 1;
			}
			else if (CheckWin(playSplitHand)&& !Player.IsSplitBust())
			{
				splitResult = "Split Hand Wins.   ";
				splitWinMulti = 2;
			}
			else if (Player.IsSplitBust())
			{
				splitResult = "Split Hand Bust.   ";
			}
			else
			{
				splitResult = "Split Hand Lost.   ";
			}
			winnings = winnings + Player.GetBet()* winningMulti + Player.GetSplitBet()* splitWinMulti;
			std::cout << playerResult << splitResult << " You got " << winnings << " Chips" << std::endl;
			Player.GetWinnings(winnings);
		}
		else
		{
			winnings = winnings + Player.GetBet()* winningMulti;
			std::cout << playerResult <<  " You got " << winnings << " Chips" << std::endl;
			Player.GetWinnings(winnings);
		}
	}
	else
	{
		std::cout << "Player Bust.    You get 0 Chips"<<std::endl;
	}
	
}

void FBlackJackGame::DealerPlay()
{
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
}

bool FBlackJackGame::CheckPush(Card hand[])
{
	int handValue = Player.CalculateValue(hand);
	int dealerValue = Dealer.CalculateValue(dealerHand);
	if (handValue == dealerValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FBlackJackGame::CheckWin(Card hand[])
{
	int handValue = Player.CalculateValue(hand);
	int dealerValue = Dealer.CalculateValue(dealerHand);
	if (handValue > dealerValue || Dealer.IsDealerBust())
	{
		return true;
	}
	else
	{
		return false;
	}
}




