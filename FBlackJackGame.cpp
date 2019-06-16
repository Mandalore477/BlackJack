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
	FPlayer PlayerFull(deltaT, updatedTime, renderer,background,playerCards,dealerCards,splitCards,hitButton,stayButton,doDownButton,surrenButton );
	Player = PlayerFull;
	FDealer DealerFull(renderer,dealerCards);
	Dealer = DealerFull;
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
	char response=' ';

	if (Player.GetBet() / 2 < Player.GetChips())
	{
		while (response != 'y' && response != 'n')
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			while (std::cout << "Would you like to purchase insurance (Y/N)" && !(std::cin >> response))
			{
				std::cin.clear(); //clear bad input flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
				std::cout << "Invalid input; please re-enter.\n";
			}
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
		SetCurrentCard();
		dealerHand[i] = *(Deck.getDeckPtr() + GetCurrentCard());
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
				ResetHands(playerHand, dealerHand, playSplitHand);
				Player.DisplayPlayerPre();
				Player.MakeBet();
				system("cls");

				Deal(playerHand, dealerHand);
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
							Player.SplitPlay(playerHand, playSplitHand, Deck.getDeckPtr(), GetCurrentCard());
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
							Player.Play(playerHand, Deck.getDeckPtr(), GetCurrentCard());
							system("cls");
							AddCurrentCard();
							Player.DisplayPlayer(playerHand);
							Dealer.DisplayDealerPre(dealerHand);
						}
					}
					Results();
				}
				char response = ' ';
				if (Player.GetChips() <= 0)
				{
					quit = true;
					system("pause");
				}
				else
				{
					while (response != 'y' && response != 'n')
					{
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						while (std::cout << "Would you like to continue playing (Y/N)" && !(std::cin >> response))
						{
							std::cin.clear(); //clear bad input flag
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
							std::cout << "Invalid input; please re-enter.\n";
						}
						response = tolower(response);
						if (response == 'n')
						{
							quit = true;
						}
						else { quit = false; }
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

void FBlackJackGame::drawText(string text, Uint16 posX, Uint16 posY)
{
	const char* textChar = text.c_str();
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

	SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, textChar, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = posX;  //controls the rect's x coordinate 
	Message_rect.y = posY; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 30; // controls the height of the rect

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

	//Don't forget too free your surface and texture
}


