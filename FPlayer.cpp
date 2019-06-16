#include"FBlackJackGame.h"
#include "FPlayer.h"
#include<iostream>
#include<string>





FPlayer::FPlayer()
{
}

FPlayer::FPlayer(Uint32 deltaT, Uint32 updatedTime, SDL_Renderer * renderer,Sprite *background, Sprite *playerCards[5], Sprite *dealerCards[5], Sprite *splitCards[5], Sprite * hitButton, Sprite * stayButton, Sprite * doDownButton, Sprite * surrenButton)
{
	this->deltaT = deltaT;
	this->updatedTime = updatedTime;
	this->renderer = renderer;
	this->background = background;
	for (int i = 0; i < 5; i++)
	{
		this->playerCards[i] = playerCards[i];
		this->dealerCards[i] = dealerCards[i];
		this->splitCards[i] = splitCards[i];
	}
	this->hitButton = hitButton;
	this->stayButton = stayButton;
	this->doDownButton = doDownButton;
	this->surrenButton = surrenButton;

}


FPlayer::~FPlayer()
{
}

void FPlayer::Play(Card hand[], Card *deckPtr, int currentCard)
{
	cardInHand = GetCardInHand(hand);
	bust = false;
	handTotal = CalculateValue(hand);
	if (cardInHand == 2)
	{
		if (handTotal == 21)
		{
			stay = true;
			std::cout << "Player Gets BlackJack!!" << std::endl;
			playBlackJack = true;
		}
		else
		{
			DoubleDownOpt(hand, deckPtr, currentCard, cardInHand);
		}
		DrawScreen();
	}
	else
	{
		if (handTotal == 21)
		{
			stay = true;
			std::cout << "You got 21" << std::endl;
		}
		else if (handTotal > 21)
		{
			stay = true;
			bust = true;
			std::cout << "Player bust" << std::endl;
		}
		else if (cardInHand == 5)
		{
			stay = true;
			if (handTotal > 21)
			{
				bust = true;
				std::cout << "Player bust" << std::endl;
			}
		}
		else
		{
			SetButtonVisible(true, true, false, false);
			do
			{
				DrawScreen();
			} while (!ClickHit() && !ClickStay());
			if (response == 'a')
			{
				Hit(hand, deckPtr, currentCard, cardInHand);
			}
			else
			{
				std::cout << "You Stay" << std::endl;
				stay = true;
			}
		}
	}
	if (stay)
	{
		SetButtonVisible(false, false, false, false);
		DrawScreen();
	}
}

void FPlayer::SplitPlay(Card hand[], Card splitHand[], Card *deckPtr, int currentCard)
{
	splitBust = false;
	// play split hand
	if (!splitStay)
	{
		splitCardInHand=GetCardInHand(splitHand);
		handTotal = CalculateValue(splitHand);
		if (splitCardInHand == 2)
		{
			if (handTotal == 21)
			{
				splitStay = true;
			}
			else
			{
				SplitDoubleDownOpt(splitHand, deckPtr, currentCard,splitCardInHand);
			}

		}
		else
		{
			if (handTotal == 21)
			{
				splitStay = true;
				std::cout << "You got 21" << std::endl;
			}
			else if (handTotal > 21)
			{
				splitStay = true;
				splitBust = true;
				std::cout << "Split Hand Bust" << std::endl;
			}
			else if (cardInHand == 5)
			{
				splitStay = true;
				if (handTotal > 21)
				{
					splitBust = true;
					std::cout << "Split Hand bust" << std::endl;
				}
			}
			else
			{
				SetButtonVisible(true, true, false, false);
				do
				{
					DrawScreen();
				} while (!ClickHit() && !ClickStay());
				if (response == 'a')
				{
					SplitHit(splitHand, deckPtr, currentCard,splitCardInHand);
				}
				else
				{
					std::cout << "Split Hand Stay" << std::endl;
					splitStay = true;
				}
			}
		}
		if (splitStay)
		{
			SetButtonVisible(false, false, false, false);
			DrawScreen();
		}

	}
	//Back to Player hand
	else
	{
		cardInHand = GetCardInHand(hand);
		bust = false;
		handTotal = CalculateValue(hand);
		if (cardInHand == 2)
		{
			if (handTotal == 21)
			{
				stay = true;
			}
			else
			{
				DoubleDownOpt(hand, deckPtr, currentCard,cardInHand);
			}

		}
		else
		{
			if (handTotal == 21)
			{
				stay = true;
				std::cout << "You got 21" << std::endl;
			}
			else if (handTotal > 21)
			{
				stay = true;
				bust = true;
				std::cout << "Player bust" << std::endl;
			}
			else if (cardInHand == 5)
			{
				stay = true;
				if (handTotal > 21)
				{
					bust = true;
					std::cout << "Player bust" << std::endl;
				}
			}
			else
			{
				SetButtonVisible(true, true, false, false);
				do{
					DrawScreen();
				} while (!ClickHit() && !ClickStay());
				if (response == 'a')
				{
					Hit(hand, deckPtr, currentCard, cardInHand);
				}
				else
				{
					std::cout << "You Stay" << std::endl;
					stay = true;
				}
			}
		}
	}
	if (stay)
	{
		SetButtonVisible(false, false, false, false);
		DrawScreen();
	}
}

