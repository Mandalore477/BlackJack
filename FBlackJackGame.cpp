#pragma once
#include<iostream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "FBlackJackGame.h"

FPlayer Player;
FDealer Dealer;
FDeck Deck;

FBlackJackGame::FBlackJackGame()
{

}

FBlackJackGame::FBlackJackGame(SDL_Renderer *renderer, Sprite * background)
{
	this->renderer = renderer;
	this->background = background;
}




void FBlackJackGame::DrawScreen()
{
	background->draw();
	for (int i = 0; i < 5; i++)
	{
		playerCards[i]->drawCard();
		splitCards[i]->drawCard();
		dealerCards[i]->drawCard();
	}
	hitButton->drawCard();
	stayButton->drawCard();
	doDownButton->drawCard();
	surrenButton->drawCard();

	/** Update display */
	SDL_RenderPresent(renderer);

	/** update time */
	updatedTime = SDL_GetTicks();
}

int FBlackJackGame::GetCurrentCard()
{
	return currentCard;
}

void FBlackJackGame::SetCurrentCard()
{
	currentCard++;
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
	Player.response=' ';

	if (Player.GetBet() / 2 < Player.GetChips())
	{
		while (Player.response != 'a' && Player.response != 's')
		{
			if (SDL_GetTicks() - updatedTime >= deltaT)
			{
				DrawScreen();
				Player.drawText("Would you like to purchase insurance. hit for yes. stay for no.", 180, 150);
			}
		}
		if (Player.response == 'a')
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
			if (Player.response == 'a')
			{
				std::cout << "You pay Insurance bet : " << Player.GetBet() / 2 << " Chips" << std::endl;
			}
			Player.DisplayPlayer(playerHand);
			Dealer.DisplayDealerPost(dealerHand);
			std::cout << "Dealer has BlackJack"<<std::endl;
			if (Player.response == 'a')
			{
				std::cout << "You get insurance payout for : " << Player.GetBet() << " Chips" << std::endl;
				Player.GetWinnings(Player.GetBet());
			}
			Dealer.SetBlackJack(true);
			if (Player.CalculateValue(playerHand) == 21)
			{
				std::cout << "Player Push.   You get " << Player.GetBet() << " Chips" << std::endl;
			}
		}
		else
		{
			system("cls");
			if (Player.response == 'a')
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
	Deck.MakeDeck();
	Deck.ShuffleDeck();

}

void FBlackJackGame::ResetHands(Card playerHand[], Card dealerHand[], Card playSplitHand[])
{
	Player.ResetPlayer(playerHand, playSplitHand);
	for (int32 i = 0; i < 5; i++)
	{
		dealerHand[i] = Dealer.blank;
		Dealer.SetCardInHand((0 - Dealer.GetCardInHand()));
		playerCards[i]->setVisible(false);
		splitCards[i]->setVisible(false);
		dealerCards[i]->setVisible(false);
	}
	Dealer.ResetStay();
}

void FBlackJackGame::Deal(Card playerHand[], Card dealerHand[])
{
	for (int32 i = 0; i < 2; i++)
	{
		playerHand[i] = *(Deck.getDeckPtr() + GetCurrentCard());
		playerCards[i]->setRow(playerHand[i].row);
		playerCards[i]->setCurrentFrame(playerHand[i].frame);
		playerCards[i]->setVisible(true);
		SetCurrentCard();
		dealerHand[i] = *(Deck.getDeckPtr() + GetCurrentCard());
		dealerCards[i]->setRow(dealerHand[i].row);
		dealerCards[i]->setCurrentFrame(dealerHand[i].frame);
		if (1==i)
			dealerCards[i]->setVisible(false);
		else 
			dealerCards[i]->setVisible(true);
		SetCurrentCard();
		//std::cout << "Player card " << playerHand[i].face << " " << playerHand[i].suit << std::endl;
		//std::cout << "Dealer card " << dealerHand[i].face << " " << dealerHand[i].suit << std::endl;

	}
	Player.DisplayPlayer(playerHand);
	Dealer.DisplayDealerPre(dealerHand);
}

void FBlackJackGame::PlayGame()
{
	for (int i = 0; i < 5; i++)
	{
		playerCards[i] = new Sprite("Images/CardDeck.png", 330 + i*10, 320 - i*15, 81, 117, renderer);
		splitCards[i] = new Sprite("Images/CardDeck.png", 200 + i*10, 320 - i*15, 81, 117, renderer);
		dealerCards[i] = new Sprite("Images/CardDeck.png", 300 + i*10, 150, 81, 117, renderer);
	}

	hitButton    = new Sprite("Images/CardDeck.png", 50,  400, 81 * 2, 117 / 2+1, renderer);
	hitButton->setRow(8);								  
	hitButton->setCurrentFrame(3);						  
	stayButton 	 = new Sprite("Images/CardDeck.png", 150, 400, 81 * 2, 117 / 2+1, renderer);
	stayButton->setRow(9);								  
	stayButton->setCurrentFrame(3);						  
	doDownButton = new Sprite("Images/CardDeck.png", 250, 400, 81 * 2, 117 / 2+1, renderer);
	doDownButton->setRow(8);							  
	doDownButton->setCurrentFrame(4);					  
	surrenButton = new Sprite("Images/CardDeck.png", 350, 400, 81 * 2, 117 / 2+1, renderer);
	surrenButton->setRow(9);
	surrenButton->setCurrentFrame(4);
	
	Player.renderer = renderer;
	Dealer.renderer = renderer;
	Player.background = background;
	Player.deltaT = deltaT;
	for (int i = 0; i < 5; i++)
	{
		Player.playerCards[i] = playerCards[i];
		Player.dealerCards[i] = dealerCards[i];
		Player.splitCards[i] = splitCards[i];
		Dealer.dealerCards[i] = dealerCards[i];
	}
	Player.hitButton = hitButton;
	Player.stayButton = stayButton;
	Player.doDownButton = doDownButton;
	Player.surrenButton = surrenButton;
	Player.event = event;

	quit = false;
	while (quit == false)
	{
		if (SDL_GetTicks() - updatedTime >= deltaT)
		{
			DrawScreen();
			srand(time(NULL));
			int seperatorCard = ((rand() % 100) + 150);
			while (GetCurrentCard() < seperatorCard && !GetIsPlay() && quit == false)
			{
				if (SDL_GetTicks() - updatedTime >= deltaT)
				{
					SDL_PollEvent(&event);
					ResetHands(playerHand, dealerHand, playSplitHand);
					DrawScreen();
					Player.DisplayPlayerPre();
					Player.MakeBet();
					system("cls");

					Deal(playerHand, dealerHand);
					DrawScreen();
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
							playSplitHand[1] = *(Deck.getDeckPtr() + (GetCurrentCard()));
							AddCurrentCard();
							playerHand[1] = *(Deck.getDeckPtr() + (GetCurrentCard()));
							system("cls");
							Player.DisplaySplit(playerHand, playSplitHand);
							Dealer.DisplayDealerPre(dealerHand);
							while (!Player.GetStay())
							{
								if (SDL_GetTicks() - updatedTime >= deltaT)
								{
									Player.SplitPlay(playerHand, playSplitHand, Deck.getDeckPtr(), GetCurrentCard());
									system("cls");
									AddCurrentCard();
									Player.DisplaySplit(playerHand, playSplitHand);
									Dealer.DisplayDealerPre(dealerHand);
									DrawScreen();
								}
							}
						}
						else
						{
							while (!Player.GetStay())
							{
								if (SDL_GetTicks() - updatedTime >= deltaT)
								{
									Player.Play(playerHand, Deck.getDeckPtr(), GetCurrentCard());
									system("cls");
									AddCurrentCard();
									Player.DisplayPlayer(playerHand);
									Dealer.DisplayDealerPre(dealerHand);
									DrawScreen();
								}
							}
						}
						Results();
					}
					Player.response = ' ';
					if (Player.GetChips() <= 0)
					{
						quit = true;
						system("pause");
					}
					else
					{
						while (Player.response != 'd' && Player.response != 'f' )
						{
							if (SDL_GetTicks() - updatedTime >= deltaT)
							{
								if (Player.response == 'f')
								{
									quit = true;
								}
								else { quit = false; }
								DrawScreen();
								Player.drawText("Would you like to keep playing? DoubleDown for yes. Surrender for no.", 180, 150);
							}
						}
					}
				}
			}
			if (quit == true)
			{
				system("cls");
				Smiley();
				if (Player.GetChips() <= 0)
				{
					std::cout << "You ran out of chips" << std::endl;
				}
				std::cout << "Thanks for playing" << std::endl;
			}
			else
			{
				std::cout << "Seperator card reached. Reshuffling the deck!";
				currentCard = 0;
				Deck.ShuffleDeck();
			}
			DrawScreen();
		}
	}

	for (int i = 0; i < 5; i++)
	{
		delete playerCards[i];
		delete splitCards[i];
		delete dealerCards[i];
	}

	delete cardSheet;
	delete hitButton;
	delete stayButton;
	delete doDownButton;
	delete surrenButton;

	
	
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
			Player.GetWinnings(Player.GetBet()*2 + Player.GetBet()/2);
		}
	}
	else if (!Player.IsPlayerBust() || !Player.IsSplitBust())
	{
		if (Player.GetBet() == 0)
		{
			std::cout << "You surrender. You get 1/2 your bet back back" << std::endl;
		}
		else
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
			else if (CheckWin(playerHand) && !Player.IsPlayerBust())
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
				else if (CheckWin(playSplitHand) && !Player.IsSplitBust())
				{
					splitResult = "Split Hand Wins.   ";
					splitWinMulti = 2;
				}
				else if (Player.IsSplitBust())
				{
					splitResult = "Split Hand Bust.   ";
					splitWinMulti = 0;
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
				std::cout << playerResult << " You got " << winnings << " Chips" << std::endl;
				Player.GetWinnings(winnings);
			}
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
		if (SDL_GetTicks() - updatedTime >= deltaT)
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
			DrawScreen();
		}
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
	if (handValue > 21) { return false; }
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

