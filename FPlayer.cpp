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

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			/** Check if user tries to quit the window */
		case SDL_QUIT:
			exit(1);		// Break out of loop to end game
			break;

			/**	Check if a key was pressed */
		case SDL_MOUSEBUTTONDOWN:
			if (hitButton->isVisible() && (event.button.x <= hitButton->getXPos())
				&& (event.button.x >= hitButton->getXPos() + hitButton->getWidth()) && (event.button.y <= hitButton->getYPos())
				&& (event.button.y >= hitButton->getYPos() + hitButton->getHeight()))
				ClickHit();
			else if (stayButton->isVisible() && event.button.x <= stayButton->getXPos()
				&& event.button.x >= stayButton->getXPos() + stayButton->getWidth() && event.button.y <= stayButton->getYPos()
				&& event.button.y >= stayButton->getYPos() + stayButton->getHeight())
				ClickStay();
			else if (doDownButton->isVisible() && event.button.x <= doDownButton->getXPos()
				&& event.button.x >= doDownButton->getXPos() + doDownButton->getWidth() && event.button.y <= doDownButton->getYPos()
				&& event.button.y >= doDownButton->getYPos() + doDownButton->getHeight())
				ClickDoDown();
			else if (surrenButton->isVisible() && event.button.x <= surrenButton->getXPos()
				&& event.button.x >= surrenButton->getXPos() + surrenButton->getWidth() && event.button.y <= surrenButton->getYPos()
				&& event.button.y >= surrenButton->getYPos() + surrenButton->getHeight())
				ClickSurren();
		}
	}
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
			response = ' ';
			SetButtonVisible(true, true, false, false);
			do{
			
				if (SDL_GetTicks() - updatedTime >= deltaT)
				{
					DrawScreen();
				}
			} while (response!='a' && response!='s');
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
				response = ' ';
				SetButtonVisible(true, true, false, false);
				do
				{
					if (SDL_GetTicks() - updatedTime >= deltaT)
					{
						DrawScreen();
					}
				} while (response != 'a' && response != 's');
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
				response = ' ';
				SetButtonVisible(true, true, false, false);
				do{
					if (SDL_GetTicks() - updatedTime >= deltaT)
					{
						DrawScreen();
					}
				} while (response != 'a' && response != 's');
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
		if (SDL_GetTicks() - updatedTime >= deltaT)
		{
			std::cin.clear();
			while (std::cout << "Bet ammount :" && !(std::cin >> bet))
			{
				if (SDL_GetTicks() - updatedTime >= deltaT)
				{
					std::cin.clear(); //clear bad input flag
					std::cin.ignore(std::numeric_limits<int>::max(), '\n'); //discard input
					std::cout << "Invalid input; please re-enter.\n";
					DrawScreen();
				}
			}
			DrawScreen();
		}
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
			while (response != 'a' && response != 's')
			{
				if (SDL_GetTicks() - updatedTime >= deltaT)
				{
					DrawScreen();
				}
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
			if (SDL_GetTicks() - updatedTime >= deltaT)
			{
				DrawScreen();
			}
		} while (response != 'a' && response != 's' && response != 'f');
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
			if (SDL_GetTicks() - updatedTime >= deltaT)
			{
				DrawScreen();
			}
		} while (response != 'a' && response != 's' && response != 'd' && response != 'f');
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
			if (SDL_GetTicks() - updatedTime >= deltaT)
			{
				DrawScreen();
			}
		} while (response != 'a' && response != 's' );
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
			if (SDL_GetTicks() - updatedTime >= deltaT)
			{
				DrawScreen();
			}
		} while (response != 'a' && response != 's' && response != 'd');
		
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

void FPlayer::ClickHit()
{
		response = 'a';
}

void FPlayer::ClickStay()
{
		response = 's';
}

void FPlayer::ClickDoDown()
{
		response = 'd';
}

void FPlayer::ClickSurren()
{
		response = 'f';
}

void FPlayer::drawText(string inputText, Uint16 posX, Uint16 posY)
{
	const char* textChar = inputText.c_str();
	TTF_Font* Sans = TTF_OpenFont("Fonts/DroidSansMono.ttf", 24); //this opens a font style and sets a size

	SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Sans, textChar, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = posX;  //controls the rect's x coordinate 
	Message_rect.y = posY; // controls the rect's y coordinte
	Message_rect.w = surfaceMessage->w; // controls the width of the rect
	Message_rect.h = surfaceMessage->h; // controls the height of the rect

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

	//Don't forget too free your surface and texture
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
}