int FPlayer::CalculateValue(Card hand[])
{
	value = hand[0].value + hand[1].value + hand[2].value + hand[3].value + hand[4].value;
	if (value > 21)
	{
		for (int i = 0; i < 5; i++)
		{
			if (hand[i].value == 11)
			{
				hand[i].value = 1;
				break;
			}
		}
		value = hand[0].value + hand[1].value + hand[2].value + hand[3].value + hand[4].value;
	}
	
	return value;
}
//return number of cards in hand
int FPlayer::GetCardInHand(Card hand[])
{
	cardInHand = 0;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].value > 0)
		{
			cardInHand++;
		}
	}
	return cardInHand;
}

void FPlayer::MakeBet()
{
	while (bet > chips || bet < 1)
	{
		std::cin.clear();
		while (std::cout << "Bet ammount :" && !(std::cin >> bet))
		{
			std::cin.clear(); //clear bad input flag
			std::cin.ignore(std::numeric_limits<int>::max(), '\n'); //discard input
			std::cout << "Invalid input; please re-enter.\n";
		}
		/*std::getline (std::istream, bet);*/
	}
	chips -= bet;
}

int FPlayer::GetBet()
{
	return bet;
}

void FPlayer::GetWinnings(int winnings)
{
	chips += winnings;
}

void FPlayer::DisplayPlayerPre()
{
	system("cls");
	std::cout << "Player" << std::endl;
	std::cout << "Chips :" << chips << "        Bet :" << bet << std::endl;
}

void FPlayer::DisplayPlayer(Card hand[])
{
	std::cout << "Player" << std::endl;
	std::cout << "Chips :" << chips << "        Bet :" << bet << std::endl;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].value == 0)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << "//*" << hand[i].face << " " << hand[i].suit << "*\\\\" << std::endl;
		}
	}
	std::cout << "Player hand value :" << CalculateValue(hand) << "\n" << std::endl;
	
}

//Display both player and split hand
void FPlayer::DisplaySplit(Card hand[], Card splitHand[])
{
	std::cout << "Player                        SplitHand" << std::endl;
	std::cout << "Chips :" << chips << "        Bet :" << bet << "        Split Bet:"<<splitBet << std::endl;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].value == 0 && splitHand[i].value>0)
		{
			std::cout << "                            " << "//*" << splitHand[i].face << " " << splitHand[i].suit << "*\\\\" << std::endl;
		}
		else if (hand[i].value > 0 && splitHand[i].value == 0)
		{
			std::cout << "//*" << hand[i].face << " " << hand[i].suit << "*\\\\" << std::endl;
		}
		else if (hand[i].value == 0 && splitHand[i].value == 0)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << "//*" << hand[i].face << " " << hand[i].suit << "*\\\\           " << "//*" << splitHand[i].face << " " << splitHand[i].suit << "*\\\\"<< std::endl;
		}
	}
	std::cout << "Player hand value :" << CalculateValue(hand) << "          Split Hand value :" << CalculateValue(splitHand) << "\n" << std::endl;
}

bool FPlayer::IsSplit(Card hand[],int chips, int bet)
{
	isSplit = false;
	char response = ' ';
	if (hand[0].value == hand[1].value || hand[0].face == hand[1].face)
	{
		if (bet <= chips)
		{
			SetButtonVisible(true, true, false, false);
			while (!ClickHit() && !ClickStay())
			{
				DrawScreen();
			}
			if (response == 'a')
			{
				isSplit = true;
				ReBet();
				splitBet = bet;
			}
		}
		else
		{
			std::cout << "Not enough chips to split" << std::endl;
		}
	}
	return isSplit;
}