bool FBlackJackGame::GetQuit()
{
	return quit;
}

void FBlackJackGame::PrintIntro()
{

	std::cout << "		 _     _            _    _            _" << std::endl;
	std::cout << "		| |   | |          | |  (_)          | |" << std::endl;
	std::cout << "		| |__ | | __ _  ___| | ___  __ _  ___| | __" << std::endl;
	std::cout << "		| '_ \\| |/ _` |/ __| |/ / |/ _` |/ __| |/ /" << std::endl;
	std::cout << "		| |_) | | (_| | (__|   <| | (_| | (__|   <" << std::endl;
	std::cout << "		|_.__/|_|\\__,_|\\___|_|\\_\\ |\\__,_|\\___|_|\\_\\" << std::endl;
	std::cout << "		                       _/ | " << std::endl;
	std::cout << "				     |__ /" << std::endl << std::endl;
	std::cout << "		Welcome to Blackjack" << std::endl << std::endl;
	std::cout << "	The object of the game to is beat the dealer without going over 21." << std::endl;
	std::cout << "	You and the dealer will start with 2 cards however the dealer will only show his top card." << std::endl;
	std::cout << "	The dealer will always stay on 17 or more." << std::endl;
	std::cout << "	For each hand you will have the following options A:Hit S:Stay D:DoubleDown F:Surrender." << std::endl;
	std::cout << "	Hit allows you to draw a new card while stay means that you will keep the cards that you currently have." << std::endl;
	std::cout << "	Hands can have no more then a maximum of 5 cards." << std::endl;
	std::cout << "	DoubleDown and Surrender can only be use as the first action of a new hand." << std::endl;
	std::cout << "	DoubleDown allows you to double your bet and draw a single card and stay." << std::endl;
	std::cout << "	Surrender allows you to forfeit your hand and you get 1/2 of your bet back." << std::endl;
	std::cout << "	If the top card of the dealer is visible, you may bet insurance. Insurance is a bet that the dealer" << std::endl;
	std::cout << "	has 21. If the dealer has 21 you will receive a payout of 1:1 of your insurance bet." << std::endl;
	std::cout << "	If you receive 2 cards of equal value you may split your hand once and play a second hand with the" << std::endl;
	std::cout << "	second card. Both hands will receive a second card and can be played normally starting with the split hand." << std::endl;
	std::cout << "	Blackjack is when you get 21 fromyour original 2 cards and you recieve a payout of 3:2." << std::endl;
	std::cout << "	Split hands cannot get blackjack. " << std::endl;
	std::cout << "	If you and the dealer have hands of equal value it is a push and you keep your bet." << std::endl;

	Player.drawText("	Welcome to Blackjack", 100, 100);

	system("pause");
	system("cls");

}