int FPlayer::GetChips()
{
	return chips;
}

void FPlayer::ReBet()
{
	chips = chips - bet;
}

void FPlayer::ResetPlayer(Card hand[], Card splitHand[])
{
	SetButtonVisible(false, false, false, false);
	stay = false;
	bust = false;
	value = 0;
	bet = 0;
	isSplit = false;
	splitBust = true;
	splitStay = false;
	splitValue = 0;
	splitBet = 0;
	cardInHand = 0;
	playBlackJack = false;
	for (int i = 0; i < 5; i++)
	{
		hand[i] = blank;
		splitHand[i] = blank;
		playerCards[i]->setVisible(false);
		playerCards[i]->setRow(4);
		playerCards[i]->setCurrentFrame(0);
		splitCards[i]->setVisible(false);
		splitCards[i]->setRow(4);
		splitCards[i]->setCurrentFrame(0);
	}
	DrawScreen();
}

bool FPlayer::GetStay()
{
	return stay;
}

void FPlayer::Hit(Card hand[], Card *deckPtr, int currentCard, int cardInHand)
{
	hand[cardInHand] = *(deckPtr + currentCard);
	playerCards[cardInHand]->setRow(hand[cardInHand].row);
	playerCards[cardInHand]->setCurrentFrame(hand[cardInHand].frame);
	playerCards[cardInHand]->setVisible(true);
	DrawScreen();
	cardInHand++;
	if (CalculateValue(hand) > 21)
	{
		stay = true;
		bust = true;
		SetButtonVisible(false, false, false, false);
	}
}

void FPlayer::SplitHit(Card splitHand[], Card *deckPtr, int currentCard, int cardInHand)
{
	splitHand[cardInHand] = *(deckPtr + currentCard);
	splitCards[cardInHand]->setRow(splitHand[cardInHand].row);
	splitCards[cardInHand]->setCurrentFrame(splitHand[cardInHand].frame);
	splitCards[cardInHand]->setVisible(true);
	DrawScreen();
	cardInHand++;
	if (CalculateValue(splitHand) > 21)
	{
		splitStay = true;
		splitBust = true;
		SetButtonVisible(false, false, false, false);
	}
}

bool FPlayer::IsPlayerBust()
{
	return bust;
}

bool FPlayer::IsSplitBust()
{
	return splitBust;
}

bool FPlayer::GetSplitHandBust()
{
	return splitBust;
}

void FPlayer::DoubleDownOpt(Card hand[],Card *deckPtr,int currentCard, int cardInHand)
{
	bust = false;
	if (bet > chips)
	{
		SetButtonVisible(true, true, false, true);
		do
		{
			DrawScreen();
		} while (!ClickHit() && !ClickStay() && !ClickSurren());
		if (response == 'a')
		{
			Hit(hand, deckPtr, currentCard, cardInHand);
		}
		else if (response == 'f')
		{
			std::cout << "You surrender. You get " << (bet / 2) << " Chips back" << std::endl;
			GetWinnings((bet / 2));
			stay = true;
			bust = true;
			bet = 0;
		}
		else
		{
			std::cout << "You Stay" << std::endl;
			stay = true;
		}
	}
	else
	{
		SetButtonVisible(true, true, true, true);
		do
		{
			DrawScreen();
		} while (!ClickHit() && !ClickStay() && !ClickDoDown() && !ClickSurren());
		if (response == 'd')
		{
			Hit(hand, deckPtr, currentCard, cardInHand);
			std::cout << "You double down" << std::endl;
			ReBet();
			bet += bet;
			stay = true;
		}
		else if (response == 'a')
		{
			Hit(hand, deckPtr, currentCard, cardInHand);
		}
		else if (response == 'f')
		{
			std::cout << "You surrender. You get " << (bet / 2) << " Chips back" << std::endl;
			GetWinnings((bet / 2));
			stay = true;
			bet = 0;
		}
		else
		{
			std::cout << "You Stay" << std::endl;
			stay = true;
		}
	}
	if (stay)
	{
		SetButtonVisible(false, false, false, false);
		DrawScreen();
	}
}