void FBlackJackGame::Smiley()
{
	std::cout << "                  __ooooooooo__" << std::endl;
	std::cout << "             oOOOOOOOOOOOOOOOOOOOOOo" << std::endl;
	std::cout << "         oOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOo" << std::endl;
	std::cout << "      oOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOo" << std::endl;
	std::cout << "    oOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOo" << std::endl;
	std::cout << "   oOOOOOOOOOOO*  *OOOOOOOOOOOOOO*  *OOOOOOOOOOOo" << std::endl;
	std::cout << "  oOOOOOOOOOOO      OOOOOOOOOOOO      OOOOOOOOOOOo" << std::endl;
	std::cout << "  oOOOOOOOOOOOOo  oOOOOOOOOOOOOOOo  oOOOOOOOOOOOOOo" << std::endl;
	std::cout << " oOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOo" << std::endl;
	std::cout << " oOOOO     OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO     OOOOo" << std::endl;
	std::cout << " oOOOOOO OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO OOOOOOo" << std::endl;
	std::cout << "  *OOOOO  OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO  OOOOOO*" << std::endl;
	std::cout << "  *OOOOOO  *OOOOOOOOOOOOOOOOOOOOOOOOOOOOO*  OOOOOO*" << std::endl;
	std::cout << "   *OOOOOO  *OOOOOOOOOOOOOOOOOOOOOOOOOOO*  OOOOOO*" << std::endl;
	std::cout << "    *OOOOOOo  *OOOOOOOOOOOOOOOOOOOOOOO*  oOOOOOO*" << std::endl;
	std::cout << "      *OOOOOOOo  *OOOOOOOOOOOOOOOOO*  oOOOOOOO*" << std::endl;
	std::cout << "        *OOOOOOOOo  *OOOOOOOOOOO*  oOOOOOOOO*" << std::endl;
	std::cout << "           *OOOOOOOOo           oOOOOOOOO*" << std::endl;
	std::cout << "              *OOOOOOOOOOOOOOOOOOOOO*" << std::endl;
	std::cout << "                    ''ooooooooo''" << std::endl;
}