void FPlayer::SplitDoubleDownOpt(Card splitHand[], Card *deckPtr, int currentCard, int splitCardInHand)
{
	splitBust = false;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (bet > chips)
	{
		SetButtonVisible(true, true, false, false);
		do
		{
			DrawScreen();
		} while (!ClickHit() && !ClickStay() );
		if (response == 'a')
		{
			SplitHit(splitHand, deckPtr, currentCard, cardInHand);
		}

		else
		{
			std::cout << "You Stay" << std::endl;
			splitStay = true;
		}
	}
	else
	{
		SetButtonVisible(true, true, true, false);
		do
		{
			DrawScreen();
		} while (!ClickHit() && !ClickStay() && !ClickDoDown());
		
		doDownButton->setVisible(false);
		
		if (response == 'd')
		{
			SplitHit(splitHand, deckPtr, currentCard, cardInHand);
			std::cout << "You double down" << std::endl;
			ReBet();
			splitBet += splitBet;
			splitStay = true;
		}
		else if (response == 'a')
		{
			SplitHit(splitHand, deckPtr, currentCard, cardInHand);
		}
		else
		{
			std::cout << "You Stay" << std::endl;
			splitStay = true;
		}
		
	}
	if (splitStay)
	{
		SetButtonVisible(false, false, false, false);
		DrawScreen();
	}
}

int FPlayer::GetSplitValue()
{
	return splitValue;
}

int FPlayer::GetSplitBet()
{
	return splitBet;
}

bool FPlayer::IsPlayBJ()
{
	return playBlackJack;
}

void FPlayer::SetButtonVisible(bool hitButton, bool stayButton, bool doDownButton, bool surrenButton)
{
	this->hitButton->setVisible(hitButton);
	this->stayButton->setVisible(stayButton);
	this->doDownButton->setVisible(doDownButton);
	this->surrenButton->setVisible(surrenButton);
}

void FPlayer::DrawScreen()
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

	SDL_RenderPresent(renderer);
}

bool FPlayer::ClickHit()
{
	/** Directly read from Keyboard */
	const Uint8*keys = SDL_GetKeyboardState(nullptr);
	SDL_Rect mouseClick;
	if (SDL_SCANCODE_A ||
		((SDL_GetMouseState(&mouseClick.x, &mouseClick.y) == SDL_PRESSED) && mouseClick.x <= hitButton->getXPos()
		&& mouseClick.x >= hitButton->getXPos() + hitButton->getWidth() && mouseClick.y <= hitButton->getYPos()
		&& mouseClick.y >= hitButton->getYPos() + hitButton->getHeight()))
	{
		response = 'a';
		return true;
	}
	else
		return false;
}

bool FPlayer::ClickStay()
{
	/** Directly read from Keyboard */
	const Uint8*keys = SDL_GetKeyboardState(nullptr);

	SDL_Rect mouseClick;
	if (SDL_SCANCODE_S ||
		((SDL_GetMouseState(&mouseClick.x, &mouseClick.y) == SDL_PRESSED) && mouseClick.x <= stayButton->getXPos()
		&& mouseClick.x >= stayButton->getXPos() + stayButton->getWidth() && mouseClick.y <= stayButton->getYPos()
		&& mouseClick.y >= stayButton->getYPos() + stayButton->getHeight()))
	{
		response = 's';
		return true;
	}
	else
		return false;
}

bool FPlayer::ClickDoDown()
{
	/** Directly read from Keyboard */
	const Uint8*keys = SDL_GetKeyboardState(nullptr);

	SDL_Rect mouseClick;
	if (SDL_SCANCODE_D ||
		((SDL_GetMouseState(&mouseClick.x, &mouseClick.y) == SDL_PRESSED) && mouseClick.x <= doDownButton->getXPos()
		&& mouseClick.x >= doDownButton->getXPos() + doDownButton->getWidth() && mouseClick.y <= doDownButton->getYPos()
		&& mouseClick.y >= doDownButton->getYPos() + doDownButton->getHeight()))
	{
		response = 'd';
		return true;
	}
	else
		return false;
}

bool FPlayer::ClickSurren()
{
	/** Directly read from Keyboard */
	const Uint8*keys = SDL_GetKeyboardState(nullptr);

	SDL_Rect mouseClick;
	if (SDL_SCANCODE_F ||
		((SDL_GetMouseState(&mouseClick.x, &mouseClick.y) == SDL_PRESSED) && mouseClick.x <= surrenButton->getXPos()
		&& mouseClick.x >= surrenButton->getXPos() + surrenButton->getWidth() && mouseClick.y <= surrenButton->getYPos()
		&& mouseClick.y >= surrenButton->getYPos() + surrenButton->getHeight()))
	{
		response = 'f';
		return true;
	}
	else
		return false;
}





